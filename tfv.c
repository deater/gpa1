#include <GL/gl.h>
#include <GL/glu.h>

#include "textures.h"

#include "matrix_math.h"

#define TFV_HEAD         0
#define TFV_TORSO        1
#define TFV_UPPER_ARM    2
#define TFV_LOWER_ARM    3
#define TFV_WAIST        4
#define TFV_UPPER_LEG    5
#define TFV_LOWER_LEG    6
#define TFV_SWORD        7
#define TFV_SIDEBURNS    8

GLuint tfv_parts[12];
GLuint tfe_parts[12];


int make_rectangle(float x, float y, float z, int text1, int text2, int text3,
		                              int text4, int text5, int text6) {
   
       /* left end */
    glBindTexture(GL_TEXTURE_2D,textures[text1]);
    glBegin(GL_QUADS);
       glNormal3f(-1,0,0);
       glTexCoord2f(0,0);
       glVertex3f(0,y/2,-z/2);
   
       glTexCoord2f(1,0);
       glVertex3f(0,-y/2,-z/2);
   
       glTexCoord2f(1,1);
       glVertex3f(0,-y/2,z/2);
   
       glTexCoord2f(0,1);
       glVertex3f(0,y/2,z/2);
    glEnd();
   
          /* front */
    glBindTexture(GL_TEXTURE_2D,textures[text2]);
    glBegin(GL_QUADS);
       glNormal3f(0,-1,0);
       glTexCoord2f(0,0);
       glVertex3f(0,-y/2,-z/2);
   
       glTexCoord2f(1,0);
       glVertex3f(x,-y/2,-z/2);
   
       glTexCoord2f(1,1);
       glVertex3f(x,-y/2,z/2);
   
       glTexCoord2f(0,1);
       glVertex3f(0,-y/2,z/2);
    glEnd();
   
             /* bottom */
    glBindTexture(GL_TEXTURE_2D,textures[text3]);
    glBegin(GL_QUADS);
       glNormal3f(0,0,-1);
       glTexCoord2f(0,0);
       glVertex3f(0,y/2,-z/2);
   
       glTexCoord2f(1,0);
       glVertex3f(x,y/2,-z/2);
   
       glTexCoord2f(1,1);
       glVertex3f(x,-y/2,-z/2);
   
       glTexCoord2f(0,1);
       glVertex3f(0,-y/2,-z/2);
    glEnd();
   
              /* back */
    glBindTexture(GL_TEXTURE_2D,textures[text4]);
    glBegin(GL_QUADS);
       glNormal3f(0,1,0);
       glTexCoord2f(0,0);
       glVertex3f(x,y/2,-z/2);
   
       glTexCoord2f(1,0);
       glVertex3f(0,y/2,-z/2);
   
       glTexCoord2f(1,1);
       glVertex3f(0,y/2,z/2);
   
       glTexCoord2f(0,1);
       glVertex3f(x,y/2,z/2);
    glEnd();
   
              /* top */
    glBindTexture(GL_TEXTURE_2D,textures[text5]);
    glBegin(GL_QUADS);
       glNormal3f(0,0,1);
       glTexCoord2f(0,0);
       glVertex3f(0,-y/2,z/2);
   
       glTexCoord2f(1,0);
       glVertex3f(x,-y/2,z/2);
   
       glTexCoord2f(1,1);
       glVertex3f(x,y/2,z/2);
   
       glTexCoord2f(0,1);
       glVertex3f(0,y/2,z/2);
    glEnd();
   
   
          /* right end */
    glBindTexture(GL_TEXTURE_2D,textures[text6]);
    glBegin(GL_QUADS);
       glNormal3f(1,0,0);
       glTexCoord2f(0,0);
       glVertex3f(x,-y/2,-z/2);
   
       glTexCoord2f(1,0);
       glVertex3f(x,y/2,-z/2);
   
       glTexCoord2f(1,1);
       glVertex3f(x,y/2,z/2);
   
       glTexCoord2f(0,1);
       glVertex3f(x,-y/2,z/2);
    glEnd();

    return 2131978;
}



