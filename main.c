#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vmw_texture.h"
#include "vmw_glfont.h"

#include "gl_helper.h"

#include "opener.h"
#include "guinea_pig.h"
#include "spaceship.h"
#include "matrix_math.h"

#include "keyboard.h"

#include "story.h"

#include "textures.h"
#include "terrain.h"

    /* As much as I have memorized... */
#define PI 3.141592653589793238462643383279502884197169399
  

int old_msecs=0,new_msecs=0;

int use_lighting=1;

   GLuint leonard;
   GLuint spaceships[2];
   GLuint terrain[NUM_TERRAINS];


typedef struct {
   float direction,pigx,pigy,pigz;
   int gridx,gridy;
   int spaceship_active,in_spaceship;   
} game_state_type;

game_state_type gs={
   0,0,0,-0.5,
   5,13,
   1,1,
};

int whoami=0;

int show_menu=0;

float camera_direction=90*(180.0/PI),camerax=-10.0,cameray=0,cameraz=5.0;

int done=0;


void parse_config(void) {
   
}

   
#define D2R(x) ((x*PI)/180.0)


map_element world_map[40][40];

void LoadTextures(void) {

   glPixelStorei(GL_UNPACK_ALIGNMENT,1);
   
   glGenTextures(TOTAL_TEXTURES,textures);  
   
       /* 0 */
   LoadTexture(64,64,"./textures/carrot.amg",CARROT_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/eye.amg",EYE_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/face.amg",ROBOT_FACE_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/grass.amg",GRASS_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/leaves.amg",LEAVES_TEXTURE,1,GL_CLAMP);
       /* 5 */
   LoadTexture(64,64,"./textures/nose.amg",NOSE_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/sky.amg",SKY_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/brown.amg",BROWN_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/bwb.amg",BROWN_WHITE_BROWN_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/flesh.amg",FLESH_TEXTURE,0,GL_CLAMP);
       /* 10 */
   LoadTexture(64,64,"./textures/ocean.amg",OCEAN_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/mountain.amg",MOUNTAIN_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/cliff.amg",CLIFF_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/sand.amg",SAND_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/tree.amg",FOREST_TEXTURE,0,GL_REPEAT);
       /* 15 */
   LoadTexture(64,64,"./textures/shallow.amg",SHALLOW_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/tundra.amg",TUNDRA_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/spaceship_gray.amg",SS_GRAY,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/spaceship_top.amg",SS_TOP,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/spaceship_bottom.amg",SS_BOTTOM,0,GL_CLAMP);
       /* 20 */
   LoadTexture(64,64,"./textures/spaceship_thrust_on.amg",SS_THRUST,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/spaceship_thrust_off.amg",SS_NOTHRUST,0,GL_CLAMP);
   LoadTexture(128,64,"./textures/spaceship_right.amg",SS_RIGHT,0,GL_CLAMP);
   LoadTexture(128,64,"./textures/spaceship_left.amg",SS_LEFT,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/spaceship_back.amg",SS_BACK,0,GL_CLAMP);
       /* 25 */
   LoadAlphaTexture(64,64,"./textures/shadow.amg",SHADOW_TEXTURE,0,GL_CLAMP,0x00,0x00,0x00);
   LoadAlphaTexture(64,64,"./textures/splash.amg",SPLASH_TEXTURE,0,GL_CLAMP,0x52,0xdd,0xdd);
}

GLubyte *font;


void init(void) {
//   glViewport(0,0,640,480);

   setup_map();

   
   glPixelStorei(GL_UNPACK_ALIGNMENT,1);
   font=vmwLoadFont("./fonts/vmw.fnt",8,16,128,2);
   glClearColor(0.0,0.0,0.0,0.0);
   glClearDepth(1.0);
   glShadeModel(GL_SMOOTH);
//   glEnable(GL_LIGHTING);
//   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
//   gluPerspective(60.0f,(GLfloat)640/(GLfloat)480,0.1f,100.0f);
   
   LoadTextures();
   setup_terrain();  
}

  

int turn_right=0,turn_left=0,draw_splash=0;

void display(void) {
   
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
   glRotatef( (360-gs.direction),0,0,1);   
   glTranslatef(-gs.pigx,-gs.pigy,-gs.pigz);

   
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
	    
	  tempx=gs.gridx+i;
	  if (tempx<0) tempx+=40;
	  if (tempx>39) tempx-=40;
	  tempy=gs.gridy+j;
	  if (tempy<0) tempy+=40;
	  if (tempy>39) tempy-=40;
	    
	  land_type=world_map[tempx][tempy].terrain_type;

	  glPushMatrix();
	  glTranslatef( (i*4)+2,(j*4)+2,0); 
	  glRotatef(world_map[tempx][tempy].rotation,0,0,1);
          glCallList(terrain[land_type]);
	  glPopMatrix();

       }
    }

   
   
//   draw_carrot(-4.0,3.0,0.5,90);
   glPopMatrix();

   
//   draw_robo_pig(gs.pigx,gs.pigy,gs.pigz,direction);
//      draw_good_pig(gs.pigx,gs.pigy,gs.pigz,direction);

//   draw_guinea_pig(leonard,gs.pigx,gs.pigy,gs.pigz,direction);
   
   if (whoami==leonard) {
      glPushMatrix(); 
//      glTranslatef(gs.pigx,gs.pigy,gs.pigz);
      
//      glRotatef(direction,0.0,0.0,1.0);
//       glRotatef(0,0,0,1);
    /* draw shadow */
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,textures[SHADOW_TEXTURE]);   
      
   glBegin(GL_QUADS);
         
          shadow_width=(1.5+(-gs.pigz/5.0))/2.0;
      
          glNormal3f(0.0,0.0,1.0);
   
          glTexCoord2f(0.0, 0.0);
          glVertex3f(-0.75,-shadow_width,-gs.pigz+0.1);
      
          glTexCoord2f(1.0, 0.0);
          glVertex3f(0.75,-shadow_width,-gs.pigz+0.1);
      
          glTexCoord2f(1.0, 1.0);
          glVertex3f(0.75,shadow_width,-gs.pigz+0.1);
      
          glTexCoord2f(0.0, 1.0);
          glVertex3f(-0.75,shadow_width,-gs.pigz+0.1);         
      
      glEnd();
      
      
      if ((draw_splash) && (gs.pigz<0.75)) {
//	 printf("pigz: %f\n",gs.pigz);
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
      glCallList(spaceships[0]);
      
      glPopMatrix();
      
      /*
      draw_guinea_pig(leonard,0,0,0,0);
       */
   }
   
   
//   printf("%.2f %.2f %.2f %i %i\n",gs.pigx,gs.pigy,gs.pigz,gs.gridx,gs.gridy);
   

   if (show_menu) {
      glDisable(GL_LIGHTING);
//      glViewport(0,0,640,480);
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
      vmwGLString("A VMW SOFTWARE PRODUCTION",font,16,32,2);
       
      reshape(640,480);
//      gluPerspective(60.0,(GLfloat)640/(GLfloat)480,1.0,100.0);
//      glMatrixMode(GL_MODELVIEW);
   }
   
   
   glFlush();
   SDL_GL_SwapBuffers();

   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);
}



