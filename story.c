#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vmw_texture.h"
#include "vmw_glfont.h"

#include "opener.h"
#include "guinea_pig.h"
#include "spaceship.h"
#include "matrix_math.h"

#include "keyboard.h"

#include "textures.h"

    /* As much as I have memorized... */
#define PI 3.141592653589793238462643383279502884197169399
  



extern GLuint spaceships[2];


   
#define D2R(x) ((x*PI)/180.0)

float sphere[28][36][3];

void setup_sphere(void) {
   

   float rho=204.5,theta=0,phi=0;
   
   int i,j;
   
   for(i=0;i<28;i++) {
      phi=((float)i-14.5)*0.4;
      for(j=0;j<36;j++) {
	 theta=j*10.0;
         sphere[i][j][0]=rho*sin(D2R(phi))*cos(D2R(theta));
         sphere[i][j][1]=rho*sin(D2R(phi))*sin(D2R(theta));
	 sphere[i][j][2]=rho*cos(D2R(phi))-204.31;
      }

   }
}


void do_story(void) {
int old_msecs=0,new_msecs=0;
float camera_direction=90*(180.0/PI),camerax=-10.0,cameray=0,cameraz=5.0;
#if 0
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
   

      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//      glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
      glLightfv(GL_LIGHT0, GL_SPECULAR,white_light);
      
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
//      glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);

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
#endif
}