int setup_tfv(void) {
   
       /* SIDEBURNS */
   tfv_parts[TFV_SIDEBURNS]=glGenLists(1);
   glNewList(tfv_parts[TFV_SIDEBURNS],GL_COMPILE);
   glBindTexture(GL_TEXTURE_2D,textures[TFV_HAIR_TEXTURE]);  

#define SIDEBURN_THICK 0.1   
#define SIDEBURN_LENGTH 0.75
   
   glBegin(GL_TRIANGLES);
       glNormal3f(0,-1,0);
       glTexCoord2f(0,0);
       glVertex3f(0,0,0);
       glTexCoord2f(1,0);
       glVertex3f(SIDEBURN_LENGTH,0,0);
       glTexCoord2f(1,0.5);
       glVertex3f(SIDEBURN_LENGTH,0,SIDEBURN_THICK);
     
       glNormal3f(0.093865,0.703985,0.703985);
       glTexCoord2f(0,0);
       glVertex3f(0,0,0);
       glTexCoord2f(1,0);
       glVertex3f(SIDEBURN_LENGTH,0,SIDEBURN_THICK);
       glTexCoord2f(1,0.5);
       glVertex3f(SIDEBURN_LENGTH,SIDEBURN_THICK,0);
   
       glNormal3f(0,0,-1);
       glTexCoord2f(0,0);
       glVertex3f(0,0,0);
       glTexCoord2f(1,0);
       glVertex3f(SIDEBURN_LENGTH,0,0);
       glTexCoord2f(1,0.5);
       glVertex3f(SIDEBURN_LENGTH,SIDEBURN_THICK,0);
   
       glNormal3f(1,0,0);
       glTexCoord2f(0,0);
       glVertex3f(SIDEBURN_LENGTH,0,0);
       glTexCoord2f(0.5,0);
       glVertex3f(SIDEBURN_LENGTH,SIDEBURN_THICK,0);
       glTexCoord2f(0,0.5);
       glVertex3f(SIDEBURN_LENGTH,0,SIDEBURN_THICK);
   
   glEnd();
   
   glEndList();
   
       /* HEAD */
   tfv_parts[TFV_HEAD]=glGenLists(1);
   glNewList(tfv_parts[TFV_HEAD],GL_COMPILE);
 
   make_rectangle(1,0.75,0.5,TFV_FLESH_TEXTURE,TFV_RIGHT_EAR_TEXTURE,TFV_HAIR_TEXTURE,
		             TFV_LEFT_EAR_TEXTURE,TFV_FACE_TEXTURE,TFV_FLESH_TEXTURE);
   
                 /* hair */
#define HAIR_HEIGHT 0.25
   glBindTexture(GL_TEXTURE_2D,textures[TFV_HAIR_TEXTURE]);   
  
   glBegin(GL_TRIANGLES);
   
      glNormal3f(0,0,1);
      glTexCoord2f(0,0);
      glVertex3f(0,-0.375,0.25);
      glTexCoord2f(1,0);
      glVertex3f(0,0,0.25);
      glTexCoord2f(1,0.25);
      glVertex3f(-HAIR_HEIGHT,0,0.25);

      glTexCoord2f(0,0);
      glVertex3f(0,0,0.25);
      glTexCoord2f(1,0);
      glVertex3f(0,0.375,0.25);
      glTexCoord2f(1,0.25);
      glVertex3f(-HAIR_HEIGHT,0.375,0.25);
   glEnd();
   
   glBegin(GL_QUADS);
      glNormal3f(0,1,0);
   
      glTexCoord2f(0,0);
      glVertex3f(0,0.375,0.25);
      glTexCoord2f(1,0);
      glVertex3f(0,0.375,-0.25);
      glTexCoord2f(1,0.5);
      glVertex3f(-HAIR_HEIGHT,0.375,-0.25);
      glTexCoord2f(0,0.5);
      glVertex3f(-HAIR_HEIGHT,0.375,0.25);
   
      glTexCoord2f(0,0);
      glVertex3f(0,0,0.25);
      glTexCoord2f(1,0);
      glVertex3f(0,0,-0.25);
      glTexCoord2f(1,0.5);
      glVertex3f(-HAIR_HEIGHT,0,-0.25);
      glTexCoord2f(0,0.5);
      glVertex3f(-HAIR_HEIGHT,0,0.25);
   
   
   glEnd();
   
   glBegin(GL_TRIANGLES);
      glNormal3f(0,0,-1);
      glTexCoord2f(0,0);
      glVertex3f(0,0.375,-0.25);
      glTexCoord2f(1,0);
      glVertex3f(0,0,-0.25);
      glTexCoord2f(0,0.25);
      glVertex3f(-HAIR_HEIGHT,0.375,-0.25);
   
      glTexCoord2f(0,0);
      glVertex3f(0,0,-0.25);
      glTexCoord2f(1,0);
      glVertex3f(0,-0.375,-0.25);
      glTexCoord2f(0,0.25);
      glVertex3f(-HAIR_HEIGHT,0,-0.25);
   glEnd();

   glBegin(GL_QUADS);
      glNormal3f(-0.894,-0.447,0);
   
      glTexCoord2f(0,0);
      glVertex3f(-HAIR_HEIGHT,0.375,0.25);
      glTexCoord2f(1,0);
      glVertex3f(-HAIR_HEIGHT,0.375,-0.25);
      glTexCoord2f(1,1);
      glVertex3f(0,0,-0.25);
      glTexCoord2f(0,1);
      glVertex3f(0,0,0.25);
   
      glTexCoord2f(0,0);
      glVertex3f(-HAIR_HEIGHT,0,0.25);
      glTexCoord2f(1,0);
      glVertex3f(-HAIR_HEIGHT,0,-0.25);
      glTexCoord2f(1,1);
      glVertex3f(0,-0.375,-0.25);
      glTexCoord2f(0,1);
      glVertex3f(0,-0.375,0.25);
   
   
   glEnd();   
   
   
                 /* nose */
#define NOSE_WIDTH  0.1
#define NOSE_LENGTH 0.15
#define NOSE_HEIGHT 0.3
   
   glPushMatrix();
   glTranslatef(0.4,0,0.25);
   glBindTexture(GL_TEXTURE_2D,textures[TFV_FLESH_TEXTURE]);   
   
   glBegin(GL_TRIANGLES);
      glNormal3f(0,-1,0);
   
      glVertex3f((NOSE_HEIGHT/2.0),-(NOSE_WIDTH/2.0),0);
      glVertex3f((NOSE_HEIGHT/2.0),-(NOSE_WIDTH/2.0),NOSE_LENGTH);
      glVertex3f(-(NOSE_HEIGHT/2.0),-(NOSE_WIDTH/2.0),0);
   glEnd();
   
   glBegin(GL_QUADS);
      glNormal3f(1,0,0);
      glVertex3f((NOSE_HEIGHT/2.0),(NOSE_WIDTH/2.0),0);
      glVertex3f((NOSE_HEIGHT/2.0),(NOSE_WIDTH/2.0),NOSE_LENGTH);
      glVertex3f((NOSE_HEIGHT/2.0),-(NOSE_WIDTH/2.0),NOSE_LENGTH);
      glVertex3f((NOSE_HEIGHT/2.0),-(NOSE_WIDTH/2.0),0);
   glEnd();
   
   glBegin(GL_TRIANGLES);
      glNormal3f(0,1,0);
   
      glVertex3f((NOSE_HEIGHT/2.0),(NOSE_WIDTH/2.0),NOSE_LENGTH);
      glVertex3f((NOSE_HEIGHT/2.0),(NOSE_WIDTH/2.0),0);
      glVertex3f(-(NOSE_HEIGHT/2.0),(NOSE_WIDTH/2.0),0);
   glEnd();
   
   glBegin(GL_QUADS);
      glNormal3f(-0.447,0,0.894);
      glVertex3f((NOSE_HEIGHT/2.0),-(NOSE_WIDTH/2.0),NOSE_LENGTH);
      glVertex3f((NOSE_HEIGHT/2.0),(NOSE_WIDTH/2.0),NOSE_LENGTH);
      glVertex3f(-(NOSE_HEIGHT/2.0),(NOSE_WIDTH/2.0),0);
      glVertex3f(-(NOSE_HEIGHT/2.0),-(NOSE_WIDTH/2.0),0);
   glEnd();
   
   glPopMatrix();
                 /* sideburns */

      /* right side */
   glPushMatrix();
      glTranslatef(0,-0.375,0.25);
      glCallList(tfv_parts[TFV_SIDEBURNS]);
      glRotatef(90,1,0,0);
      glCallList(tfv_parts[TFV_SIDEBURNS]);
      glRotatef(90,1,0,0);
      glCallList(tfv_parts[TFV_SIDEBURNS]);
   
   glPopMatrix();
   
         /* left side */
   glPushMatrix();
      glTranslatef(0,0.375,0.25);
      glRotatef(-90,1,0,0);
      glCallList(tfv_parts[TFV_SIDEBURNS]);
      glRotatef(90,1,0,0);
      glCallList(tfv_parts[TFV_SIDEBURNS]);
      glRotatef(90,1,0,0);
      glCallList(tfv_parts[TFV_SIDEBURNS]);
   
   glPopMatrix();
   
                 /* neck */
   glPushMatrix();
   glTranslatef(1,0,0);
   make_rectangle(0.25,0.25,0.25,TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE,
		                 TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE);
   glPopMatrix();
   glEndList();

       /* TORSO */
   tfv_parts[TFV_TORSO]=glGenLists(1);
   glNewList(tfv_parts[TFV_TORSO],GL_COMPILE);
   
   make_rectangle(2,1,0.5,TFV_NAVY_TEXTURE,TFV_NAVY_TEXTURE,TFV_NAVY_TEXTURE,
		          TFV_NAVY_TEXTURE,TFV_NAVY_TEXTURE,TFV_NAVY_TEXTURE);
   glEndList();
   
 
       /* UPPER ARM */
   tfv_parts[TFV_UPPER_ARM]=glGenLists(1);
   glNewList(tfv_parts[TFV_UPPER_ARM],GL_COMPILE);
   make_rectangle(1,0.25,0.25,TFV_NAVY_TEXTURE,TFV_NAVY_TEXTURE,TFV_NAVY_TEXTURE,
		              TFV_NAVY_TEXTURE,TFV_NAVY_TEXTURE,TFV_NAVY_TEXTURE);
   glEndList();
   
       /* LOWER ARM */
   tfv_parts[TFV_LOWER_ARM]=glGenLists(1);
   glNewList(tfv_parts[TFV_LOWER_ARM],GL_COMPILE);
   glPushMatrix();
   make_rectangle(1,0.25,0.25,TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE,
		              TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE);
                        /* hand */
   glTranslatef(1,0,0);
   make_rectangle(0.33,0.33,0.33,TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE,
		                 TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE,TFV_FLESH_TEXTURE);
   glPopMatrix();
   
   glEndList();
   
       /* WAIST */
   tfv_parts[TFV_WAIST]=glGenLists(1);
   glNewList(tfv_parts[TFV_WAIST],GL_COMPILE);
   make_rectangle(0.5,1.0,0.5,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,
		              TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE);
   glEndList();
   
       /* UPPER LEG */
   tfv_parts[TFV_UPPER_LEG]=glGenLists(1);
   glNewList(tfv_parts[TFV_UPPER_LEG],GL_COMPILE);
   make_rectangle(1,0.5,0.5,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,
		              TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE);
   glEndList();
   
       /* LOWER LEG */
   tfv_parts[TFV_LOWER_LEG]=glGenLists(1);
   glNewList(tfv_parts[TFV_LOWER_LEG],GL_COMPILE);
   make_rectangle(1,0.5,0.5,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,
		              TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE);
   glTranslatef(1.0,0,0);
   make_rectangle(0.25,0.5,0.5,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,
		               TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE);
   glTranslatef(0.25,0,0.25);
   make_rectangle(0.5,0.5,1.0,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,
		              TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE);
   
   glEndList();
   

       /* SWORD */
   tfv_parts[TFV_SWORD]=glGenLists(1);
   glNewList(tfv_parts[TFV_SWORD],GL_COMPILE);
      
   make_rectangle(1,0.25,0.25,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,
		              TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE);   
   

   glTranslatef(1,0,0);

   glBindTexture(GL_TEXTURE_2D,textures[TFV_SWORD_TEXTURE]);      
   glBegin(GL_TRIANGLES);
       glNormal3f(0,0,1);
   
       glTexCoord2f(0,0);
       glVertex3f(0,-0.5,0.125);
       glTexCoord2f(1,0.5);
       glVertex3f(1,0,0.125);
       glTexCoord2f(0,1);
       glVertex3f(0,0.5,0.125);
   
   glEnd();
   
   glBegin(GL_QUADS);
       glNormal3f(-1,0,0);
       glTexCoord2f(0,0);
       glVertex3f(0,-0.5,-0.125);
       glTexCoord2f(1,0);
       glVertex3f(0,-0.5,0.125);
       glTexCoord2f(1,1);
       glVertex3f(0,0.5,0.125);
       glTexCoord2f(0,1);
       glVertex3f(0,0.5,-0.125);
   
       glNormal3f(0.447,-0.894,0);
       glTexCoord2f(0,0);
       glVertex3f(0,-0.5,-0.125);
       glTexCoord2f(1,0);
       glVertex3f(0,-0.5,0.125);
       glTexCoord2f(1,1);
       glVertex3f(1,0,0.125);
       glTexCoord2f(0,1);
       glVertex3f(1,0,-0.125);
   
       glNormal3f(0.447,0.894,0);
       glTexCoord2f(0,0);
       glVertex3f(1,0,-0.125);
       glTexCoord2f(1,0);
       glVertex3f(1,0,0.125);
       glTexCoord2f(1,1);
       glVertex3f(0,0.5,0.125);
       glTexCoord2f(0,1);
       glVertex3f(0,0.5,-0.125);
      
   
   glEnd();
   
   glBegin(GL_TRIANGLES);
       glNormal3f(0,0,-1);
   
       glTexCoord2f(1,0);
       glVertex3f(0,-0.5,-0.125);
       glTexCoord2f(1,1);
       glVertex3f(0,0.5,-0.125);
       glTexCoord2f(0,0.5);
       glVertex3f(1,0,-0.125);
   
   glEnd();
   
   
   glTranslatef(1,0,0);
   make_rectangle(0.25,1,0.25,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,
		              TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE);   
   glTranslatef(0.25,0,0);
   make_rectangle(1,0.25,0.25,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,
		              TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE);   
   
   glTranslatef(-0.5,-0.75,0);
   glBindTexture(GL_TEXTURE_2D,textures[TFV_SWORD_ARROWS_TEXTURE]);      
   glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glTexCoord2f(0,0);
      glVertex3f(0.5,0.5,0);
      glTexCoord2f(1,0);
      glVertex3f(0.5,-0.5,0);
      glTexCoord2f(1,1);
      glVertex3f(-0.5,-0.5,0);
      glTexCoord2f(0,1);
      glVertex3f(-0.5,0.5,0);
   glEnd();
   
   glEndList();
   
   return 6798329;
}

