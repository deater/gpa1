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

int generate_sphere(float radius, int latitudes, int longitudes, int texture) {
 
       /* The way I do this is brutally inefficient */
       /* I should optimize it later [ie, do everything in radians] */
   float delta_theta,delta_phi;
   float init_x1,init_y1,init_z1,x1,y1,z1;
   float init_x2,init_y2,init_z2,x2,y2,z2;
   int phi_prime,theta_prime;
   float normalx,normaly,normalz;


   glBindTexture(GL_TEXTURE_2D,textures[texture]);
   
   delta_phi=180.0/(float)latitudes;
   delta_theta=360.0/(float)longitudes;
   
   
   for(phi_prime=0;phi_prime<latitudes;phi_prime++) {
      theta_prime=0;
      glBegin(GL_QUAD_STRIP);
      
      init_x1=radius*sin(D2R(phi_prime*delta_phi))*cos(D2R(theta_prime*delta_theta));
      init_y1=radius*sin(D2R(phi_prime*delta_phi))*sin(D2R(theta_prime*delta_theta));
      init_z1=radius*cos(D2R(phi_prime*delta_phi));
      

      glNormal3f(init_x1/radius,init_y1/radius,init_z1/radius);
      glTexCoord2f( (theta_prime*delta_theta)/360.0, (phi_prime*delta_phi)/360.0);
      glVertex3f(init_x1,init_y1,init_z1);      
      
      init_x2=radius*sin(D2R((phi_prime+1)*delta_phi))*cos(D2R(theta_prime*delta_theta));
      init_y2=radius*sin(D2R((phi_prime+1)*delta_phi))*sin(D2R(theta_prime*delta_theta));
      init_z2=radius*cos(D2R((phi_prime+1)*delta_phi));
      
      
      
//      printf("%.2f %.2f %.2f : %.2f %.2f %.2f\n",radius,phi_prime*delta_phi,theta_prime*delta_theta,normalx,normaly,normalz);
      
      glNormal3f(init_x2/radius,init_y2/radius,init_z2/radius);
      glTexCoord2f( (theta_prime*delta_theta)/360.0, ((phi_prime+1)*delta_phi)/360.0);
      glVertex3f(init_x2,init_y2,init_z2);
      
      for(theta_prime=1;theta_prime<longitudes;theta_prime++) {
   
	 x1=radius*sin(D2R(phi_prime*delta_phi))*cos(D2R(theta_prime*delta_theta));
         y1=radius*sin(D2R(phi_prime*delta_phi))*sin(D2R(theta_prime*delta_theta));
	 z1=radius*cos(D2R(phi_prime*delta_phi));
	 
	 
         glNormal3f(x1/radius,y1/radius,z1/radius);
	 glTexCoord2f( (theta_prime*delta_theta)/360.0, (phi_prime*delta_phi)/360.0);
	 glVertex3f(x1,y1,z1);
	 
	 x2=radius*sin(D2R((phi_prime+1)*delta_phi))*cos(D2R(theta_prime*delta_theta));
         y2=radius*sin(D2R((phi_prime+1)*delta_phi))*sin(D2R(theta_prime*delta_theta));
         z2=radius*cos(D2R((phi_prime+1)*delta_phi));
	 
	 glNormal3f(x2/radius,y2/radius,z2/radius);
	 glTexCoord2f( (theta_prime*delta_theta)/360.0, ((phi_prime+1)*delta_phi)/360.0);
	 glVertex3f(x2,y2,z2);	 
      }
      glNormal3f(init_x1/radius,init_y1/radius,init_z1/radius);
      glTexCoord2f( (theta_prime*delta_theta)/360.0, (phi_prime*delta_phi)/360.0);
      glVertex3f(init_x1,init_y1,init_z1);
      
            glNormal3f(init_x1/radius,init_y1/radius,init_z1/radius);
      glTexCoord2f( (theta_prime*delta_theta)/360.0, (phi_prime*delta_phi)/360.0);
      glVertex3f(init_x2,init_y2,init_z2);
      glEnd();      
   }
   
   return 0;
}


