#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include <unistd.h> /* usleep() */

#include "vmw_glfont.h"
#include "main_menu.h"
#include "keyboard.h"



void putMenuOption(int x,int y,char *string,int physical_position,int position) {
       
    if (physical_position==position) {
       glColor3f(1.0,1.0,1.0);
       glRasterPos3f(x-16,y,0);
       vmwGLString("->",font);
       glColor3f(1.0,0.0,0.0);
    }
    else {
       glColor3f(0.5,0.0,0.0);
    }
    glRasterPos3f(x,y,0);
    vmwGLString(string,font);
}

int main_menu(int xsize, int ysize) {

    int result,position=0;
    char alpha;


   
    glDisable(GL_LIGHTING);
    glViewport(0,0,xsize,ysize);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,320,0,200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   
    while (1) {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glColor3f(1.0,0.0,0.0);
       glRasterPos3f(76,175,0);
       vmwGLString("GUINEA PIG ADVENTURE",font);
       
       
       putMenuOption(50,125,"VIEW STORY",0,position);
       putMenuOption(50,115,"NEW GAME",1,position);
       putMenuOption(50,105,"LOAD SAVED GAME",2,position);
       putMenuOption(50, 95,"CREDITS",3,position);
       putMenuOption(50, 85,"QUIT",4,position);

       glFlush();
       SDL_GL_SwapBuffers();
       
       usleep(100);
       result=check_keyboard(&alpha,0);
   
       if (result&MENU_PRESSED) {
	  return QUIT;
       }
       
       if ( (result>>16)&UP_PRESSED) {
	  position--;
	  if (position<0) position=4;
       }
       if ( (result>>16)&DOWN_PRESSED) {
	  position++;
	  if (position>4) position=0;
       }
       if ( (result>>16)&CONFIRM_PRESSED) {
	  switch(position) {
	   case 0: return VIEW_STORY;
	   case 1: return NEW_GAME;
	   case 2: return LOAD_GAME;
	   case 3: return CREDITS;
	   case 4: return QUIT;
	     
	     
	  }
       }
       
    }
    return NEW_GAME;
}
