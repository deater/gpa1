#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* usleep()  */
#include <string.h> /* strncpy() */
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

#include "setup_enemies.h"


extern int use_lighting;
extern int show_fps;

#define PI 3.141592653589793238462643383279502884197169399


typedef struct {

   char string[35];
   int x,y,z;
   int timeout;
   float r,g,b;
   int displaying;
} message_type;


#define YOU_ATTACK 0
#define IT_ATTACKS 1
 


    

int do_battle(game_state_type *gs) {

    message_type message;
    message_type damage;
   
    int opening_pan=1,pan_timer=0,game_state=0;
   
    int frames=0,fps_msecs=0,old_fps_msecs=0,keyspressed=0;
    int old_msecs=0,current_msecs=0;
    int position=0,update_bottom_bar=1;

    int enemy_attacking=0,enemy_attack_count=0;
   
    int attacking=0,running=0,defending=0,run_count=0;
    int attack_count=0;
   
    float scale=0.0;

    float pig_x=-5,pig_y=0,pig_z=0.5,enemy_x=5,enemy_y=0,enemy_z=2;
   
    char key_alpha,temp_string[40];
    
    float camerax=-10.0,cameray=0,cameraz=5.0;

    int enemy_hp=500,enemy_hp_total=500;
   
    GLfloat light_position[]={5.0,5.0,100.0,0.0
    };

    GLfloat white_light[]={1.0,1.0,1.0,1.0
    };
   
    GLfloat lmodel_ambient[]={0.9,0.9,0.9,1.0
    };
       /* Init screen and keyboard */
    reshape(gs->xsize,gs->ysize);
    check_keyboard(&key_alpha,1);

   
    game_state=YOU_ATTACK;  /* could be IT_ATTACKS if "back attack" */

    old_msecs=SDL_GetTicks();
    pan_timer=old_msecs+5000;

    
    strncpy(message.string,"ATTACKED BY CUBE",32);
    message.x=80; message.y=175;
    message.r=1; message.g=1; message.b=1;
    message.timeout=old_msecs+5000;
    message.displaying=1;   
   
   
    glScissor(0,gs->ysize/4,gs->xsize,gs->ysize-(gs->ysize/4));
    
    while (1) {
       
       frames++;
       current_msecs=SDL_GetTicks();
         
          /* * how far to go in 1s */
       scale=(current_msecs-old_msecs)/50.0;
       old_msecs=current_msecs;

       if (frames%100==0) {
	  old_fps_msecs=fps_msecs;
	  fps_msecs=current_msecs;
          printf("FPS=%.2f\n", frames/((fps_msecs-old_fps_msecs)/1000.0));	 
	  frames=0;
       }

          /* Check for input events */
       keyspressed=check_keyboard(&key_alpha,0);
       
       if (keyspressed>>16&MENU_PRESSED) {
	  return 0;
       }

       if (game_state==YOU_ATTACK) {
       
	  if (keyspressed>>16&UP_PRESSED) {
	     update_bottom_bar=1;
	     position--;
	     if (position<0) position=0;
	  }
          if (keyspressed>>16&DOWN_PRESSED) {
	     update_bottom_bar=1;
	     position++;
	     if (position>3) position=3;
	  }
       
          if (keyspressed>>16&CONFIRM_PRESSED) {
	     update_bottom_bar=1;
	     if (position==0) {
		attacking=1;
		attack_count=current_msecs+2000;
		game_state=IT_ATTACKS;
	     }
	     if (position==1) {
		defending=1;
		game_state=IT_ATTACKS;
	     }
	     if (position==2) {
		game_state=IT_ATTACKS;
	     }
	     if (position==3) {
		running=1;
		run_count=current_msecs+3000;
		game_state=IT_ATTACKS;
	     }
	  }
       }

       
          /* TIMED EVENTS */
       if (running) {
	  if (current_msecs>run_count) return 0;
	  pig_x-=(scale*0.5);
       }
       
       if (attacking) {
	  pig_x+=(scale*0.5);
	  if (current_msecs>attack_count) {
	     attacking=0;
	     pig_x=-5;
	     
             enemy_hp-=100;
	     strncpy(damage.string,"100",32);
             damage.x=enemy_x; damage.y=enemy_y; damage.z=enemy_z;
             damage.r=1; damage.g=1; damage.b=1;
             damage.timeout=current_msecs+2000;
             damage.displaying=1;   
	  }
       }
       
       if (opening_pan) {
	  float theta=0;
	  
	  theta=(PI/180.0)*18.0*((pan_timer-current_msecs)/1000.0);
	  
	  camerax=-10*sin(theta);
	  cameray=-10*cos(theta);
	  
	  if (current_msecs>pan_timer) {
	     opening_pan=0;
	     camerax=0;
	     cameray=-10;
	     cameraz=5;
	     
	  }
       }

   


          /* Don't draw to area where status info is */
//       glScissor(0,gs->ysize/4,gs->xsize,gs->ysize-(gs->ysize/4));
       
       if (!update_bottom_bar) glEnable(GL_SCISSOR_TEST);
       
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glLoadIdentity();
       gluLookAt(camerax,cameray,cameraz,
	     0.0,0.0,0.0,
	     0.0,0.0,1.0);
   
       if (use_lighting) {
          glLightfv(GL_LIGHT0, GL_POSITION, light_position);
          glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
          glLightfv(GL_LIGHT0, GL_SPECULAR,white_light);
      
          glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

          glEnable(GL_LIGHTING);
          glEnable(GL_LIGHT0);
       }
   

   
       {
	  GLfloat default_a[]={0.6,0.6,0.6,1.0};
          GLfloat default_d[]={   0.8,0.8,0.8,1.0};
	  GLfloat default_s[]={0.0,0.0,0.0,1.0};
	  GLfloat default_e[]={0.0,0.0,0.0,1.0};
	
          glMaterialfv(GL_FRONT,GL_AMBIENT,default_a);
	  glMaterialfv(GL_FRONT,GL_DIFFUSE,default_d);
	  glMaterialfv(GL_FRONT,GL_SPECULAR,default_s);
	  glMaterialfv(GL_FRONT,GL_EMISSION,default_e);
       }

       glPushMatrix();
       
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
      
   glEnd();

//   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,textures[GRASS_TEXTURE]);
       
       
   glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(-SKY_DISTANCE,-SKY_DISTANCE);
       glVertex3f(-SKY_DISTANCE,-SKY_DISTANCE,0);
       
       glTexCoord2f(SKY_DISTANCE,-SKY_DISTANCE);
       glVertex3f(SKY_DISTANCE,-SKY_DISTANCE,0);
       
       glTexCoord2f(SKY_DISTANCE,SKY_DISTANCE);
       glVertex3f(SKY_DISTANCE,SKY_DISTANCE,0);
       
       glTexCoord2f(-SKY_DISTANCE,SKY_DISTANCE);
       glVertex3f(-SKY_DISTANCE,SKY_DISTANCE,0);
       
   glEnd();
       
#define BUSHES_DISTANCE 10
       
   glBindTexture(GL_TEXTURE_2D,textures[BUSHES_TEXTURE]);
   glBegin(GL_QUADS);
           
          /* BACK */
       glTexCoord2f(1,1);
       glVertex3f(BUSHES_DISTANCE,BUSHES_DISTANCE,0);
       
       glTexCoord2f(0,1);
       glVertex3f(BUSHES_DISTANCE,-BUSHES_DISTANCE,0);
       
       glTexCoord2f(0,0);
       glVertex3f(BUSHES_DISTANCE,-BUSHES_DISTANCE,5);
       
       glTexCoord2f(1,0);
       glVertex3f(BUSHES_DISTANCE,BUSHES_DISTANCE,5);
       
           /* RIGHT */
       glTexCoord2f(1,1);
       glVertex3f(BUSHES_DISTANCE,-BUSHES_DISTANCE,0);
       
       glTexCoord2f(0,1);
       glVertex3f(-BUSHES_DISTANCE,-BUSHES_DISTANCE,0);
       
       glTexCoord2f(0,0);
       glVertex3f(-BUSHES_DISTANCE,-BUSHES_DISTANCE,5);
       
       glTexCoord2f(1,0);
       glVertex3f(BUSHES_DISTANCE,-BUSHES_DISTANCE,5); 
       
           /* FRONT */
       glTexCoord2f(1,1);
       glVertex3f(-BUSHES_DISTANCE,BUSHES_DISTANCE,0);
       
       glTexCoord2f(0,1);
       glVertex3f(-BUSHES_DISTANCE,-BUSHES_DISTANCE,0);
       
       glTexCoord2f(0,0);
       glVertex3f(-BUSHES_DISTANCE,-BUSHES_DISTANCE,5);
       
       glTexCoord2f(1,0);
       glVertex3f(-BUSHES_DISTANCE,BUSHES_DISTANCE,5); 
       
          /* LEFT */
       glTexCoord2f(1,1);
       glVertex3f(-BUSHES_DISTANCE,BUSHES_DISTANCE,0);
       
       glTexCoord2f(0,1);
       glVertex3f(BUSHES_DISTANCE,BUSHES_DISTANCE,0);
       
       glTexCoord2f(0,0);
       glVertex3f(BUSHES_DISTANCE,BUSHES_DISTANCE,5);
       
       glTexCoord2f(1,0);
       glVertex3f(-BUSHES_DISTANCE,BUSHES_DISTANCE,5);

   glEnd();


          /* Draw pig */
       glPushMatrix();
       glTranslatef(pig_x,pig_y,pig_z);
       glRotatef(90,1,0,0);
       if (running) {
	  glRotatef(180,0,1,0);
       }
       glCallList(guinea_pigs[LEONARD]);
       glPopMatrix();

          /* Draw Enemy */
       glPushMatrix();
       glTranslatef(enemy_x,enemy_y,enemy_z);
       glCallList(enemies[CUBE_ENEMY].alive);
       glPopMatrix();

       glDisable(GL_TEXTURE_2D);
       glDisable(GL_LIGHTING);

       
       if (damage.displaying) {
	  
	  printf("DAMAGE\n");
#if 0	  
	  glColor3f(0,0,0);
	  glRasterPos3f(damage.x,damage.y,damage.z+3);
	  texture_put_string(damage.string);
	  
	  glColor3f(damage.r,damage.g,damage.b);
	  glRasterPos3f(damage.x,damage.y,damage.z+3);

	  vmwGLString(damage.string,font);
#endif
	  glPushMatrix();
	  glTranslatef(damage.x,damage.y,damage.z+3);
	  texture_put_string(damage.string);
	  glPopMatrix();
	  
	  if (current_msecs>damage.timeout) {
	     damage.displaying=0;
	  }	  
       }
       
       
       
       if (message.displaying) {

           	  
	  
	  texture_put_string(message.string);
	  
	  if (current_msecs>message.timeout) {
	     message.displaying=0;
	  }
	  reshape(gs->xsize,gs->ysize);
       }
       
       
       if (!update_bottom_bar) glDisable(GL_SCISSOR_TEST);
       
       if (update_bottom_bar) {
             /* display bottom bar */
          glDisable(GL_TEXTURE_2D);
          glDisable(GL_LIGHTING);
          glMatrixMode(GL_PROJECTION);
          glLoadIdentity();
          gluOrtho2D(0,320,0,200);
          glMatrixMode(GL_MODELVIEW);
          glLoadIdentity();
	  
	     /* clear bottom part */
          glColor3f(0.0,0.0,0.0);
          glBegin(GL_QUADS);
             glNormal3f(0,0,1);
             glVertex3f(0,0,-0.1);
             glVertex3f(320,0,-0.1);
             glVertex3f(320,50,-0.1);
             glVertex3f(0,50,-0.1);
          glEnd();
             /* Draw dividing line */
          glColor3f(1.0,1.0,0.0);
          glBegin(GL_LINES);
             glVertex3f(160,50,0);
             glVertex3f(160,0,0);
          glEnd();

	     /* Attack menu if appropriate */
          if (game_state==YOU_ATTACK) {
             if (gs->anger==9) {
                putMenuOption(20,30,"SPECIAL",0,position,0);
	     }
             else {
	        putMenuOption(20,30,"ATTACK",0,position,0);
	     }
             putMenuOption(20,20,"DEFEND",1,position,0);
             putMenuOption(20,10,"USE ITEM",2,position,0);
             putMenuOption(20,0,"RUN AWAY",3,position,0);
	  }
       
	     /* Right hand part */
          glColor3f(0.0,0.0,1.0);
          glRasterPos3f(165,30,0);
          vmwGLString("LEONARD",font);
       
          if ((gs->health/gs->health_total)<0.25) {
	     glColor3f(1.0,1.0,0.0);
          }
          else if ((gs->health/gs->health_total)<0.1) {
	     glColor3f(1.0,0.0,0.0);
          }
          else {
	     glColor3f(0.0,1.0,0.0);
	  }
          sprintf(temp_string,"HEALTH: %d/%d",gs->health,gs->health_total);
          glRasterPos3f(170,20,0);
          vmwGLString(temp_string,font);
	  
          sprintf(temp_string,"ANGER:  %d",gs->anger);       
          glColor3f(1.0,1.0,1.0);
          glRasterPos3f(170,10,0);
          vmwGLString(temp_string,font);

	  sprintf(temp_string,"SPEED:  x%.1f",gs->speed);
          glColor3f(1.0,1.0,1.0);
          glRasterPos3f(170,0,0);
          vmwGLString(temp_string,font);
          reshape(gs->xsize,gs->ysize);	  
	  
	  update_bottom_bar=0;
       }
       
   

    
          /* Flush it out to the device */
       glFlush();
       SDL_GL_SwapBuffers();

       glDisable(GL_LIGHTING);
       glDisable(GL_TEXTURE_2D);



/* Emulate low frame-rates */
//usleep(100000); 
    }
    return 1;
}
