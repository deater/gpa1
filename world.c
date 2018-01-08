#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* usleep() */
#include <math.h>

#include "vmw_texture.h"
#include "vmw_glfont.h"

#include "gl_helper.h"

#include "guinea_pig.h"
#include "spaceship.h"
#include "matrix_math.h"

#include "keyboard.h"

#include "main_menu.h"

#include "textures.h"
#include "terrain.h"

#include "game_state.h"
#include "battle.h"
#include "setup_enemies.h"

#include "joppatowne.h"

#include "tfv.h"

    /* As much as I have memorized... */
#define PI 3.141592653589793238462643383279502884197169399
  



extern int use_lighting;
extern int show_fps;

extern GLuint spaceships[2];
   GLuint terrain[NUM_TERRAINS];




   /* icky globals */
int show_menu=0;

float camera_direction=90*(180.0/PI),camerax=-10.0,cameray=0,cameraz=5.0;
    
int turn_right=0,turn_left=0,draw_splash=0,accelerating=0;

   
#define D2R(x) (x*(PI/180.0))


#define MAPSIZE_X 40
#define MAPSIZE_Y 40

map_element world_map[MAPSIZE_X][MAPSIZE_Y];



int in_game_menu(game_state_type *gs) {

    int result,position=0;
    char alpha,tempstring[25];
   
    glDisable(GL_LIGHTING);
    glViewport(0,0,gs->xsize,gs->ysize);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,320,0,200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    result=check_keyboard(&alpha,1);

   
    while (1) {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glColor3f(1.0,1.0,0.0);
       
       glBegin(GL_LINES);
          glVertex3f(95,0,0);
          glVertex3f(95,200,0);
         
       glEnd();
       
       glRasterPos3f(100,180,0);
       vmwGLString("LOCATION: ",font);
       glRasterPos3f(120,170,0);
       vmwGLString(world_map[gs->gridx][gs->gridy].region_name,font);
       glRasterPos3f(100,160,0);
       vmwGLString("HEALTH:",font);
       
       sprintf(tempstring,"%d/%d",gs->health,gs->health_total);
       
       glRasterPos3f(120,150,0);
       vmwGLString(tempstring,font);
       
       glRasterPos3f(100,140,0);
       vmwGLString("MONEY:",font);
       glRasterPos3f(120,130,0);
       sprintf(tempstring,"$%d",gs->money);
       vmwGLString(tempstring,font);
       
       putMenuOption(20,180,"CONTINUE",0,position,0);
       putMenuOption(20,170,"SAVE",1,position,0);
       putMenuOption(20,120,"QUIT",2,position,0);

       glFlush();
       SDL_GL_SwapBuffers();
       
       usleep(100);
       result=check_keyboard(&alpha,0);
   
       if ( (result>>16)&MENU_PRESSED) {
	  reshape(gs->xsize,gs->ysize);
	  check_keyboard(&alpha,1);
	  return CANCELED;
       }
       
       if ( (result>>16)&UP_PRESSED) {
	  position--;
	  if (position<0) position=0;
       }
       if ( (result>>16)&DOWN_PRESSED) {
	  position++;
	  if (position>2) position=2;
       }
       if ( (result>>16)&CONFIRM_PRESSED) {
	  reshape(gs->xsize,gs->ysize);
	  switch(position) {
	   case 0: return CANCELED;
	   case 1: return SAVE_GAME;
	   case 2: return QUIT;
	  }
       }
       
    }
    return NEW_GAME;
}



