/* Do a fancy 3d "VMW Software Productions Logo */
/* It looks cool.  I tried to do this in Pascal many years ago */
/* for the paintpro program, but could never get what I wanted */

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  /* usleep() */
#include <math.h>

#include "vmw_texture.h"
#include "vmw_glfont.h"

#include "keyboard.h"

extern int use_lighting;
extern int show_fps;

extern GLubyte *font;

void opener(int xsize, int ysize) {

    int scale;
    int frames=0,keyspressed=0;
    int triangle,done=0,original_msecs=0,current_msecs=0;
    float time_passed,i;
    char alpha;
   
   
    GLfloat light_position[]={0.0,0.0,10.0,0.0
    };
   
    GLfloat lmodel_ambient[]={0.9,0.9,0.9,1.0
    };
   
    GLfloat white_light[]={1.0,1.0,1.0,1.0
    };
   

    GLfloat red_material[2][4]={
	 {0.2,0.0,0.0,1.0},  /* Ambient */
         {0.9,0.1,0.1,1.0}   /* Diffuse */
    };
   
    GLfloat green_material[2][4]={
   	 {0.0,0.2,0.0,1.0},  /* Ambient */
         {0.1,0.9,0.1,1.0}   /* Diffuse */
    };
   
    GLfloat blue_material[2][4]={
   	 {0.0,0.0,0.2,1.0},  /* Ambient */
         {0.1,0.1,0.9,1.0}   /* Diffuse */
    };
   
    GLfloat no_mat[]={0.0,0.0,0.0,1.0
    };
    
    GLfloat no_shiny[]={0.0
    };
   

    scale=xsize/320;
    if (scale<=1) scale=1;
    else (scale=2);
   
       /* Look in the right direction */
    glLoadIdentity();
    gluLookAt(-0.00,0.0,15.0,
	     0.0,0.0,0.0,
	     0.0,1.0,1.0);
   
       /* Setup triangle display list */
    triangle=glGenLists(1);
    glNewList(triangle,GL_COMPILE);

       /* Front */
    glBegin(GL_TRIANGLES);
       glNormal3f(0.0,0.0,1.0);
       glVertex3f(-2.0,2.0,0.5);
       glVertex3f( 2.0,2.0,0.5);
       glVertex3f( 0.0,-2.0,0.5);
    glEnd();
   
       /* Sides */
    glBegin(GL_QUADS);
       glNormal3f(0.0,1.0,0.0);
       glVertex3f(-2.0, 2.0, 0.5);
       glVertex3f(-2.0, 2.0,-0.5);
       glVertex3f( 2.0, 2.0,-0.5);
       glVertex3f( 2.0, 2.0, 0.5);
   
   
       glNormal3f( 1.4142,-1.4142,0.0);
       glVertex3f( 2.0, 2.0, 0.5);
       glVertex3f( 2.0, 2.0,-0.5);
       glVertex3f( 0.0,-2.0,-0.5);
       glVertex3f( 0.0,-2.0, 0.5);
   
      glNormal3f(-1.4142,-1.4142,0.0);
      glVertex3f( 0.0,-2.0, 0.5);
      glVertex3f( 0.0,-2.0,-0.5);
      glVertex3f(-2.0, 2.0,-0.5);
      glVertex3f(-2.0, 2.0, 0.5);
    glEnd();
   
       /* Back */  
    glBegin(GL_TRIANGLES);
       glNormal3f(0.0,0.0,-1.0);
       glVertex3f(-2.0,  2.0, -0.5);
       glVertex3f( 2.0,  2.0, -0.5);
       glVertex3f( 0.0, -2.0, -0.5);
    glEnd();

    glEndList();


    if (use_lighting) {
       glLightfv(GL_LIGHT0, GL_POSITION, light_position);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
       glLightfv(GL_LIGHT0, GL_SPECULAR,white_light);

/*   
   glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
   glLightfv(GL_LIGHT1, GL_SPECULAR,white_light);
*/  
   
 
       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   
       glEnable(GL_LIGHTING);
   
       glEnable(GL_LIGHT0);
    }
   
    glEnable(GL_DEPTH_TEST);
   

       /* Attempt to calculate FPS */

    original_msecs=SDL_GetTicks();
    i=180;
#define TIME_TO_TAKE 3.0   
    while (!done) {
         /* hack! why does my machine need this!?! */
       usleep(1);
       current_msecs=SDL_GetTicks();

       if (show_fps) {
          frames++;
          if (frames%20==0) {
             printf("FPS=%f\n",((float) frames)/((current_msecs-original_msecs)/1000.0));
	  }
       }

       time_passed=((float)(current_msecs-original_msecs))/1000.0;
//       printf("%.2f\n",time_passed);
       i=180+(time_passed*(180.0/TIME_TO_TAKE));
       if (i>360.0) i=360.0;
       
//       printf("%i %i %f %f\n",current_msecs,original_msecs,time_passed,i);
       
       if (time_passed>TIME_TO_TAKE) done=1;

       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
          /* Red */
       glColor3f(1.0,0.0,0.0);
       glMaterialfv(GL_FRONT,GL_AMBIENT,  red_material[0]);
       glMaterialfv(GL_FRONT,GL_DIFFUSE, red_material[1]);
       glMaterialfv(GL_FRONT,GL_SPECULAR, no_mat);
       glMaterialfv(GL_FRONT,GL_SHININESS, no_shiny);
       glMaterialfv(GL_FRONT,GL_EMISSION, no_mat);
      
       glPushMatrix();
       glTranslatef(-4 - ((360.0-i)/18.0),0,0.0);
       glRotatef(i,1,1,1);
       glCallList(triangle);
       glPopMatrix();
      
          /* Blue */
       glColor3f(0.0,0.0,1.0);
       glMaterialfv(GL_FRONT,GL_AMBIENT, blue_material[0]);
       glMaterialfv(GL_FRONT,GL_DIFFUSE, blue_material[1]);
       glMaterialfv(GL_FRONT,GL_SPECULAR, no_mat);
       glMaterialfv(GL_FRONT,GL_SHININESS, no_shiny);
       glMaterialfv(GL_FRONT,GL_EMISSION, no_mat);
      
       glPushMatrix();
       glTranslatef(0,((360.0-i)/18.0),0.0);
       glRotatef(i,1,1,1);      
       glCallList(triangle);
       glPopMatrix();
       
       glPushMatrix();
       glTranslatef(4+((360.0-i)/18.0),0+((360.0-i)/18.0),0.0);
       glRotatef(i,1,1,1);      
       glCallList(triangle);
       glPopMatrix();
       
          /* Green */
       glColor3f(0.0,0.0,1.0);
       glMaterialfv(GL_FRONT,GL_AMBIENT, green_material[0]);
       glMaterialfv(GL_FRONT,GL_DIFFUSE, green_material[1]);
       glMaterialfv(GL_FRONT,GL_SPECULAR, no_mat);
       glMaterialfv(GL_FRONT,GL_SHININESS, no_shiny);
       glMaterialfv(GL_FRONT,GL_EMISSION, no_mat);
      
       glPushMatrix();
       glTranslatef(-2,-((360.0-i)/18.0),0.0);
       glRotatef(180,1,0,0);
       glRotatef(i,1,1,1);      
       glCallList(triangle);
       glPopMatrix();
       
       glPushMatrix();
       glTranslatef(2+((360.0-i)/18.0),-((360.0-i)/18.0),0.0);
       glRotatef(180,1,0,0);
       glRotatef(i,1,1,1);      
       glCallList(triangle);
       glPopMatrix();
            
       glFlush();
       SDL_GL_SwapBuffers();

    }

   
    if (use_lighting) {
       glDisable(GL_LIGHTING);
    }
   
    glDisable(GL_LIGHTING);
    glViewport(0,0,xsize,ysize);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,320,0,200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   
    glColor3f(1.0,1.0,1.0);

    glRasterPos3f(60,50,0);
   
    vmwGLString("A VMW SOFTWARE PRODUCTION",font);
   
    glFlush();
    SDL_GL_SwapBuffers();
   
    done=0;

       /* cleak keyboard buffer */
    keyspressed=check_keyboard(&alpha,1);
   
    original_msecs=SDL_GetTicks();
   
       /* Wait 4 seconds or until keypressed */
    while( ((SDL_GetTicks()-original_msecs)<4000) && (!done)) {

       keyspressed=check_keyboard(&alpha,0);
       
       if (keyspressed) {
	  done=1;
       }
       
          /* sleep so we don't use 100% of CPU */
       usleep(100);
    }
   
    /* add code to pause for a few minutes here */
    /* plus play some music */

       /* Don't need this anymore? */
    glDeleteLists(triangle,1);
}
