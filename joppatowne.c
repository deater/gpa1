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

#include "game_state.h"

extern int use_lighting;
extern int show_fps;

GLfloat light_position[]={5.0,5.0,100.0,0.0};
GLfloat lmodel_ambient[]={0.9,0.9,0.9,1.0};
GLfloat white_light[]={1.0,1.0,1.0,1.0};

int do_jtowne(game_state_type *gs) {

    char key_alpha;
    int frames=0,new_msecs,old_msecs,fps_msecs=0,old_fps_msecs=0;
    int keyspressed;
	double scale;

       /* Init screen and keyboard */
    reshape(gs->xsize,gs->ysize);
    check_keyboard(&key_alpha,1);

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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLoadIdentity();
    gluLookAt(0,-10,10,
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
        GLfloat default_d[]={   0.8,0.8,0.8,1.0};
	GLfloat default_s[]={0.0,0.0,0.0,1.0};
	GLfloat default_e[]={0.0,0.0,0.0,1.0
	};

        glMaterialfv(GL_FRONT,GL_AMBIENT,default_a);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,default_d);
	glMaterialfv(GL_FRONT,GL_SPECULAR,default_s);
	glMaterialfv(GL_FRONT,GL_EMISSION,default_e);
     }

   glEnable(GL_TEXTURE_2D);

   glPushMatrix();

   glTranslatef(-5,-5,0);
   glRotatef(45,0,0,1);
   glRotatef(90,1,0,0);

   glCallList(guinea_pigs[LEONARD]);
   glPopMatrix();

   glPushMatrix();
          glTranslatef(5,5,0);
   glRotatef(225,0,0,1);
   glRotatef(90,1,0,0);

   glCallList(guinea_pigs[OLD_GREY]);
   glPopMatrix();

//       glBegin(GL_QUADS);
//       glVertex3f(-5,-5,0);
//              glVertex3f(5,-5,0);
//              glVertex3f(5,5,0);
//              glVertex3f(-5,5,0);
//       glEnd();
  
    glScalef(0.5,0.5,0.5);
    
    glPushMatrix();
    glTranslatef(-15,0,12);   
    texture_put_string("HELLO, WELCOME TO JOPPATOWNE");
    glPopMatrix();
    glTranslatef(-15,0,11);
    texture_put_string("UNFORTUNATELY WE ARE NOT FINISHED YET");
       
       
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