void render_world(game_state_type *gs) {
   
   int i,j,distance_seen,land_type,tempx,tempy;
   GLfloat shadow_width;
     GLfloat light_position[]={5.0,5.0,100.0,0.0
     };
   
//     GLfloat light_ambient[]={0.5,0.5,0.5,1.0
//     };
       GLfloat lmodel_ambient[]={0.9,0.9,0.9,1.0
       };
   
   
       GLfloat white_light[]={1.0,1.0,1.0,1.0
       };
   
   
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   glLoadIdentity();
   gluLookAt(camerax,cameray,cameraz,
	     0.0,0.0,0.0,
	     0.0,0.0,1.0);
   
   if (use_lighting) {
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//      glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
      glLightfv(GL_LIGHT0, GL_SPECULAR,white_light);
      
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
//      glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);

      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
   }
   

   
     {
	GLfloat default_a[]={0.6,0.6,0.6,1.0};
        GLfloat default_d[]={   0.8,0.8,0.8,1.0};
	GLfloat default_s[]={0.0,0.0,0.0,1.0};
	GLfloat default_e[]={0.0,0.0,0.0,1.0
	};
	
        glMaterialfv(GL_FRONT,GL_AMBIENT,default_a);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,default_d);
	glMaterialfv(GL_FRONT,GL_SPECULAR,default_s);
	glMaterialfv(GL_FRONT,GL_EMISSION,default_e);
     }

   glPushMatrix();
   glRotatef( (360-gs->direction),0,0,1);   
   glTranslatef(-gs->pigx,-gs->pigy,-gs->pigz);

   
   glColor3f(0.4102,0.543,0.1328);
   
   glEnable(GL_TEXTURE_2D);
       /* Draw Sky */

   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   glBindTexture(GL_TEXTURE_2D,textures[SKY_TEXTURE]);
   glBegin(GL_QUADS);
   
