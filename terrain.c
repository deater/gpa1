#include <GL/gl.h>
#include <GL/glu.h>

#include "terrain.h"
#include "textures.h"
#include "matrix_math.h"

extern GLuint terrain[8];
extern GLuint textures[12];

void setup_terrain(void) {

   float normalx,normaly,normalz;
   
   terrain[GRASS_TERRAIN]=glGenLists(1);
   glNewList(terrain[GRASS_TERRAIN],GL_COMPILE);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,textures[GRASS_TEXTURE]);
   
   glBegin(GL_QUADS);
      glNormal3f(0.0,0.0,1.0);
      glTexCoord2f(0.0,0.0);
      glVertex3f(-2.0,-2.0,0.0);
   
      glTexCoord2f(1.0,0.0);
      glVertex3f(2.0,-2.0,0.0);
   
      glTexCoord2f(1.0,1.0);
      glVertex3f(2.0,2.0,0.0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(-2.0,2.0,0.0);
   glEnd();
   glDisable(GL_TEXTURE_2D);
   
   glEndList();

   
    terrain[OCEAN_TERRAIN]=glGenLists(1);
    glNewList(terrain[OCEAN_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[OCEAN_TEXTURE]);
   
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,-0.25);
    glEnd();
    glDisable(GL_TEXTURE_2D);
   
    glEndList();

   
    terrain[MOUNTAIN_TERRAIN]=glGenLists(1);
    glNewList(terrain[MOUNTAIN_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[MOUNTAIN_TEXTURE]);
   
    glBegin(GL_TRIANGLES);
   
          /* Face 1 */

       calculate_normal(-2.0,2.0,0.0,
			-2.0,-2.0,0.0,
			0.0,0.0,4.0,
			&normalx,&normaly,&normalz);
       glNormal3f(normalx,normaly,normalz);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2.0,-2.0,0.0);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,0.0,4.0);
   
          /* Face 2 */
   
       calculate_normal(-2.0,-2.0,0.0,
			2.0,-2.0,0.0,
			0.0,0.0,4.0,
			&normalx,&normaly,&normalz);
       glNormal3f(normalx,normaly,normalz);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,0.0);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,0.0,4.0);
   
          /* Face 3 */
   
      calculate_normal(2.0,-2.0,0.0,
			2.0,2.0,0.0,
			0.0,0.0,4.0,
			&normalx,&normaly,&normalz);
       glNormal3f(normalx,normaly,normalz);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(2.0,-2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,2.0,0.0);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,0.0,4.0);
   
          /* Face 4 */
   
          calculate_normal(2.0,2.0,0.0,
			-2.0,2.0,0.0,
			0.0,0.0,4.0,
			&normalx,&normaly,&normalz);
       glNormal3f(normalx,normaly,normalz);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(2.0,2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2.0,2.0,0.0);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,0.0,4.0);
   
   
    glEnd();
    glDisable(GL_TEXTURE_2D);
   
    glEndList();

}
   
