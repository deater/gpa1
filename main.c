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
#include "matrix_math.h"

#define PI 3.141592653589793238462643383279502884197169399
  

#define checkImageWidth 64
#define checkImageHeight 64


int use_textures=1;
int use_lighting=1;

   GLuint leonard;

GLuint textures[10];


float direction=0.0,pigx=0.0,pigy=0.0,pigz=1.0;

float camera_direction=90*(180.0/PI),camerax=-10.0,cameray=0,cameraz=5.0;

int done=0;


void parse_config(void) {
   
}

#define CARROT_TEXTURE            0
#define EYE_TEXTURE               1
#define ROBOT_FACE_TEXTURE        2
#define GRASS_TEXTURE             3
#define LEAVES_TEXTURE            4
#define NOSE_TEXTURE              5
#define SKY_TEXTURE               6
#define BROWN_TEXTURE             7
#define BROWN_WHITE_BROWN_TEXTURE 8
#define FLESH_TEXTURE             9

void LoadTexture(int x,int y,char *filename,int which_one,int transparent,
		 int repeat_type) {


    static GLubyte *texture;
    texture=vmwLoadTexture(x,y,texture,filename,transparent);

    glBindTexture(GL_TEXTURE_2D,textures[which_one]);
   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x,
		 y ,0,GL_RGBA,GL_UNSIGNED_BYTE,texture);
   
}
   
void LoadTextures(void) {

   glPixelStorei(GL_UNPACK_ALIGNMENT,1);
   
   glGenTextures(10,textures);  
   
   LoadTexture(64,64,"./textures/carrot.amg",CARROT_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/eye.amg",EYE_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/face.amg",ROBOT_FACE_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/grass.amg",GRASS_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/leaves.amg",LEAVES_TEXTURE,1,GL_CLAMP);
   LoadTexture(64,64,"./textures/nose.amg",NOSE_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/sky.amg",SKY_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/brown.amg",BROWN_TEXTURE,0,GL_REPEAT);
   LoadTexture(64,64,"./textures/bwb.amg",BROWN_WHITE_BROWN_TEXTURE,0,GL_CLAMP);
   LoadTexture(64,64,"./textures/flesh.amg",FLESH_TEXTURE,0,GL_CLAMP);
}

GLubyte *font;


void init(void) {
//   glViewport(0,0,640,480);

   glPixelStorei(GL_UNPACK_ALIGNMENT,1);
   font=vmwLoadFont("./fonts/vmw.fnt",8,16,128,2);
   glClearColor(0.0,0.0,0.0,0.0);
   glClearDepth(1.0);
   glShadeModel(GL_SMOOTH);
//   glEnable(GL_LIGHTING);
//   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0f,(GLfloat)640/(GLfloat)480,0.1f,100.0f);
   
   LoadTextures();
  
}

  


void draw_carrot(float carrotx,float carroty,float carrotz,float direction) {
   
   glPushMatrix();

   glTranslatef(carrotx,carroty,carrotz);
   glRotatef(direction,0.0,0.0,1.0);
   
   glColor3f(0.9961,0.6445,0);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,textures[CARROT_TEXTURE]);      
   glBegin(GL_TRIANGLES);
    
      glVertex3f(0.0,-0.5,0.5);
      glVertex3f(2.0,0,0.5);
      glVertex3f(0.0,0.5,0.5);
   
      glVertex3f(0.0,0.5,0.5);
      glVertex3f(2.0,0,0.5);
      glVertex3f(0.0,0.5,-0.5);
   
      glVertex3f(0.0,0.5,-0.5);
      glVertex3f(2.0,0,0.5);
      glVertex3f(0.0,-0.5,-0.5);
   
   
      glVertex3f(0.0,-0.5,-0.5);
      glVertex3f(2.0,0,0.5);
      glVertex3f(0.0,-0.5,0.5);
   
      /* TOP */
   
      glVertex3f(0.0,-0.5,0.5);
      glVertex3f(0.0,0.5,0.5);
      glVertex3f(0.0,0.5,-0.5);
   
   
      glVertex3f(0.0,0.5,-0.5);
      glVertex3f(0.0,-0.5,-0.5);
      glVertex3f(0.0,-0.5,0.5);
   
   
   glEnd();
   


   
   glBindTexture(GL_TEXTURE_2D,textures[LEAVES_TEXTURE]);   
     glBegin(GL_QUADS);
   
     glTexCoord2f(0.0,0.0);
     glVertex3f(0.0,0.0,0.5);
     glTexCoord2f(0.0,1.0);
     glVertex3f(0.0,0.0,-0.5);
     glTexCoord2f(1.0,1.0);
     glVertex3f(-2.0,0.0,-0.5);
     glTexCoord2f(1.0,0.0);
     glVertex3f(-2.0,0.0,0.5);

     glTexCoord2f(0.0,0.0);
     glVertex3f(0.0,0.5,0.0);
     glTexCoord2f(0.0,1.0);
     glVertex3f(0.0,-0.5,0.5);
     glTexCoord2f(1.0,1.0);
     glVertex3f(-2.0,-0.5,0.0);
     glTexCoord2f(1.0,0.0);
     glVertex3f(-2.0,0.5,0.0);
   
   
   
     glEnd();
   
   
   glDisable(GL_TEXTURE_2D);
   
   
   
   
   glPopMatrix();
   
}