int setup_tfe(void) {
   

    float normalx,normaly,normalz;
   
       /* HEAD */
   tfe_parts[TFV_HEAD]=glGenLists(1);
   glNewList(tfe_parts[TFV_HEAD],GL_COMPILE);
 
   make_rectangle(1,0.75,0.5,TFV_HAIR_BLACK_TEXTURE,TFV_RIGHT_EAR2_TEXTURE,TFV_HAIR_BLACK_TEXTURE,
		             TFV_LEFT_EAR2_TEXTURE,TFV_FACE2_TEXTURE,TFV_FLESH2_TEXTURE);
   
                 /* hair */

   glBindTexture(GL_TEXTURE_2D,textures[TFV_HAIR_BLACK_TEXTURE]);   
  
   
   
   glBegin(GL_TRIANGLES);
   
   glEnd();
   
   glBegin(GL_QUADS);
       glNormal3f(1,0,0);
       glTexCoord2f(0,0);
       glVertex3f(1.5,-0.375,-0.75);
       glTexCoord2f(1,0);
       glVertex3f(1.5,0.375,-0.75);
       glTexCoord2f(1,1);
       glVertex3f(0,0.375,-0.25);
       glTexCoord2f(0,1);
       glVertex3f(0,-0.375,-0.25);
  
   glEnd();

   glBegin(GL_TRIANGLES);
        /* her right */
      glVertex3f(1.5,-0.375,-0.75);
      glVertex3f(1.5,-0.75,-0.75);
      glVertex3f(0,-0.375,-0.25);
    
      glVertex3f(1.5,-0.75,-0.75);
      glVertex3f(0,-0.375,-0.1);
      glVertex3f(0,-0.375,-0.25);
   
      glVertex3f(1.5,-0.75,-0.75);
      glVertex3f(1.0,-0.375,-0.25);
      glVertex3f(0,-0.375,-0.1);
   
        /* her left */
      glVertex3f(1.5,0.375,-0.75);
      glVertex3f(1.5,0.75,-0.75);
      glVertex3f(0,0.375,-0.25);
   
      glVertex3f(1.5,0.75,-0.75);
      glVertex3f(0,0.375,-0.1);
      glVertex3f(0,0.375,-0.25);
   
      glVertex3f(1.5,0.75,-0.75);
      glVertex3f(1.0,0.375,-0.25);
      glVertex3f(0,0.375,-0.1);
   glEnd();
    
                 /* Glasses */
   glBegin(GL_LINE_LOOP);
      glVertex3f(0.35,-0.375,0.3);
      glVertex3f(0.35,-0.05,0.3);
      glVertex3f(0.15,-0.05,0.3);
      glVertex3f(0.15,-0.375,0.3);
      
   glEnd();   
   
   glBegin(GL_LINE_LOOP);
      glVertex3f(0.35,0.375,0.3);
      glVertex3f(0.35,0.05,0.3);
      glVertex3f(0.15,0.05,0.3);
      glVertex3f(0.15,0.375,0.3);
      
   glEnd();   
                
   glBegin(GL_LINES);
      glVertex3f(0.2,-0.05,0.3);
      glVertex3f(0.2, 0.05,0.3);
   glEnd();
   
                 /* nose */
#define NOSE_WIDTH_F  0.1
#define NOSE_LENGTH_F 0.1
#define NOSE_HEIGHT_F 0.3
   
   glPushMatrix();
   glTranslatef(0.4,0,0.25);
   glBindTexture(GL_TEXTURE_2D,textures[TFV_FLESH2_TEXTURE]);   
   
   glBegin(GL_TRIANGLES);
      glNormal3f(0,-1,0);
   
      glVertex3f((NOSE_HEIGHT_F/2.0),-(NOSE_WIDTH_F/2.0),0);
      glVertex3f((NOSE_HEIGHT_F/2.0),-(NOSE_WIDTH_F/2.0),NOSE_LENGTH_F);
      glVertex3f(-(NOSE_HEIGHT_F/2.0),-(NOSE_WIDTH_F/2.0),0);
   glEnd();
   
   glBegin(GL_QUADS);
      glNormal3f(1,0,0);
      glVertex3f((NOSE_HEIGHT_F/2.0),(NOSE_WIDTH_F/2.0),0);
      glVertex3f((NOSE_HEIGHT_F/2.0),(NOSE_WIDTH_F/2.0),NOSE_LENGTH_F);
      glVertex3f((NOSE_HEIGHT_F/2.0),-(NOSE_WIDTH_F/2.0),NOSE_LENGTH_F);
      glVertex3f((NOSE_HEIGHT_F/2.0),-(NOSE_WIDTH_F/2.0),0);
   glEnd();
   
   glBegin(GL_TRIANGLES);
      glNormal3f(0,1,0);
   
      glVertex3f((NOSE_HEIGHT_F/2.0),(NOSE_WIDTH_F/2.0),NOSE_LENGTH_F);
      glVertex3f((NOSE_HEIGHT_F/2.0),(NOSE_WIDTH_F/2.0),0);
      glVertex3f(-(NOSE_HEIGHT_F/2.0),(NOSE_WIDTH_F/2.0),0);
   glEnd();
   
   glBegin(GL_QUADS);
   	    calculate_normal( (NOSE_HEIGHT_F/2.0),-(NOSE_WIDTH_F/2.0),NOSE_LENGTH_F,	      
			     (NOSE_HEIGHT_F/2.0),(NOSE_WIDTH_F/2.0),NOSE_LENGTH_F,
			     -(NOSE_HEIGHT_F/2.0),-(NOSE_WIDTH_F/2.0),0,
			     &normalx,&normaly,&normalz);
	 glNormal3f(normalx,normaly,normalz);

      glVertex3f((NOSE_HEIGHT_F/2.0),-(NOSE_WIDTH_F/2.0),NOSE_LENGTH_F);
      glVertex3f((NOSE_HEIGHT_F/2.0),(NOSE_WIDTH_F/2.0),NOSE_LENGTH_F);
      glVertex3f(-(NOSE_HEIGHT_F/2.0),(NOSE_WIDTH_F/2.0),0);
      glVertex3f(-(NOSE_HEIGHT_F/2.0),-(NOSE_WIDTH_F/2.0),0);
   glEnd();
   
   glPopMatrix();
   
                 /* neck */
   glPushMatrix();
   glTranslatef(1,0,0);
   make_rectangle(0.25,0.25,0.25,TFV_FLESH2_TEXTURE,TFV_FLESH2_TEXTURE,TFV_FLESH2_TEXTURE,
		                 TFV_FLESH2_TEXTURE,TFV_FLESH2_TEXTURE,TFV_FLESH2_TEXTURE);
   glPopMatrix();
   glEndList();

       /* TORSO */
#define BREAST_SIZE 0.2  /* Oh, I hope no one ever reads this source code */
   
   tfe_parts[TFV_TORSO]=glGenLists(1);
   glNewList(tfe_parts[TFV_TORSO],GL_COMPILE);
   
   make_rectangle(2,1.0,0.5,TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE,
		          TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE);

       /* chest */
   glBegin(GL_QUADS);

	    calculate_normal(0.5,-0.5,0.25+BREAST_SIZE,
			     0.5,0.5,0.25+BREAST_SIZE,
			     0,-0.5,0.25,
			     &normalx,&normaly,&normalz);
	 glNormal3f(normalx,normaly,normalz);

   
   
       glTexCoord2f(0,0);
       glVertex3f(0.5,-0.5,0.25+BREAST_SIZE);
       glTexCoord2f(1,0);
       glVertex3f(0.5,0.5,0.25+BREAST_SIZE);
       glTexCoord2f(1,1);
       glVertex3f(0,0.5,0.25);
       glTexCoord2f(0,1);
       glVertex3f(0,-0.5,0.25);
   
   
   	    calculate_normal(0.75,-0.5,0.25,
			     0.75,0.5,0.25,
			     0.5,-0.5,0.25+BREAST_SIZE,
			     &normalx,&normaly,&normalz);
	 glNormal3f(normalx,normaly,normalz);
   
       glTexCoord2f(0,0);
       glVertex3f(0.75,-0.5,0.25);
       glTexCoord2f(1,0);
       glVertex3f(0.75,0.5,0.25);
       glTexCoord2f(1,1);
       glVertex3f(0.5,0.5,0.25+BREAST_SIZE);
       glTexCoord2f(0,1);
       glVertex3f(0.5,-0.5,0.25+BREAST_SIZE);
   
   glEnd();
   
   glBegin(GL_TRIANGLES);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(0,-0.5,0.25);
      glTexCoord2f(0,1);
      glVertex3f(0.75,-0.5,0.25);
      glTexCoord2f(0.25,1);
      glVertex3f(0.5,-0.5,0.25+BREAST_SIZE);
   
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(0,0.5,0.25);
      glTexCoord2f(0,1);
      glVertex3f(0.75,0.5,0.25);
      glTexCoord2f(0.25,1);
      glVertex3f(0.5,0.5,0.25+BREAST_SIZE);
      
   
   
   glEnd();
   
   glEndList();
   
 
       /* UPPER ARM */
   tfe_parts[TFV_UPPER_ARM]=glGenLists(1);
   glNewList(tfe_parts[TFV_UPPER_ARM],GL_COMPILE);
   make_rectangle(1,0.25,0.25,TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE,
		              TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE);
   glEndList();
   
       /* LOWER ARM */
   tfe_parts[TFV_LOWER_ARM]=glGenLists(1);
   glNewList(tfe_parts[TFV_LOWER_ARM],GL_COMPILE);
   glPushMatrix();
   make_rectangle(1,0.25,0.25,TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE,
		              TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE,TFV_LIGHT_FLANNEL_TEXTURE);
                        /* hand */
   glTranslatef(1,0,0);
   make_rectangle(0.33,0.33,0.33,TFV_FLESH2_TEXTURE,TFV_FLESH2_TEXTURE,TFV_FLESH2_TEXTURE,
		                 TFV_FLESH2_TEXTURE,TFV_FLESH2_TEXTURE,TFV_FLESH2_TEXTURE);
   glPopMatrix();
   
   glEndList();
   
       /* WAIST */
   tfe_parts[TFV_WAIST]=glGenLists(1);
   glNewList(tfe_parts[TFV_WAIST],GL_COMPILE);
   make_rectangle(0.5,1.1,0.6,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,
		              TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE);
   glEndList();
   
       /* UPPER LEG */
   tfe_parts[TFV_UPPER_LEG]=glGenLists(1);
   glNewList(tfe_parts[TFV_UPPER_LEG],GL_COMPILE);
   make_rectangle(1,0.5,0.5,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,
		              TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE);
   glEndList();
   
       /* LOWER LEG */
   tfe_parts[TFV_LOWER_LEG]=glGenLists(1);
   glNewList(tfe_parts[TFV_LOWER_LEG],GL_COMPILE);
   make_rectangle(1,0.5,0.5,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,
		              TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE,TFV_JEANS_TEXTURE);
   glTranslatef(1.0,0,0);
   make_rectangle(0.25,0.5,0.5,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,
		               TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE);
   glTranslatef(0.25,0,0.25);
   make_rectangle(0.5,0.5,1.0,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,
		              TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE,TFV_SHOE_TEXTURE);
   
   glEndList();
   

       /* SWORD */
   tfe_parts[TFV_SWORD]=glGenLists(1);
   glNewList(tfe_parts[TFV_SWORD],GL_COMPILE);
      
   make_rectangle(1,0.25,0.25,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,
		              TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE);   
   

   glTranslatef(1,0,0);

   glBindTexture(GL_TEXTURE_2D,textures[TFV_SWORD_TEXTURE]);      
   glBegin(GL_TRIANGLES);
       glNormal3f(0,0,1);
   
       glTexCoord2f(0,0);
       glVertex3f(0,-0.5,0.125);
       glTexCoord2f(1,0.5);
       glVertex3f(1,0,0.125);
       glTexCoord2f(0,1);
       glVertex3f(0,0.5,0.125);
   
   glEnd();
   
   glBegin(GL_QUADS);
       glNormal3f(-1,0,0);
       glTexCoord2f(0,0);
       glVertex3f(0,-0.5,-0.125);
       glTexCoord2f(1,0);
       glVertex3f(0,-0.5,0.125);
       glTexCoord2f(1,1);
       glVertex3f(0,0.5,0.125);
       glTexCoord2f(0,1);
       glVertex3f(0,0.5,-0.125);
   
       glNormal3f(0.447,-0.894,0);
       glTexCoord2f(0,0);
       glVertex3f(0,-0.5,-0.125);
       glTexCoord2f(1,0);
       glVertex3f(0,-0.5,0.125);
       glTexCoord2f(1,1);
       glVertex3f(1,0,0.125);
       glTexCoord2f(0,1);
       glVertex3f(1,0,-0.125);
   
       glNormal3f(0.447,0.894,0);
       glTexCoord2f(0,0);
       glVertex3f(1,0,-0.125);
       glTexCoord2f(1,0);
       glVertex3f(1,0,0.125);
       glTexCoord2f(1,1);
       glVertex3f(0,0.5,0.125);
       glTexCoord2f(0,1);
       glVertex3f(0,0.5,-0.125);
      
   
   glEnd();
   
   glBegin(GL_TRIANGLES);
       glNormal3f(0,0,-1);
   
       glTexCoord2f(1,0);
       glVertex3f(0,-0.5,-0.125);
       glTexCoord2f(1,1);
       glVertex3f(0,0.5,-0.125);
       glTexCoord2f(0,0.5);
       glVertex3f(1,0,-0.125);
   
   glEnd();
   
   
   glTranslatef(1,0,0);
   make_rectangle(0.25,1,0.25,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,
		              TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE);   
   glTranslatef(0.25,0,0);
   make_rectangle(1,0.25,0.25,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,
		              TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE,TFV_SWORD_TEXTURE);   
   
   glTranslatef(-0.5,-0.75,0);
   glBindTexture(GL_TEXTURE_2D,textures[TFV_SWORD_ARROWS_TEXTURE]);      
   glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glTexCoord2f(0,0);
      glVertex3f(0.5,0.5,0);
      glTexCoord2f(1,0);
      glVertex3f(0.5,-0.5,0);
      glTexCoord2f(1,1);
      glVertex3f(-0.5,-0.5,0);
      glTexCoord2f(0,1);
      glVertex3f(-0.5,0.5,0);
   glEnd();
   
   glEndList();
   
   return 6798329;
}



    /* Options.. make them blink now and then? */
