#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VERSION "0.0.11"

#include "vmw_texture.h"
#include "vmw_glfont.h"

#include "gl_helper.h"

#include "opener.h"
#include "guinea_pig.h"

#include "main_menu.h"
#include "story.h"

#include "textures.h"

#include "game_state.h"
#include "world.h"


int use_lighting=1;
int show_fps=1;

void parse_config(void) {
   
}

void LoadTextures(void) {

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
   
    glGenTextures(TOTAL_TEXTURES,textures);  
   
        /* 0 */
    LoadTexture(64,64,"./textures/carrot.amg",CARROT_TEXTURE,0,GL_REPEAT);
    LoadTexture(64,64,"./textures/eye.amg",EYE_TEXTURE,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/face.amg",ROBOT_FACE_TEXTURE,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/grass.amg",GRASS_TEXTURE,0,GL_REPEAT);
    LoadTexture(64,64,"./textures/leaves.amg",LEAVES_TEXTURE,1,GL_CLAMP);
        /* 5 */
    LoadTexture(64,64,"./textures/nose.amg",NOSE_TEXTURE,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/sky.amg",SKY_TEXTURE,0,GL_REPEAT);
    LoadTexture(64,64,"./textures/brown.amg",BROWN_TEXTURE,0,GL_REPEAT);
    LoadTexture(64,64,"./textures/bwb.amg",BROWN_WHITE_BROWN_TEXTURE,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/flesh.amg",FLESH_TEXTURE,0,GL_CLAMP);
        /* 10 */
    LoadTexture(64,64,"./textures/ocean.amg",OCEAN_TEXTURE,0,GL_REPEAT);
    LoadTexture(64,64,"./textures/mountain.amg",MOUNTAIN_TEXTURE,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/cliff.amg",CLIFF_TEXTURE,0,GL_REPEAT);
    LoadTexture(64,64,"./textures/sand.amg",SAND_TEXTURE,0,GL_REPEAT);
    LoadTexture(64,64,"./textures/tree.amg",FOREST_TEXTURE,0,GL_REPEAT);
        /* 15 */
    LoadTexture(64,64,"./textures/shallow.amg",SHALLOW_TEXTURE,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/tundra.amg",TUNDRA_TEXTURE,0,GL_REPEAT);
    LoadTexture(64,64,"./textures/spaceship_gray.amg",SS_GRAY,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/spaceship_top.amg",SS_TOP,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/spaceship_bottom.amg",SS_BOTTOM,0,GL_CLAMP);
        /* 20 */
    LoadTexture(64,64,"./textures/spaceship_thrust_on.amg",SS_THRUST,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/spaceship_thrust_off.amg",SS_NOTHRUST,0,GL_CLAMP);
    LoadTexture(128,64,"./textures/spaceship_right.amg",SS_RIGHT,0,GL_CLAMP);
    LoadTexture(128,64,"./textures/spaceship_left.amg",SS_LEFT,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/spaceship_back.amg",SS_BACK,0,GL_CLAMP);
        /* 25 */
    LoadAlphaTexture(64,64,"./textures/shadow.amg",SHADOW_TEXTURE,0,GL_CLAMP,0x00,0x00,0x00);
    LoadAlphaTexture(64,64,"./textures/splash.amg",SPLASH_TEXTURE,0,GL_CLAMP,0x52,0xdd,0xdd);
    LoadTexture(128,64,"./textures/planet_map.amg",WORLD_MAP_TEXTURE,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/moon_map.amg",MOON_MAP_TEXTURE,0,GL_CLAMP);
    LoadTexture(64,64,"./textures/sun.amg",SUN_TEXTURE,0,GL_CLAMP);
        /* 30 */
    LoadTexture(64,64,"./textures/stars.amg",STAR_TEXTURE,0,GL_REPEAT);
}

void init_gl(void) {
   
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glClearColor(0.0,0.0,0.0,0.0);
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   
    LoadTextures();
}

  



int main(int argc, char **argv) {

    SDL_Joystick *joy;

    int result,font_scale,i,mode;
    int print_help=0,print_version=0,fullscreen=0;
   
    int xsize=640,ysize=480;

 
    game_state_type gs={
       0,0,0,-0.5,
       5,13,
       1,1,
       1,
       4,13,
       0,0,0
    };

    for(i=1;i<argc;i++) {
       switch(argv[i][1]) {
	case 'h': print_help=1;
	          break;
	case 'v': print_version=1;
	          break;
	case 'f': fullscreen=1;
	          break;
	case 't': xsize=320; ysize=200;
	          break;
	case 'l': xsize=1024; ysize=768;
	          break;
	default: printf("\nUnknown option %s\n",argv[i]);
	         print_help=1;
       }
    }
    printf("\n");
    printf("       Guinea Pig Adventure version %s\n",VERSION);
    printf("        by Vince Weaver <vince@deater.net>\n");
    printf("      http://www.deater.net/weave/vmwprod/gp1/\n");
    printf("\n");

    if (print_version) return 0;
   
    if (print_help) {
       printf("Usage:	%s [-help] [-version] [-fullscreen] [-tiny] [-large]\n",argv[0]);
       printf("\n");
       printf("\t-help       : print this help information\n");
       printf("\t-version    : print version info and quit\n");
       printf("\t-fullscreen : run in full screen mode\n");
       printf("\t-tiny       : run in 320x200 mode\n");
       printf("\t-large      : run in 1024x768 mode\n");
       printf("\n");
       return 0;
    }
   
       /* Parse the config file */
    parse_config();   
   
       /* Make sure the font is loaded and the proper size */
    font_scale=(xsize/320);
    if (font_scale<=1) font_scale=1;
    else (font_scale=2);
   
    font=vmwLoadFont("./fonts/vmw.fnt",8,16,128,font_scale);
   
       /* Initialize SDL */
    if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK)<0) {
       printf("Error trying to init SDL: %s\n",SDL_GetError());
       return -1;
    }
   
    if (fullscreen) mode=SDL_OPENGL | SDL_FULLSCREEN;
    else mode=SDL_OPENGL;
   
       /* Create the OpenGL screen */
    if ( SDL_SetVideoMode(xsize, ysize, 0, mode) == NULL ) {
       printf("Unable to create OpenGL screen: %s\n", SDL_GetError());
       SDL_Quit();
       return -2;
    }
   
    SDL_WM_SetCaption("Guinea Pig Adventure...",NULL);
   
       /* Try to init Joysticks */
    if (SDL_NumJoysticks()>0){
       /* Open joystick */
       joy=SDL_JoystickOpen(0);
       if (joy) {
	  printf("Opened Joystick 0\n");
	  printf("Name: %s\n", SDL_JoystickName(0));
	  SDL_JoystickEventState(SDL_ENABLE);
       }
    }
   
   
       /* Setup OpenGL screen */
    init_gl();
    reshape(xsize,ysize);
 
       /* Run the opener */
    opener(xsize,ysize);
   
       /* Run the main menu */
    result=main_menu(xsize,ysize);
    
    if (result==QUIT) {
       SDL_Quit();
    }
   
    if (result==VIEW_STORY) {
       do_story(xsize,ysize);
    }
    
       /* Start off at the world map */
    reshape(xsize,ysize);
    do_world(xsize,ysize,&gs);
       
       /* Quit */
    SDL_Quit();

   return 0;
}
