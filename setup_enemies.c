#include <GL/gl.h>
#include <GL/glu.h>

#include "textures.h"
#include "setup_enemies.h"

enemy_list_t enemies[NUM_ENEMIES];

int setup_robopig(int green) {
#if 0   
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   
   glPushMatrix();

   
   glTranslatef(pigx,pigy,pigz);
   glRotatef(direction,0.0,0.0,1.0);
   
   glBindTexture(GL_TEXTURE_2D,texName[0]);
   
   
      /* Back */
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,1.0,-1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(-2.0,1.0,1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(-2.0,-1.0,1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,-1.0,-1.0);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,texName[1]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,1.0,-1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,1.0,-1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,1.0,1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,1.0,1.0);

   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,1.0,1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,1.0,1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,-1.0,1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,-1.0,1.0);

   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,-1.0,1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,-1.0,1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,-1.0,-1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,-1.0,-1.0);

   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,-1.0,-1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,-1.0,-1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,1.0,-1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,1.0,-1.0);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,texName[2]);
   glBegin(GL_QUADS);
   
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,1.0,-1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(2.0,1.0,1.0);
   glTexCoord2f(0.0, 0.0); glVertex3f(2.0,-1.0,1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,-1.0,-1.0);
   
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
#endif 
   return 0;
  
}

GLuint setup_cube(int green) {
       
    GLuint display_list;
   
    display_list=glGenLists(1);
    glNewList(display_list,GL_COMPILE);
   
          /* Draw CUBE */
    glEnable(GL_TEXTURE_2D);
    
    if (green) { 
       glBindTexture(GL_TEXTURE_2D,textures[DISINTEGRATE_TEXTURE]);
    }
    else {
       glBindTexture(GL_TEXTURE_2D,textures[ARCTIC_ROOF_TEXTURE]);
    }
    
    glBegin(GL_QUADS);

          /* TOP */
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2,-2,2);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2,-2,2);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2,2,2);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2,2,2);
   
             /* RIGHT */
       glNormal3f(1.0,0.0,0.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(2,-2,-2);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2,2,-2);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2,2,2);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(2,-2,2);
   
             /* FAR */
       glNormal3f(0.0,1.0,0.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(2,2,-2);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2,2,-2);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(-2,2,2);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(2,2,2);
   
             /* LEFT */
       glNormal3f(-1.0,0.0,0.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2,2,-2);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2,-2,-2);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(-2,-2,2);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2,2,2);
   
             /* NEAR */
       glNormal3f(0.0,-1.0,0.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2,-2,-2);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2,-2,-2);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2,-2,2);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2,-2,2);
   
             /* BOTTOM */
       glNormal3f(0.0,0.0,-1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2,-2,-2);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2,-2,-2);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2,2,-2);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2,2,-2);
   
    glEnd();
   
   
    glDisable(GL_TEXTURE_2D);
    glEndList();
   
    return display_list;
}


void setup_enemies(void) {
   
   enemies[ROBO_PIG_ENEMY].alive=setup_robopig(0);
   enemies[ROBO_PIG_ENEMY].dead=setup_robopig(1);
 
   enemies[CUBE_ENEMY].alive=setup_cube(0);
   enemies[CUBE_ENEMY].dead=setup_cube(1);
}