void draw_tfv(int head_twist,int waist_twist,int left_arm_angle,int left_elbow_angle,
	      int right_arm_angle,int right_elbow_angle,int left_leg_angle,
	      int left_knee_angle,int right_leg_angle,int right_knee_angle,
	      int show_sword,int whom) {

   GLuint *parts;
   
   if (whom) parts=tfe_parts;
   else parts=tfv_parts;
   
   glPushMatrix();
          /* head */   
      glCallList(parts[TFV_HEAD]);

      glTranslatef(1.25,0,0);
          /* torso */
      glCallList(parts[TFV_TORSO]);
             /* right arm */
      glPushMatrix();

         glTranslatef(0,-.625,0);
   
         glCallList(parts[TFV_UPPER_ARM]);
         glTranslatef(1,0,0);
         glRotatef(right_elbow_angle,0,1,0);
         glCallList(parts[TFV_LOWER_ARM]);
   
         if (show_sword) { 
	    glTranslatef(1.15,0,0);
	    glRotatef(270,0,1,0);
	    glRotatef(90,1,0,0);
	    glCallList(parts[TFV_SWORD]);
	 }
   
      glPopMatrix();   
             /* left arm */   
      glPushMatrix();
         glTranslatef(0,0.625,0);
   
         glCallList(parts[TFV_UPPER_ARM]);
         glTranslatef(1,0,0);
         glRotatef(left_elbow_angle,0,1,0);
         glCallList(parts[TFV_LOWER_ARM]);
      glPopMatrix();   
   
      glTranslatef(2.0,0,0);
          /* waist */
      glCallList(parts[TFV_WAIST]);
   
      glTranslatef(0.5,0,0);
          /* right leg */
      glPushMatrix();
         glTranslatef(0,-0.26,0);
         glCallList(parts[TFV_UPPER_LEG]);
         glTranslatef(1,0,0);
         glRotatef(right_knee_angle,0,1,0);
         glCallList(parts[TFV_LOWER_LEG]);
      glPopMatrix();
          /* left leg */
      glPushMatrix();
         glTranslatef(0,0.26,0);
         glCallList(parts[TFV_UPPER_LEG]);
         glTranslatef(1,0,0);
         glRotatef(right_knee_angle,0,1,0);
         glCallList(parts[TFV_LOWER_LEG]);
      glPopMatrix();
   glPopMatrix();
   
}
   
   