float scale=0.0;

int main(int argc, char **argv) {

   SDL_Joystick *joy;
   
   int frames=0,fps_msecs=0,old_fps_msecs=0,keyspressed=0;
   int xsize=640,ysize=480;
    int tempx,tempy;
   float x_offset,y_offset;

    char key_alpha;
   
   if (argc==2) {
      xsize=320;
      ysize=200;
   }
   
   if (argc==3) {
      xsize=1024;
      ysize=768;
   }
   
   
   parse_config();
   
   
       /* Initialize SDL */
   if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK)<0) {
      printf("Error trying to init SDL: %s\n",SDL_GetError());
      return -1;
   }
   
       /* Create a 640x480 OpenGL screen */
   if ( SDL_SetVideoMode(xsize, ysize, 0, SDL_OPENGL) == NULL ) {
      printf("Unable to create OpenGL screen: %s\n", SDL_GetError());
      SDL_Quit();
      return -2;
   }
   
   SDL_WM_SetCaption("Guinea Pig Adventure...",NULL);
   
       /* Try to init Joysticks */
    if (SDL_NumJoysticks()>0){
       /* Open joystick */
       joy=SDL_JoystickOpen(0);
       if (joy) {
	  printf("Opened Joystick 0\n");
	  printf("Name: %s\n", SDL_JoystickName(0));
	  SDL_JoystickEventState(SDL_ENABLE);
       }
    }
   
   
   init();
   reshape(xsize,ysize);
   
