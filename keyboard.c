#include <SDL/SDL.h>

#include "keyboard.h"


int check_keyboard(char *alphanum) {
   
    SDL_Event event;
   
    static int keys_down=0;
    int momentary=0;
    int button,axis,jdirection;
   
    int keypressed;

    *alphanum=0;
   
    while ( SDL_PollEvent(&event) ) {
       if ( event.type == SDL_QUIT ) {
          keys_down|=ESC_PRESSED;
	  return 1;
       }

       if (event.type == SDL_VIDEORESIZE) {
	  printf("RESIZE\b");	  
       }
       
       if (event.type == SDL_JOYBUTTONDOWN) {
	  button=event.jbutton.button;
	  switch(button) {
	     case 0: keys_down|=A_PRESSED;
	             break;
	     case 1: keys_down|=Z_PRESSED;
	             break;
	  }
	  //printf("Button: %i\n",button);
       }
       
       if (event.type == SDL_JOYAXISMOTION) {
	  axis=event.jaxis.axis;
	  jdirection=event.jaxis.value;
	  if (axis==0) {  /* X */
	     if (jdirection>20000) {
		keys_down|=RIGHT_PRESSED;
	     }
	     else if (jdirection<-20000) {
		keys_down|=LEFT_PRESSED;
	     }	     
	     else if ((jdirection>5000) || (jdirection<-5000)) {
		keys_down&=(~RIGHT_PRESSED);
		keys_down&=(~LEFT_PRESSED);
//			     printf("X: %i\n",jdirection);
	     }

	  }
	  if (axis==1) {  /* Y */
	     if (jdirection>20000) {
		keys_down|=DOWN_PRESSED;
	     }
	     else if (jdirection<-20000) {
		keys_down|=UP_PRESSED;
	     }
	     else if ((jdirection>5000) || (jdirection<-5000)) {
		keys_down&=(~UP_PRESSED);
		keys_down&=(~DOWN_PRESSED);
//			     printf("Y: %i\n",jdirection);
	     }
	     
	     
//	     printf("Y: %i\n",jdirection);
	  }
	  
       }
       
       
       if (event.type == SDL_JOYBUTTONUP) {
	  button=event.jbutton.button;
	  switch(button) {
	     case 0: keys_down&=(~A_PRESSED);
	             break;
	     case 1: keys_down&=(~Z_PRESSED);
	             break;
	  }
	  //printf("Button: %i\n",button);
       }
       
       if (event.type == SDL_KEYUP) {
	  keypressed=event.key.keysym.sym;
	  
	  switch(keypressed) {
              case SDLK_UP: keys_down&=(~UP_PRESSED);	 
	                    break;
	      case SDLK_DOWN: keys_down&=(~DOWN_PRESSED);
	                    break;
	      case SDLK_RIGHT: keys_down&=(~RIGHT_PRESSED);
	                    break;
	     case SDLK_LEFT: keys_down&=(~LEFT_PRESSED);
	                    break;
	   case 'a': case 'A': keys_down&=(~A_PRESSED); break;
	   case 'z': case 'Z': keys_down&=(~Z_PRESSED); break;
	  }
       }
       
       if ( event.type == SDL_KEYDOWN ) {
	  keypressed=event.key.keysym.sym;
	   
	  switch (keypressed) {
	   case 'L':
	   case 'l': *alphanum='l'; break;
	     

	   case 'k': case 'K':
	             *alphanum='k';
	             break;
	   case 'j': case 'J':
	             *alphanum='j';
	             break;
	   case 'm': case 'M':
	             *alphanum='m';
	             break;
	   case 'i': case 'I':
	             *alphanum='i';
	             break;

	   case 'P': case 'p':
	             *alphanum='p';
	             break;
	     
	   case 'a': case 'A':
	                     momentary|=A_PRESSED;
	                     keys_down|=A_PRESSED;
	                     break;
	     
	   case 'z': case 'Z':
	                     momentary|=Z_PRESSED;
	                     keys_down|=Z_PRESSED;
	                     break;  
	     
	   case SDLK_ESCAPE: keys_down|=ESC_PRESSED; 
	                     return 1;  
	                     break;
	   case SDLK_RIGHT:  momentary|=RIGHT_PRESSED;
                             keys_down|=RIGHT_PRESSED;	                     
                             break;
           case SDLK_LEFT:   momentary|=LEFT_PRESSED;
	                     keys_down|=LEFT_PRESSED;
                             break;
           case SDLK_UP:     
	                     momentary|=UP_PRESSED;
	                     keys_down|=UP_PRESSED;
	                     break;
	   case SDLK_DOWN:   momentary|=DOWN_PRESSED;
	                     keys_down|=DOWN_PRESSED;
                             break;
	  }
       }
    }
    return (momentary<<16)+keys_down;
}
