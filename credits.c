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
#include "keyboard.h"

#include "guinea_pig.h"
#include "tfv.h"


#include "game_state.h"

#define PI 3.141592653589793238462643383279502884197169399

extern int use_lighting;
extern int show_fps;

int do_credits(game_state_type *gs) {

    char key_alpha;
    int frames=0,new_msecs,old_msecs,fps_msecs=0,old_fps_msecs=0;
    int keyspressed;
    float scale,camerax=10,cameray=-10,cameraz=10,camera_direction=0;
    int right_elbow=0;

	GLfloat light_position[]={5.0,5.0,100.0,0.0};
	GLfloat lmodel_ambient[]={0.9,0.9,0.9,1.0};
	GLfloat white_light[]={1.0,1.0,1.0,1.0};


    printf("ENTERING DO CREDITS\n"); fflush(stdout);
   
       /* Init screen and keyboard */
    reshape(gs->xsize,gs->ysize);
    check_keyboard(&key_alpha,1);

    printf("ABOUT TO SETUP TFV\n"); fflush(stdout);
   
    setup_tfv();
    setup_tfe();
   
    printf("ABOUT TO ENTER MAIN LOOP\n"); fflush(stdout);
   
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

       if (keyspressed&MENU_PRESSED) {
          return 0;	  
       }

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
                     if (keyspressed&UP_PRESSED) {
	                cameraz+=0.5;
	      }
                            if (keyspressed&DOWN_PRESSED) {
	                cameraz-=0.5;
	      }
       

       if (keyspressed&RIGHT_PRESSED) {
	  right_elbow+=10;
       }
   
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLoadIdentity();
    gluLookAt(camerax,cameray,cameraz,
	     0.0,0.0,0.0,
	     0.0,0.0,1.0);
   

      glLightfv(GL_LIGHT0, GL_POSITION, light_position);

      glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
      glLightfv(GL_LIGHT0, GL_SPECULAR,white_light);
      
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);

     {
	GLfloat default_a[]={0.6,0.6,0.6,1.0};
        GLfloat default_d[]={0.8,0.8,0.8,1.0};
	GLfloat default_s[]={0.0,0.0,0.0,1.0};
	GLfloat default_e[]={0.0,0.0,0.0,1.0
	};
	
        glMaterialfv(GL_FRONT,GL_AMBIENT,default_a);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,default_d);
	glMaterialfv(GL_FRONT,GL_SPECULAR,default_s);
	glMaterialfv(GL_FRONT,GL_EMISSION,default_e);
     }

   glBegin(GL_QUADS);
       glVertex3f(-5,-5,0);
       glVertex3f(5,-5,0);
       glVertex3f(5,5,0);
       glVertex3f(-5,5,0);
       
       glVertex3f(-5,5,0);
       glVertex3f(5,5,0);
       glVertex3f(5,5,5);
       glVertex3f(-5,5,5);
       
       glVertex3f(-5,-5,0);
       glVertex3f(-5,5,0);
       glVertex3f(-5,5,5);
       glVertex3f(-5,-5,5);
   glEnd();
       
   glEnable(GL_TEXTURE_2D);

   glPushMatrix();

   glTranslatef(0,0,6.5);
   glRotatef(90,0,1,0);

   draw_tfv(0,0,0,0,
	    0,right_elbow,0,
	    0,0,0,
	    0,
	    1);

   draw_tfv(0,0,0,0,
	    0,right_elbow,0,
	    0,0,0,
	    0,
	    1);

   glTranslatef(0,2.5,0);

   draw_tfv(0,0,0,0,
	    0,right_elbow,0,
	    0,0,0,
	    0,
	    0);

   glPopMatrix();

       
       
       /* Flush it out to the device */
    glFlush();
    SDL_GL_SwapBuffers();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);


/* Emulate low frame-rates */
//usleep(100000); 
    }
	(void) scale;
    	return 1;
}