#define SKY_DISTANCE 60
   
          /* Back */
      glNormal3f(-1.0,0.0,0.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(SKY_DISTANCE,-SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(SKY_DISTANCE,-SKY_DISTANCE,SKY_DISTANCE);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(SKY_DISTANCE,SKY_DISTANCE,SKY_DISTANCE);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(SKY_DISTANCE,SKY_DISTANCE,-SKY_DISTANCE);
   
         /* Right */
   
      glNormal3f(0.0,1.0,0.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(SKY_DISTANCE,-SKY_DISTANCE,SKY_DISTANCE);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(SKY_DISTANCE,-SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-SKY_DISTANCE,-SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-SKY_DISTANCE,-SKY_DISTANCE,SKY_DISTANCE);
   
         /* Front */
      glNormal3f(1.0,0.0,0.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(-SKY_DISTANCE,-SKY_DISTANCE,SKY_DISTANCE);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(-SKY_DISTANCE,-SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-SKY_DISTANCE,SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-SKY_DISTANCE,SKY_DISTANCE,SKY_DISTANCE);
   
         /* Left */
   
       glNormal3f(0.0,-1.0,0.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(-SKY_DISTANCE,SKY_DISTANCE,SKY_DISTANCE);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(-SKY_DISTANCE,SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(SKY_DISTANCE,SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(SKY_DISTANCE,SKY_DISTANCE,SKY_DISTANCE);
   
   
          /* top */
      glNormal3f(0.0,0.0,-1.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(SKY_DISTANCE,SKY_DISTANCE,SKY_DISTANCE);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(SKY_DISTANCE,-SKY_DISTANCE,SKY_DISTANCE);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-SKY_DISTANCE,-SKY_DISTANCE,SKY_DISTANCE);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-SKY_DISTANCE,SKY_DISTANCE,SKY_DISTANCE);
   
             /* bottom */
      glNormal3f(0.0,0.0,1.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(SKY_DISTANCE,SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(SKY_DISTANCE,-SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-SKY_DISTANCE,-SKY_DISTANCE,-SKY_DISTANCE);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-SKY_DISTANCE,SKY_DISTANCE,-SKY_DISTANCE);
   
   glEnd();

//   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

   
   
   
       /* Draw World */   


   
       /* 25.5 = "radius of world" */
    distance_seen=(int)sqrt(2*25.5*cameraz);

    for(i=-distance_seen;i<=distance_seen;i++) {
       for(j=-distance_seen;j<=distance_seen;j++) {
	    
	  tempx=gs->gridx+i;
	  if (tempx<0) tempx+=MAPSIZE_X;
	  if (tempx>39) tempx-=MAPSIZE_X;
	  tempy=gs->gridy+j;
	  if (tempy<0) tempy+=MAPSIZE_Y;
	  if (tempy>39) tempy-=MAPSIZE_Y;
	    
	  land_type=world_map[tempx][tempy].terrain_type;

	  glPushMatrix();
	    // +2 removed???
	  glTranslatef( (i*4),(j*4),0); 
	  glRotatef(world_map[tempx][tempy].rotation,0,0,1);
          glCallList(terrain[land_type]);
	  
	  if (!gs->in_spaceship) {
	     if ((tempx==gs->spaceship_gridx) && (tempy==gs->spaceship_gridy)) {
		glTranslatef(gs->spaceship_xoffset,gs->spaceship_yoffset,0.75);
		glRotatef(gs->spaceship_direction,0,0,1);
		glCallList(spaceships[0]);

//		glPushMatrix();
//		glEnable(GL_TEXTURE_2D);
//		glScalef(0.75,0.75,0.75);
//		glTranslatef(2,2,5.75);
//		glRotatef(90,0,1,0);
//
//		   draw_tfv(0,0,0,0,
//			    0,315,0,
//			    0,0,0,
//			    1);
//		glPopMatrix();
	     }
	  }
	  
	  glPopMatrix();

       }
    }

   

    glPopMatrix();

    glPushMatrix(); 

    if (gs->in_spaceship) {  
          /* draw shadow */
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D,textures[SHADOW_TEXTURE]);   
      
       glBegin(GL_QUADS);  
          shadow_width=(1.5+(-gs->pigz/5.0))/2.0;
      
          glNormal3f(0.0,0.0,1.0);
   
          glTexCoord2f(0.0, 0.0);
          glVertex3f(-0.75,-shadow_width,-gs->pigz+0.1);
      
          glTexCoord2f(1.0, 0.0);
          glVertex3f(0.75,-shadow_width,-gs->pigz+0.1);
      
          glTexCoord2f(1.0, 1.0);
          glVertex3f(0.75,shadow_width,-gs->pigz+0.1);
      
          glTexCoord2f(0.0, 1.0);
          glVertex3f(-0.75,shadow_width,-gs->pigz+0.1);         
      
       glEnd();
      
       if ((draw_splash) && (gs->pigz<0.75)) {
          glBindTexture(GL_TEXTURE_2D,textures[SPLASH_TEXTURE]);   
      
          glBegin(GL_QUADS);
               
             glNormal3f(0.0,0.0,1.0);
   
             glTexCoord2f(0.0, 0.0);
             glVertex3f(-8.0,-1.0,-0.85);
      
             glTexCoord2f(1.0, 0.0);
             glVertex3f(-8.0,1.0,-0.85);
      
             glTexCoord2f(1.0, 1.0);
             glVertex3f(-1.45,1.0,-0.85);
      
             glTexCoord2f(0.0, 1.0);
             glVertex3f(-1.25,-1.0,-0.85);         
          glEnd();
       }
       if (turn_right) {
          glRotatef(20,1.0,0.0,0.0);
       }
       if (turn_left) {
	  glRotatef(-20,1.0,0.0,0.0);
       }
      
       if (accelerating) glCallList(spaceships[1]);
       else glCallList(spaceships[0]);
    }
    else {
#if 0
       glBegin(GL_QUADS);
         glVertex3f(-1.5,0.5,1.0);
         glVertex3f( 1.5,0.5,1.0);
         glVertex3f( 1.5,-0.5,1.0);
         glVertex3f(-1.5,-0.5,1.0);
       glEnd();
#endif
       glRotatef(90,1,0,0);
       glCallList(guinea_pigs[LEONARD]);
    }
           
    glPopMatrix();
      
   
   
//   printf("%.2f %.2f %.2f %i %i\n",gs->pigx,gs->pigy,gs->pigz,gs->gridx,gs->gridy);
   

       /* Prototype to display overlay text */
    if (show_menu) {
       glDisable(GL_LIGHTING);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D(0,320,0,200);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();  
       
       glBegin(GL_QUADS);
          glNormal3f(0,0,1);
          glVertex3f(5,5,-0.1);
          glVertex3f(100,5,-0.1);
          glVertex3f(100,100,-0.1);
          glVertex3f(5,100,-0.1);
       glEnd();
      
       glColor3f(1.0,0.0,0.0);
       glRasterPos3f(5,5,0);
       vmwGLString("A VMW SOFTWARE PRODUCTION",font);
       
       reshape(640,480);
    }
   
       /* Flush it out to the device */
    glFlush();
    SDL_GL_SwapBuffers();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}



int handle_ss_keyboard(int keyspressed,game_state_type  *gs,float scale) {
  

    float x_offset,y_offset;
    int tempx,tempy;
   
    draw_splash=0;
    turn_right=0; turn_left=0; accelerating=0;
    
    if (keyspressed&RIGHT_PRESSED) {
       gs->direction-=10*scale;
       turn_right=1;
    }
    if (keyspressed&LEFT_PRESSED) {
       gs->direction+=10*scale;
       turn_left=1;
    }
    if (keyspressed&ACTION1_PRESSED) {
       gs->pigy+=sin( (gs->direction*PI)/180.0)*scale;
       gs->pigx+=cos( (gs->direction*PI)/180.0)*scale;
       accelerating=1;
    }
    if (keyspressed&ACTION2_PRESSED) {
       gs->pigy-=sin( (gs->direction*PI)/180.0)*scale;
       gs->pigx-=cos( (gs->direction*PI)/180.0)*scale;      
       accelerating=1;
    }

    if (keyspressed&UP_PRESSED) {
       gs->pigz+=1.0*scale;
    }
    if (keyspressed&DOWN_PRESSED) {
       gs->pigz-=1.0*scale;
    }
   
       /* After up and down so GP doesn't end up in air */
    if ((keyspressed>>16)&CONFIRM_PRESSED) {
       	     printf("TRYING TO GET OUT: %i,%i,%.2f,%.2f %i,%i,%.2f,%.2f\n",
		    gs->gridx,gs->gridy,gs->pigx,gs->pigy,
		    gs->spaceship_gridx,gs->spaceship_gridy,gs->spaceship_xoffset,gs->spaceship_yoffset);
       if (world_map[gs->gridx][gs->gridy].terrain_type==GRASS_TERRAIN) {
          gs->in_spaceship=0;
	  gs->spaceship_gridx=gs->gridx;
	  gs->spaceship_gridy=gs->gridy;
	  gs->spaceship_direction=gs->direction;
	  gs->spaceship_xoffset=gs->pigx;
	  gs->spaceship_yoffset=gs->pigy;
	  gs->pigz=0.5;
       }
       
    }

    if (!gs->in_spaceship) return 0;
   
	     /* Collision detection */
	  
	  
	  /* spaceship is 3x1.5 more or less */
	  /* so check all 4 corners */
          /* Double check these later */
	  
	  x_offset=  sin(((gs->direction-26.565)*PI)/180.0)*1.677;
	  y_offset=  cos(((gs->direction-26.565)*PI)/180.0)*1.677;
	  
	  /* lower right */
	  
	  tempx=gs->gridx;  tempy=gs->gridy;
	  if ((x_offset+gs->pigx)>=2.0) {
	     tempx++;
	     if (tempx>=MAPSIZE_X) tempx=0;
	  }
	  if ((y_offset+gs->pigy)>=2.0) {
	     tempy++;
	     if (tempy>=MAPSIZE_Y) tempy=0;
	  }
	  if ((gs->pigx-x_offset)<=-2.0) {
	     tempx--;
	     if (tempx<0) tempx=MAPSIZE_X-1;
	  }
	  if ((gs->pigy-y_offset)<=-2.0) {
	     tempy--;
	     if (tempy<0) tempy=MAPSIZE_Y-1;
	  }
	  if (gs->pigz<terrain_heights[world_map[tempx][tempy].terrain_type]+0.89) { 

//	     printf("SPLASH %f %f\n",gs->pigz,terrain_heights[world_map[tempx][tempy].terrain_type]+0.9);
	     gs->pigz=terrain_heights[world_map[tempx][tempy].terrain_type]+0.9;
	     draw_splash=1;
	  }	  	  
	  
	  
	  	  /* lower left */
	  
	  tempx=gs->gridx;  tempy=gs->gridy;
	  if ((gs->pigx-x_offset)>=2.0) {
	     tempx++;
	     if (tempx>=MAPSIZE_X) tempx=0;
	  }
	  if ((y_offset+gs->pigy)>=2.0) {
	     tempy++;
	     if (tempy>=MAPSIZE_Y) tempy=0;
	  }
	  if ((gs->pigx+x_offset)<=-2.0) {
	     tempx--;
	     if (tempx<0) tempx=MAPSIZE_X-1;
	  }
	  if ((gs->pigy-y_offset)<=-2.0) {
	     tempy--;
	     if (tempy<0) tempy=MAPSIZE_Y-1;
	  }
	  if (gs->pigz<terrain_heights[world_map[tempx][tempy].terrain_type]+0.89) { 
	     gs->pigz=terrain_heights[world_map[tempx][tempy].terrain_type]+0.9;
	     draw_splash=1;
	  }	  	  
	  
	  	  /* upper left */
	  
	  tempx=gs->gridx;  tempy=gs->gridy;
	  if ((gs->pigx-x_offset)>=2.0) {
	     tempx++;
	     if (tempx>=MAPSIZE_X) tempx=0;
	  }
	  if ((gs->pigy-y_offset)>=2.0) {
	     tempy++;
	     if (tempy>=MAPSIZE_Y) tempy=0;
	  }
	  if ((gs->pigx+x_offset)<=-2.0) {
	     tempx--;
	     if (tempx<0) tempx=MAPSIZE_X-1;
	  }
	  if ((gs->pigy+y_offset)<=-2.0) {
	     tempy--;
	     if (tempy<0) tempy=MAPSIZE_Y-1;
	  }
	  if (gs->pigz<terrain_heights[world_map[tempx][tempy].terrain_type]+0.89) { 
	     gs->pigz=terrain_heights[world_map[tempx][tempy].terrain_type]+0.9;
	     draw_splash=1;
	  }	  	  
	  
	  
	  	  /* upper right */
	  
	  tempx=gs->gridx;  tempy=gs->gridy;
	  if ((x_offset+gs->pigx)>=2.0) {
	     tempx++;
	     if (tempx>=40) tempx=0;
	  }
	  if ((gs->pigy-y_offset)>=2.0) {
	     tempy++;
	     if (tempy>=40) tempy=0;
	  }
	  if ((gs->pigx-x_offset)<=-2.0) {
	     tempx--;
	     if (tempx<0) tempx=39;
	  }
	  if ((gs->pigy+y_offset)<=-2.0) {
	     tempy--;
	     if (tempy<0) tempy=39;
	  }
	  if (gs->pigz<terrain_heights[world_map[tempx][tempy].terrain_type]+0.89) { 
	     gs->pigz=terrain_heights[world_map[tempx][tempy].terrain_type]+0.9;
	     draw_splash=1;
	  }	  	  
       
	  
	  
	  if (gs->pigz>5) gs->pigz=5;
	  if (gs->pigx>=2.0) { 
	     gs->gridx++; 
	     gs->pigx-=4.0;
	  }
	  if (gs->pigx<=-2.0) {
	     gs->gridx--;
	     gs->pigx+=4.0;
	  }
	  if (gs->pigy>=2.0) {
	     gs->gridy++;
	     gs->pigy-=4.0;
	  }
	  if (gs->pigy<=-2.0) {
	     gs->gridy--;
	     gs->pigy+=4.0;
	  }
	      
	  if (gs->gridx>=40) gs->gridx=0;
	  if (gs->gridx<0) gs->gridx=39;
	  if (gs->gridy>=40) gs->gridy=0;
	  if (gs->gridy<0) gs->gridy=39;

    return 0;
}

int handle_gp_keyboard(int keyspressed, game_state_type *gs, float scale) {

    struct {
       float x;
       float y;
    } p[6];
   
    float oldpigx,oldpigy,olddirection;
    float x1,y1,xdelta,ydelta,theta;   
    int collision=0;
    int i,j,grid[3][3]; 
    int collide[3][3]={{0,0,0},{0,0,0},{0,0,0}};
    int need_terrain_check=0,need_spaceship_check=0,tempx,tempy;   

       /* remove later */
    olddirection=gs->direction;
    oldpigx=gs->pigx;
    oldpigy=gs->pigy;
   
    if (keyspressed&RIGHT_PRESSED) {
       gs->direction=olddirection-10*scale;
    }
    if (keyspressed&LEFT_PRESSED) {
       gs->direction=olddirection+10*scale;    
    }
    
    if (keyspressed&ACTION1_PRESSED) {
       do_battle(gs);
    }
   
//    if (keyspressed&ACTION2_PRESSED) {
//       do_jtowne(gs);  
//    }
   
       /* should these go off of new direction or old??? */
    if (keyspressed&UP_PRESSED) {
       gs->pigy=oldpigy+sin( D2R(gs->direction))*scale;
       gs->pigx=oldpigx+cos( D2R(gs->direction))*scale;
    }
          
    if (keyspressed&DOWN_PRESSED) {
       gs->pigy=oldpigy-sin( D2R(gs->direction))*scale;
       gs->pigx=oldpigx-cos( D2R(gs->direction))*scale;       
    }
   
   
    if (keyspressed&ACTION1_PRESSED) {
    }

   
    /**********************************
      COLLISION DETECTION
     * ********************************/

   
    /* This is inefficient now.  There has to be a better way of doing this*/
    /* possibly one optimization is bitmasks of terrain types, but that */
    /* depends on < 32 types */
   
   
    /* we check for mountains, towns, or ocean */
    /* plus spaceship */
   

    for(j=0;j<3;j++) {
       for(i=0;i<3;i++) {
	  tempx=((gs->gridx+(i-1))+40)%40;
	  tempy=((gs->gridy+(-(j-1)))+40)%40;
	  grid[i][j]=world_map[tempx][tempy].terrain_type;
	  if (grid[i][j]>WALKABLE_LIMIT) need_terrain_check++;
	  if ((tempx==gs->spaceship_gridx)&&(tempy==gs->spaceship_gridy)) {
	     need_spaceship_check++;
	  }
       }
    }

//    if (need_terrain_check) {
//       printf("TERRAIN CHECK!\n");
//    }
   
//    if (need_spaceship_check) {
//       printf("SPACESHIP CHECK\n");
//    }

   
                /* should monitor x_offset,y_offset too */
    if ( ( (keyspressed>>16)&CONFIRM_PRESSED) && need_spaceship_check)  {
	     printf("TRYING TO GET IN: %i,%i,%.2f,%.2f %i,%i,%.2f,%.2f\n",
		    gs->gridx,gs->gridy,gs->pigx,gs->pigy,
		    gs->spaceship_gridx,gs->spaceship_gridy,gs->spaceship_xoffset,gs->spaceship_yoffset);
       
	     if ((gs->spaceship_gridx==gs->gridx) &&  
	         (gs->spaceship_gridy==gs->gridy)) {
		gs->in_spaceship=1;
		gs->pigx=gs->spaceship_xoffset;
		gs->pigy=gs->spaceship_yoffset;
		gs->direction=gs->spaceship_direction;
		gs->pigz=0.75;
	     }

    }


   
    theta=D2R(gs->direction+90);
   
    x1=sin(theta);
    y1=cos(theta);
    xdelta=(y1)/2;  /* Quick hack ;) 90 degrees out of phase */
    ydelta=(x1)/2;  /* instead of doing another sin/cos      */

    x1*=1.5; y1*=1.5;
   
       /* The 6 points we will be checking */
    p[0].x= x1-xdelta; p[0].y= y1+ydelta;
    p[1].x= x1+xdelta; p[1].y= y1-ydelta;
    p[2].x=   -xdelta; p[2].y=   +ydelta;
    p[3].x=    xdelta; p[3].y=   -ydelta;
    p[4].x=-x1-xdelta; p[4].y=-y1+ydelta;
    p[5].x=-x1+xdelta; p[5].y=-y1-ydelta;


    if (need_terrain_check) {
       for(i=0;i<6;i++) {
             /* Col 0 */
          if (p[i].x+gs->pigx<-2) {
	     if (p[i].y+gs->pigy<-2) {
	        collide[0][2]++;
	     }
	     else if (p[i].y+gs->pigy>2) {
	        collide[0][0]++;
	     }
 	     else {
	        collide[0][1]++;
	     }
          } else if (p[i].x+gs->pigx>2) { /* Col 2 */
	     if (p[i].y+gs->pigy<-2) {
	        collide[2][2]++;
	     }
	     else if (p[i].y+gs->pigy>2) {
	        collide[2][0]++;
	     }
	     else {
	        collide[2][1]++;
	     }
          } else { /* Col 1 */
	     if (p[i].y+gs->pigy<-2) {
	        collide[1][2]++;
	     }
	     else if (p[i].y+gs->pigy>2) {
	        collide[1][0]++;
	     }
	     else {
	        collide[1][1]++;
	     }
	  }
       }
   
       for (i=0;i<3;i++) {
          for(j=0;j<3;j++) {
	     if ((collide[i][j]) && (grid[i][j]>WALKABLE_LIMIT)) { 
	        collision++;
		if (grid[i][j]==JOPPATOWNE_TERRAIN) do_jtowne(gs);
//	     printf("Collision %i %i %.2f %.2f\n",i,j,gs->pigx,gs->pigy);
	     }
	  }
       }
    }
#if 0   
    if ((collision) || ((keyspressed>>16)&ACTION2_PRESSED)){
       for(i=0;i<3;i++) {
	  printf("%i %i %i\n",grid[0][i],grid[1][i],grid[2][i]);
       }
       printf("\n");
       for(i=0;i<3;i++) {
	  printf("%i %i %i\n",collide[0][i],collide[1][i],collide[2][i]);
       }
       for(i=0;i<6;i++) {
	  printf("p[%i]: %.2f %.2f\n",i,p[i].x,p[i].y);
       }
       printf("%i %i %.2f %.2f\n",gs->gridx,gs->gridy,gs->pigx,gs->pigy);
       printf("\n");
      	 
    }
#endif
    if (!collision) {

    }
    else {
              /* RESTORE LAST KNOWN GOOD POSITION */
       gs->pigx=oldpigx;
       gs->pigy=oldpigy;
       gs->direction=olddirection;

       

    }


   

    if (gs->pigx>=2.0) { 
       gs->gridx++; 
       gs->pigx-=4.0;
    }
    if (gs->pigx<=-2.0) {
       gs->gridx--;
       gs->pigx+=4.0;
    }
    if (gs->pigy>=2.0) {
       gs->gridy++;
       gs->pigy-=4.0;
    }
    if (gs->pigy<=-2.0) {
       gs->gridy--;
       gs->pigy+=4.0;
    }

    if (gs->gridx>=40) gs->gridx=0;
    if (gs->gridx<0) gs->gridx=39;
	                      
    if (gs->gridy>=40) gs->gridy=0;
    if (gs->gridy<0) gs->gridy=39;
	     
    return 0;      
}
       
       
       

int do_world(game_state_type *gs) {

   
    int frames=0,fps_msecs=0,old_fps_msecs=0,keyspressed=0;
    int old_msecs=0,new_msecs=0;
   
    float scale=0.0;

    int result;
    char key_alpha;
   
       /* Init screen and keyboard */
    reshape(gs->xsize,gs->ysize);
    check_keyboard(&key_alpha,1);

       /* Setup display Lists */

    guinea_pigs[LEONARD]=setup_pig_list(BROWN_WHITE_BROWN_TEXTURE,
			   BROWN_TEXTURE,
			   NOSE_TEXTURE,
			   BROWN_TEXTURE,
			   EYE_TEXTURE,
			   FLESH_TEXTURE,
			   FLESH_TEXTURE);

    guinea_pigs[OLD_GREY]=setup_pig_list(GREY_TEXTURE,
			   GREY_TEXTURE,
			   GREY_NOSE_TEXTURE,
			   GREY_TEXTURE,
			   GREY_EYE_TEXTURE,
			   DARK_SKIN_TEXTURE,
			   DARK_SKIN_TEXTURE);

     guinea_pigs[SNOWY]=setup_pig_list(WHITE_TEXTURE,
			   WHITE_TEXTURE,
			   WHITE_TEXTURE,
			   WHITE_TEXTURE,
			   ALBINO_EYE_TEXTURE,
			   FLESH_TEXTURE,
      		           FLESH_TEXTURE);
   
    spaceships[0]=setup_spaceship(0);
    spaceships[1]=setup_spaceship(1);
    setup_enemies();
    gs->whoami=LEONARD;
   
    setup_map();
    setup_terrain();  
    
    old_msecs=SDL_GetTicks();

    gs->in_spaceship=0;
    gs->pigz=0.5;
   
    while (1) {
       
       frames++;
       new_msecs=SDL_GetTicks();
         
          /* * how far to go in 1s */
       scale=(new_msecs-old_msecs)/50.0;
       old_msecs=new_msecs;

       if (frames%100==0) {
	  old_fps_msecs=fps_msecs;
	  fps_msecs=SDL_GetTicks();
          printf("FPS=%.2f\n", frames/((fps_msecs-old_fps_msecs)/1000.0));	 
	  frames=0;
       }

          /* Check for input events */
       keyspressed=check_keyboard(&key_alpha,0);

       if (keyspressed&PAN_LEFT_PRESSED) {
          camera_direction-=(10.0*PI)/180;
	  if (camera_direction<0.0) camera_direction+=2*PI;
	  camerax=10*sin(camera_direction);
	  cameray=10*cos(camera_direction);
       }
       if (keyspressed&PAN_RIGHT_PRESSED) {
	  camera_direction+=(10.0*PI)/180;
	  if (camera_direction>2*PI) camera_direction-=2*PI;
	  camerax=10*sin(camera_direction);
	  cameray=10*cos(camera_direction);
       }
          /* Nonstandard key events */
       switch(key_alpha) {
          case 'l': use_lighting=!(use_lighting); break;
	  case 'm': cameraz-=0.5; break;
	  case 'i': cameraz+=0.5; break;
          case 'o': show_menu=!show_menu; break;
       }

       if (keyspressed&MENU_PRESSED) {
	  result=in_game_menu(gs);
	  if (result==QUIT) return -1;
       }
   
       if (gs->in_spaceship) handle_ss_keyboard(keyspressed,gs,scale);
       else handle_gp_keyboard(keyspressed,gs,scale);
       

       render_world(gs);       
/* Emulate low frame-rates */
//usleep(100000); 
    }
    return 1;
}