void draw_robo_pig(float pigx,float pigy,float pigz,float direction) {
   
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   
   glPushMatrix();

   
   glTranslatef(pigx,pigy,pigz);
   glRotatef(direction,0.0,0.0,1.0);
   
   glBindTexture(GL_TEXTURE_2D,textures[0]);
   
   
      /* Back */
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,1.0,-1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(-2.0,1.0,1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(-2.0,-1.0,1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,-1.0,-1.0);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,textures[1]);
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
   
   glBindTexture(GL_TEXTURE_2D,textures[2]);
   glBegin(GL_QUADS);
   
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,1.0,-1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(2.0,1.0,1.0);
   glTexCoord2f(0.0, 0.0); glVertex3f(2.0,-1.0,1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,-1.0,-1.0);
   
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

   return;
}

void display(void) {
   
   int i,j;
     GLfloat light_position[]={0.0,0.0,10.0,0.0
     };
   
       GLfloat lmodel_ambient[]={0.9,0.9,0.9,1.0
       };
   
   
       GLfloat white_light[]={1.0,1.0,1.0,1.0
       };
   
   
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   glLoadIdentity();
   gluLookAt(camerax,cameray,cameraz,
	     0.0,0.0,0.0,
	     0.0,0.0,1.0);
   
   if (use_lighting) {
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
      glLightfv(GL_LIGHT0, GL_SPECULAR,white_light);
      
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
      glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
			        
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
   }
   

   
     {
	GLfloat default_a[]={0.2,0.2,0.2,1.0};
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
   glRotatef( (360-direction),0,0,1);   
   glTranslatef(-pigx,-pigy,-0.5);

   
   glColor3f(0.4102,0.543,0.1328);
   
   glEnable(GL_TEXTURE_2D);
       /* Draw Sky */

   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   glBindTexture(GL_TEXTURE_2D,textures[SKY_TEXTURE]);
   glBegin(GL_QUADS);
   
          /* Back */
      glNormal3f(-1.0,0.0,0.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(20,-20,-20);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(20,-20,20);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(20,20,20);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(20,20,-20);
   
         /* Right */
   
      glNormal3f(0.0,1.0,0.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(20,-20,20);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(20,-20,-20);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-20,-20,-20);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-20,-20,20);
   
         /* Front */
      glNormal3f(1.0,0.0,0.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(-20,-20,20);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(-20,-20,-20);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-20,20,-20);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-20,20,20);
   
         /* Left */
    
      glNormal3f(0.0,-1.0,0.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(-20,20,20);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(-20,20,-20);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(20,20,-20);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(20,20,20);
   
   
          /* top */
      glNormal3f(0.0,0.0,-1.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(20,20,20);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(20,-20,20);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-20,-20,20);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-20,20,20);
   
             /* bottom */
      glNormal3f(0.0,0.0,1.0);
   
      glTexCoord2f(0.0, 0.0);
      glVertex3f(20,20,-20);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(20,-20,-20);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(-20,-20,-20);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(-20,20,-20);
   
   glEnd();

   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
       /* Draw grassy field */   
   glBindTexture(GL_TEXTURE_2D,textures[GRASS_TEXTURE]);      

   glBegin(GL_QUADS);
      for(i=-10;i<10;i++) {
         for (j=-10;j<10;j++) {
	     glNormal3f(0.0,0.0,1.0);
   
             glTexCoord2f(0.0, 0.0);
             glVertex3f(i*2,j*2,0);
             
	     glTexCoord2f(0.0, 1.0);
             glVertex3f(i*2,(j*2)+2,0);
      
	     glTexCoord2f(1.0, 1.0);
             glVertex3f((i*2)+2,(j*2)+2,0);
	    
             glTexCoord2f(1.0, 0.0);
             glVertex3f( (i*2)+2,(j*2),0);
	 }
      }
   glEnd();
   glDisable(GL_TEXTURE_2D);
   
   
   draw_carrot(-4.0,3.0,0.5,90);
   glPopMatrix();

   
//   draw_robo_pig(pigx,pigy,pigz,direction);
//      draw_good_pig(pigx,pigy,pigz,direction);

//   draw_guinea_pig(leonard,pigx,pigy,pigz,direction);
   
   draw_guinea_pig(leonard,0,0,0,0);
   
//   printf("%.2f %.2f %.2f\n",pigx,pigy,pigz);
   
   
   
   glFlush();
   SDL_GL_SwapBuffers();

   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);
}

