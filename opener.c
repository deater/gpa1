#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vmw_texture.h"
#include "vmw_glfont.h"

#define PI 3.141592653589793238462643383279502884197169399
  

extern int use_textures;
extern int use_lighting;

extern GLubyte *font;

void opener() {

    int i,frames=0,msecs=0,startmsecs=0;
    int triangle;
   
   
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
    startmsecs=SDL_GetTicks();

   
    for(i=180;i<361;i++) {
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
      
       frames++;

       if (frames%10==0) {
	  msecs=SDL_GetTicks();
          printf("FPS=%f\n",((float) frames)/((msecs-startmsecs)/1000.0));
       }
    }

   
    if (use_lighting) {
       glDisable(GL_LIGHTING);
    }
   
    glColor3f(1.0,1.0,1.0);

    glRasterPos3f(-2.45,-1.5,10);
   
    vmwGLString("A VMW SOFTWARE PRODUCTION",font,16,32,2);
   
    glFlush();
    SDL_GL_SwapBuffers();
   
    /* add code to pause for a few minutes here */
    /* plus play some music */

       /* Don't need this anymore? */
    glDeleteLists(triangle,1);
}