//   display();
 
    opener();
    do_story();
   
    leonard=setup_pig_list(0,0);
    spaceships[0]=setup_spaceship(0);
    whoami=leonard;

    old_msecs=SDL_GetTicks();
   
    while ( ! done ) {
       
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

       keyspressed=check_keyboard(&key_alpha);

       switch(key_alpha) {
          case 'l': use_lighting=!(use_lighting); break;
	  case 'k':  camera_direction+=(10.0*PI)/180;
	             if (camera_direction>2*PI) camera_direction-=2*PI;
	             camerax=10*sin(camera_direction);
	             cameray=10*cos(camera_direction);
	             break;
	  case 'j':  camera_direction-=(10.0*PI)/180;
	             if (camera_direction<0.0) camera_direction+=2*PI;
	             camerax=10*sin(camera_direction);
	             cameray=10*cos(camera_direction);
	             break;
	  case 'm':
	             cameraz-=0.5;
	             break;
	   case 'i': 
	             cameraz+=0.5;;
	             break;

	   case 'P': case 'p':
	             show_menu=!show_menu;
	             break;
	     
       }

       keyspressed&=0xffff; /* mask off momentary for now */

       if (keyspressed&ESC_PRESSED) {
	  done=1;
       }
   
       turn_right=turn_left=0,draw_splash=0;
       
       if (gs.in_spaceship) {
	  if (keyspressed&RIGHT_PRESSED) {
	     gs.direction-=10*scale;
	     turn_right=1;
          }
          if (keyspressed&LEFT_PRESSED) {
             gs.direction+=10*scale;
	     turn_left=1;
          }
          if (keyspressed&A_PRESSED) {
             gs.pigy+=sin( (gs.direction*PI)/180.0)*scale;
             gs.pigx+=cos( (gs.direction*PI)/180.0)*scale;
          }
          if (keyspressed&Z_PRESSED) {
             gs.pigy-=sin( (gs.direction*PI)/180.0)*scale;
             gs.pigx-=cos( (gs.direction*PI)/180.0)*scale;       
          }

	  
	  if (keyspressed&UP_PRESSED) {
	     gs.pigz+=1.0*scale;
          }
          if (keyspressed&DOWN_PRESSED) {
	     gs.pigz-=1.0*scale;

          }
	     /* Collision detection */
	  
	  
	  /* spaceship is 3x1.5 more or less */
	  /* so check all 4 corners */
          /* Double check these later */
	  
	  x_offset=  sin(((gs.direction-26.565)*PI)/180.0)*1.677;
	  y_offset=  cos(((gs.direction-26.565)*PI)/180.0)*1.677;
	  
	  /* lower right */
	  
	  tempx=gs.gridx;  tempy=gs.gridy;
	  if ((x_offset+gs.pigx)>=2.0) {
	     tempx++;
	     if (tempx>=40) tempx=0;
	  }
	  if ((y_offset+gs.pigy)>=2.0) {
	     tempy++;
	     if (tempy>=40) tempy=0;
	  }
	  if ((gs.pigx-x_offset)<=-2.0) {
	     tempx--;
	     if (tempx<0) tempx=39;
	  }
	  if ((gs.pigy-y_offset)<=-2.0) {
	     tempy--;
	     if (tempy<0) tempy=39;
	  }
	  if (gs.pigz<terrain_heights[world_map[tempx][tempy].terrain_type]+0.89) { 

//	     printf("SPLASH %f %f\n",gs.pigz,terrain_heights[world_map[tempx][tempy].terrain_type]+0.9);
	     gs.pigz=terrain_heights[world_map[tempx][tempy].terrain_type]+0.9;
	     draw_splash=1;
	  }	  	  
	  
	  
	  	  /* lower left */
	  
	  tempx=gs.gridx;  tempy=gs.gridy;
	  if ((gs.pigx-x_offset)>=2.0) {
	     tempx++;
	     if (tempx>=40) tempx=0;
	  }
	  if ((y_offset+gs.pigy)>=2.0) {
	     tempy++;
	     if (tempy>=40) tempy=0;
	  }
	  if ((gs.pigx+x_offset)<=-2.0) {
	     tempx--;
	     if (tempx<0) tempx=39;
	  }
	  if ((gs.pigy-y_offset)<=-2.0) {
	     tempy--;
	     if (tempy<0) tempy=39;
	  }
	  if (gs.pigz<terrain_heights[world_map[tempx][tempy].terrain_type]+0.89) { 
	     gs.pigz=terrain_heights[world_map[tempx][tempy].terrain_type]+0.9;
	     draw_splash=1;
	  }	  	  
	  
	  	  /* upper left */
	  
	  tempx=gs.gridx;  tempy=gs.gridy;
	  if ((gs.pigx-x_offset)>=2.0) {
	     tempx++;
	     if (tempx>=40) tempx=0;
	  }
	  if ((gs.pigy-y_offset)>=2.0) {
	     tempy++;
	     if (tempy>=40) tempy=0;
	  }
	  if ((gs.pigx+x_offset)<=-2.0) {
	     tempx--;
	     if (tempx<0) tempx=39;
	  }
	  if ((gs.pigy+y_offset)<=-2.0) {
	     tempy--;
	     if (tempy<0) tempy=39;
	  }
	  if (gs.pigz<terrain_heights[world_map[tempx][tempy].terrain_type]+0.89) { 
	     gs.pigz=terrain_heights[world_map[tempx][tempy].terrain_type]+0.9;
	     draw_splash=1;
	  }	  	  
	  
	  
	  	  /* upper right */
	  
	  tempx=gs.gridx;  tempy=gs.gridy;
	  if ((x_offset+gs.pigx)>=2.0) {
	     tempx++;
	     if (tempx>=40) tempx=0;
	  }
	  if ((gs.pigy-y_offset)>=2.0) {
	     tempy++;
	     if (tempy>=40) tempy=0;
	  }
	  if ((gs.pigx-x_offset)<=-2.0) {
	     tempx--;
	     if (tempx<0) tempx=39;
	  }
	  if ((gs.pigy+y_offset)<=-2.0) {
	     tempy--;
	     if (tempy<0) tempy=39;
	  }
	  if (gs.pigz<terrain_heights[world_map[tempx][tempy].terrain_type]+0.89) { 
	     gs.pigz=terrain_heights[world_map[tempx][tempy].terrain_type]+0.9;
	     draw_splash=1;
	  }	  	  
       
	  
	  
	  if (gs.pigz>5) gs.pigz=5;
	  if (gs.pigx>=2.0) { 
	     gs.gridx++; 
	     gs.pigx-=4.0;
	  }
	  if (gs.pigx<=-2.0) {
	     gs.gridx--;
	     gs.pigx+=4.0;
	  }
	  if (gs.pigy>=2.0) {
	     gs.gridy++;
	     gs.pigy-=4.0;
	  }
	  if (gs.pigy<=-2.0) {
	     gs.gridy--;
	     gs.pigy+=4.0;
	  }
	      
	  if (gs.gridx>=40) gs.gridx=0;
	  if (gs.gridx<0) gs.gridx=39;
	  if (gs.gridy>=40) gs.gridy=0;
	  if (gs.gridy<0) gs.gridy=39;
	
       }
       else {
          if (keyspressed&RIGHT_PRESSED) {
	     gs.direction-=10;
          }
          if (keyspressed&LEFT_PRESSED) {
             gs.direction+=10;    
          }
          if (keyspressed&UP_PRESSED) {
             gs.pigy+=sin( (gs.direction*PI)/180.0);
             gs.pigx+=cos( (gs.direction*PI)/180.0);
          }
          if (keyspressed&DOWN_PRESSED) {
             gs.pigy-=sin( (gs.direction*PI)/180.0);
             gs.pigx-=cos( (gs.direction*PI)/180.0);       
          }
	  if (keyspressed&A_PRESSED) {
	     gs.pigz-=1.0;
	     if (gs.pigz<-5) gs.pigz=-5;
          }
          if (keyspressed&Z_PRESSED) {
	     gs.pigz+=1.0;
	     if (gs.pigz>-0.5) gs.pigz=-0.5;
          }
       
	     	             if (gs.pigx>=2.0) { 
				gs.gridx++; 
				gs.pigx-=4.0;
				
			     }
	                     if (gs.pigx<=-2.0) {
				gs.gridx--;
				gs.pigx+=4.0;
			     }
	                     if (gs.pigy>=2.0) {
				gs.gridy++;
				gs.pigy-=4.0;
			     }
	                     if (gs.pigy<=-2.0) {
				gs.gridy--;
				gs.pigy+=4.0;
			     }
	      
	                     if (gs.gridx>=40) gs.gridx=0;
	                     if (gs.gridx<0) gs.gridx=39;
	                      
	                     if (gs.gridy>=40) gs.gridy=0;
	                     if (gs.gridy<0) gs.gridy=39;
	     
       
       }
       
       
       
       display();       
/* Emulate low frame-rates */
//usleep(100000); 
    }
    SDL_Quit();

   return 0;
}