void reshape(int w,int h) {
   glViewport(0,0,(GLsizei)w,(GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //glTranslatef(0.0,0.0,-3.6);
}

int check_keyboard(void) {

      
   
    SDL_Event event;
    int keypressed;

    static int up_down=0,up_time=0;

    static int count=0;
   
    if (up_down) {
       count++;
       if (count==100) {
	  count=0;
	  printf("REPEAT!\n");
       }
    }
   
   
   
    while ( SDL_PollEvent(&event) ) {
       if ( event.type == SDL_QUIT ) {
          done = 1;
	  return 1;
       }

       if (event.type == SDL_KEYUP) {
	  printf("UP\n");
	  keypressed=event.key.keysym.sym;
	  
	  switch(keypressed) {
              case SDLK_UP: up_down=0;	 
	                    return 1;
	                    break;
	     
	  }
       }
       
       if ( event.type == SDL_KEYDOWN ) {
	  keypressed=event.key.keysym.sym;
	   
	  switch (keypressed) {
	   case 'L':
	   case 'l': use_lighting=!(use_lighting); break;
	     
	   case 'T':
	   case 't': use_textures=!(use_textures); break;

	   case 'k': case 'K':
	             camera_direction+=(10.0*PI)/180;
	             if (camera_direction>2*PI) camera_direction-=2*PI;
	             camerax=10*sin(camera_direction);
	             cameray=10*cos(camera_direction);
	             break;
	   case 'j': case 'J':
	             camera_direction-=(10.0*PI)/180;
	             if (camera_direction<0.0) camera_direction+=2*PI;
	             camerax=10*sin(camera_direction);
	             cameray=10*cos(camera_direction);
	             break;
	  case 'm': case 'M':
	             cameraz-=0.5;
	             break;
	   case 'i': case 'I':
	             cameraz+=0.5;;
	             break;
	     
	   case SDLK_ESCAPE: done = 1; 
	                     return 1;  
	                     break;
	   case SDLK_RIGHT:  direction-=10;
                             return 1;
           case SDLK_LEFT:   direction+=10;    
                             return 1;
           case SDLK_UP:     up_down=1;
	                     up_time=SDL_GetTicks();
	                     pigy+=sin( (direction*PI)/180.0);
                             pigx+=cos( (direction*PI)/180.0);
	                     return 1;
	   case SDLK_DOWN:   pigy-=sin( (direction*PI)/180.0);
                             pigx-=cos( (direction*PI)/180.0);
                             return 1;
	  }
       }
    }
    return 0;
}

int main(int argc, char **argv) {


   int frames=0,msecs=0,old_msecs=0;
      
   parse_config();
   
   
       /* Initialize SDL */
   if ( SDL_Init(SDL_INIT_VIDEO)<0) {
      printf("Error trying to init SDL\n");
      return -1;
   }
   
       /* Create a 640x480 OpenGL screen */
   if ( SDL_SetVideoMode(640, 480, 0, SDL_OPENGL) == NULL ) {
      printf("Unable to create OpenGL screen: %s\n", SDL_GetError());
      SDL_Quit();
      return -2;
   }
   
   SDL_WM_SetCaption("Guinea Pig Adventure...",NULL);
   
   init();
   reshape(640,480);
   
//   display();
 
    opener();

    leonard=setup_pig_list(0,0);
   
    
    while ( ! done ) {
       
       frames++;
//       printf("%i\n",frames);
       if (frames%100==0) {
	  old_msecs=msecs;
	  msecs=SDL_GetTicks();
          printf("FPS=%.2f\n", frames/((msecs-old_msecs)/1000.0));	 
	  frames=0;
       }
       check_keyboard();
       display();
       
    }
    SDL_Quit();

   return 0;
}