void do_story(int width,int height) {

    int old_msecs=0,msecs=0;
    int frames_msec,old_frames_msec=0,frames=0;
    float camera_direction=90*(180.0/PI),camerax=-10.0,cameray=0,cameraz=5.0;

    char alpha;
    int done=0,keyspressed;
     
       
    float stars[1000][3];
   
   int i,j,distance_seen,land_type,tempx,tempy,theta,phi;
   GLfloat shadow_width;
       
     GLfloat light_position[]={1.0,0.0,0.0,0.0
     };
   
//     GLfloat light_ambient[]={0.5,0.5,0.5,1.0
//     };
       GLfloat lmodel_ambient[]={0.4,0.4,0.4,1.0
       };
   
   
       GLfloat white_light[]={1.0,1.0,1.0,1.0
       };
   
    glViewport(0,0,(GLsizei)width,(GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)width/(GLfloat)height,1.0,200000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
      //glTranslatef(0.0,0.0,-3.6);

    for(i=0;i<1000;i++) {
       theta=rand()%360;
       phi=rand()%180;
       
       stars[i][0]=150000*sin(D2R(phi))*cos(D2R(theta));
       stars[i][1]=150000*sin(D2R(phi))*sin(D2R(theta));
       stars[i][2]=150000*cos(D2R(phi));
       
       
    }
   
   
    old_msecs=SDL_GetTicks();
    while(!done) {
       
       frames++;
       if (frames%100==0) {
	  frames_msec=SDL_GetTicks();
          printf("FPS: %.2f\n",frames/((frames_msec-old_frames_msec)/1000.0));
	  frames=0;
	  old_frames_msec=frames_msec;
       }
       
       
       msecs=SDL_GetTicks();
       cameray=(15-((msecs-old_msecs)/1000.0))*44.0;
       camerax=(((msecs-old_msecs)/1000.0))*-3.2;
  

       if (((msecs-old_msecs)/1000.0)>20.0) {
	  done=1;
       }
   
   
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
//   glRotatef( (360-gs.direction),0,0,1);   
//   glTranslatef(-gs.pigx,-gs.pigy,-gs.pigz);

   
   glColor3f(0.4102,0.543,0.1328);
   
   glEnable(GL_TEXTURE_2D);
       /* Draw Sky */


       
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POINTS);

       for(i=0;i<1000;i++) {
//	  printf("%.2f %.2f %.2f\n",stars[i][0],stars[i][1],stars[i][2]);
	  glVertex3f(stars[i][0],stars[i][1],stars[i][2]);
       }
       
   glEnd();
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);

   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   glBindTexture(GL_TEXTURE_2D,textures[SUN_TEXTURE]);
   glBegin(GL_QUADS);
   
   
          /* Draw Sun */
          /* Earth's sun is 149 000 000km away and 1 400 000km in diameter */
          /* Here I am using a scale of 1:1000km */
       
          /* I actually make the sun bigger by factor of 10 because otherwise */
          /* it is hardly more than a large star... */
       
      glNormal3f(-1.0,0.0,0.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(149000,7000,-7000);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(149000,-7000,-7000);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(149000,-7000,7000);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(149000,7000,7000);
   glEnd();
   
       
   glEnable(GL_TEXTURE_2D);

   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

       /* make world.  Rotate 90 degrees so main continent is face out */
   glPushMatrix();
   glRotatef(270,0,0,1);
   generate_sphere(12.7,20,20,WORLD_MAP_TEXTURE);
   glPopMatrix();    
       
   glPushMatrix();
   glTranslatef(0,384,0);
       
       /* moon is 3 times bigger too */
   generate_sphere(8,15,15,MOON_MAP_TEXTURE);

   glPopMatrix();

   glDisable(GL_LIGHTING);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,320,0,200);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glColor3f(1.0,0.0,0.0);
   glRasterPos3f(5,170,0);
   vmwGLString("THE MEERSCHWEINCHEN SYSTEM",font);
       
    glViewport(0,0,(GLsizei)width,(GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)width/(GLfloat)height,1.0,200000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();   
       
       
       
       glFlush();
       SDL_GL_SwapBuffers();

       glDisable(GL_LIGHTING);
       glDisable(GL_TEXTURE_2D);

       keyspressed=check_keyboard(&alpha,0);
       if (keyspressed&MENU_PRESSED) {
          done=1;
       }
       
       switch(alpha) {
	      
          case 'k':  camera_direction+=(10.0*PI)/180;
		     if (camera_direction>2*PI) camera_direction-=2*PI;
		     camerax=100*sin(camera_direction);
		     cameray=100*cos(camera_direction);
		     break;
          case 'j':  camera_direction-=(10.0*PI)/180;
		     if (camera_direction<0.0) camera_direction+=2*PI;
		     camerax=100*sin(camera_direction);
		     cameray=100*cos(camera_direction);
		     break;
	  case 'm':
		     cameraz-=0.5;
		     break;
	  case 'i':
                     cameraz+=0.5;
		     break;
       }
		 
      
    }
}
