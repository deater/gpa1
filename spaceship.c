#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vmw_texture.h"
#include "vmw_glfont.h"

#include "matrix_math.h"

#include "textures.h"

#define PI 3.141592653589793238462643383279502884197169399

extern int use_lighting;
extern int use_textures;

extern GLuint textures[];

GLuint spaceships[2];

GLuint setup_spaceship(int engines_on) {
      
    GLuint display_list;
   
   
    display_list=glGenLists(1);
    glNewList(display_list,GL_COMPILE);
   
       /* Draw hull */
       
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[SS_LEFT]);
    glColor3f(0.80,0.80,0.80);
 
    glBegin(GL_TRIANGLES);   
       glNormal3f(0,1,0);
	  
       glTexCoord2f(1.0,1.0);	  
       glVertex3f(-1.5,0.75,-0.75);
          
       glTexCoord2d(0.0,1.0);
       glVertex3f(1.5,0.75,-0.75);

       glTexCoord2d(1.0,0.0);
       glVertex3f(-1.5,0.75,0.75);
    glEnd();
   
    glBindTexture(GL_TEXTURE_2D,textures[SS_TOP]);
    glBegin(GL_QUADS);  
          /* top */
       glNormal3f(0.5547,0,0.83205);
       
       glTexCoord2f(0.0,0.0);
       glVertex3f(-1.5,0.75,0.75);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(1.5,0.75,-0.75);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(1.5,-0.75,-0.75);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-1.5,-0.75,0.75);
    glEnd();
       
    glBindTexture(GL_TEXTURE_2D,textures[SS_BACK]);
    glBegin(GL_QUADS);
           /* back */   
       glNormal3f(-1,0,0);
       
       glTexCoord2f(0.0,1.0);
       glVertex3f(-1.5,-0.75,-0.75);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(-1.5,0.75,-0.75);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-1.5,0.75,0.75);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(-1.5,-0.75,0.75);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,textures[SS_BOTTOM]);
   glBegin(GL_QUADS);
          /* bottom */
       glNormal3f(0,0,-1);
       
       glTexCoord2f(0.0,0.0);
       glVertex3f(-1.5,-0.75,-0.75);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(1.5,-0.75,-0.75);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(1.5,0.75,-0.75);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-1.5,0.75,-0.75);

    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[SS_RIGHT]);
    glBegin(GL_TRIANGLES);   
       glNormal3f(0,-1,0);
	  
       glTexCoord2f(0.0,1.0);	  
       glVertex3f(-1.5,-0.75,-.75);
          
       glTexCoord2d(0.0,0.0);
       glVertex3f(-1.5,-0.75,0.75);

       glTexCoord2d(1.0,1.0);
       glVertex3f(1.5,-0.75,-.75);
   
    glEnd();

    if (engines_on) {
       glBindTexture(GL_TEXTURE_2D,textures[SS_THRUST]);
    }
    else {
       glBindTexture(GL_TEXTURE_2D,textures[SS_NOTHRUST]);
    }

       /* Flame things */
    glBegin(GL_QUADS);
       glNormal3f(-1.0,0.0,0.0);
   
       glTexCoord2f(0,0);
       glVertex3f(-1.5,0.75,0.5);
   
       glTexCoord2f(1,0);
       glVertex3f(-1.5,1.0,0.5);
   
       glTexCoord2f(1,1);
       glVertex3f(-1.5,1.0,0.75);
   
       glTexCoord2f(0,1);
       glVertex3f(-1.5,0.75,0.75);

   
       glTexCoord2f(0,0);
       glVertex3f(-1.5,-1.0,0.5);
   
       glTexCoord2f(1,0);
       glVertex3f(-1.5,-0.75,0.5);
   
       glTexCoord2f(1,1);
       glVertex3f(-1.5,-0.75,0.75);
   
       glTexCoord2f(0,1);
       glVertex3f(-1.5,-1.0,0.75);

    glEnd();


    glBindTexture(GL_TEXTURE_2D,textures[SS_GRAY]);
       /* triangular thingies on left */    
    glBegin(GL_QUADS);
       glNormal3f(0,0,-1);
       glTexCoord2f(0,0);
       glVertex3f(-1.5,-0.75,0.5);
   
       glTexCoord2f(1,0);
       glVertex3f(-1.0,-0.75,0.5);
   
       glTexCoord2f(1,1);
       glVertex3f(-1.0,-1.0,0.5);
   
       glTexCoord2f(0,1);
       glVertex3f(-1.5,-1.0,0.5);
   
       glNormal3f(0.5547,0,0.83205);
       glTexCoord2f(0,0);
       glVertex3f(-1.5,-0.75,0.75);
   
       glTexCoord2f(1,0);
       glVertex3f(-1.0,-0.75,0.5);
   
       glTexCoord2f(1,1);
       glVertex3f(-1.0,-1.0,0.5);
   
       glTexCoord2f(0,1);
       glVertex3f(-1.5,-1.0,0.75);
   glEnd();
   
   glBegin(GL_TRIANGLES);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(-1.5,-1.0,0.5);
   
      glTexCoord2f(1,0);
      glVertex3f(-1.0,-1.0,0.5);
   
      glTexCoord2f(0,1);
      glVertex3f(-1.5,-1.0,0.75);
   
   glEnd();
   
          /* triangular thingies on right */    
    glBegin(GL_QUADS);
       glNormal3f(0,0,-1);
       glTexCoord2f(0,0);
       glVertex3f(-1.5,0.75,0.5);
   
       glTexCoord2f(1,0);
       glVertex3f(-1.0,0.75,0.5);
   
       glTexCoord2f(1,1);
       glVertex3f(-1.0,1.0,0.5);
   
       glTexCoord2f(0,1);
       glVertex3f(-1.5,1.0,0.5);
   
       glNormal3f(0.5547,0,0.83205);
       glTexCoord2f(0,0);
       glVertex3f(-1.5,0.75,0.75);
   
       glTexCoord2f(1,0);
       glVertex3f(-1.0,0.75,0.5);
   
       glTexCoord2f(1,1);
       glVertex3f(-1.0,1.0,0.5);
   
       glTexCoord2f(0,1);
       glVertex3f(-1.5,1.0,0.75);
   glEnd();
   
   glBegin(GL_TRIANGLES);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(-1.5,1.0,0.5);
   
      glTexCoord2f(1,0);
      glVertex3f(-1.0,1.0,0.5);
   
      glTexCoord2f(0,1);
      glVertex3f(-1.5,1.0,0.75);
   
   glEnd();
   
   
    
    glDisable(GL_TEXTURE_2D);
    glEndList();
   
    return display_list;
}
   
