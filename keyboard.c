#include <SDL/SDL.h>

#include "keyboard.h"

/* MODEL ->  We pretend we essentially have essentially 10 buttons */
/* Right now this reflects the Gravis-Gamepad I have.  Eventually */
/* I will add some sort of generic config utility for custom controls */

/* UP, DOWN, LEFT, RIGHT */
/* 1 (A or ACTION1)
 * 2 (Z or ACTION2)
 * 3 (ENTER or CONFIRM)
 * 4 (SPACE or CANCEL)
 * 5 (J or PAN_LEFT)
 * 6 (K or PAN_RIGHT)
 * 9 (P or PAUSE)
 *10 (ESCAPE or MENU)
*/


int check_keyboard(char *alphanum,int reset) {
   
    SDL_Event event;
   
    static int keys_down=0;
    int momentary=0;
    int button,axis,jdirection;
   
    int keypressed;

    *alphanum=0;
   
    if (reset) {
       keys_down=0;
       return 1;
    }
        
    while ( SDL_PollEvent(&event) ) {
       
       if ( event.type == SDL_QUIT ) {
          keys_down|=MENU_PRESSED;
	  return 1;
       }

       if (event.type == SDL_VIDEORESIZE) {
	  printf("RESIZE\b");	  
       }
       
       if (event.type == SDL_JOYBUTTONDOWN) {
	  button=event.jbutton.button;
	  switch(button) {
	     case 0: momentary|=ACTION1_PRESSED;
	             keys_down|=ACTION1_PRESSED;
	             break;
	     case 1: momentary|=ACTION2_PRESSED;
	             keys_down|=ACTION2_PRESSED;
	             break;
	     case 2: momentary|=CONFIRM_PRESSED;
	             keys_down|=CONFIRM_PRESSED;
	             break;
	     case 3: momentary|=CANCEL_PRESSED;
	             keys_down|=CANCEL_PRESSED;
	             break;
	     case 4: momentary|=PAN_LEFT_PRESSED;
	             keys_down|=PAN_LEFT_PRESSED;
	             break;
	     case 5: momentary|=PAN_RIGHT_PRESSED;
	             keys_down|=PAN_RIGHT_PRESSED;
	             break;
	     case 8: momentary|=PAUSE_PRESSED;
	             keys_down|=PAUSE_PRESSED;
	             break;
	     case 9: momentary|=MENU_PRESSED;
	             keys_down|=MENU_PRESSED;
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
	     case 0: keys_down&=(~ACTION1_PRESSED);
	             break;
	     case 1: keys_down&=(~ACTION2_PRESSED);
	             break;
	     case 2: keys_down&=(~CONFIRM_PRESSED);
	             break;
	     case 3: keys_down&=(~CANCEL_PRESSED);
	             break;
	     case 4: keys_down&=(~PAN_LEFT_PRESSED);
	             break;
	     case 5: keys_down&=(~PAN_RIGHT_PRESSED);
	             break;
	     case 8: keys_down&=(~PAUSE_PRESSED);
	             break;
	    case  9: keys_down&=(~MENU_PRESSED);
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
	     case SDLK_ESCAPE: keys_down&=(~MENU_PRESSED); 
	                    break;
	     case SDLK_RETURN:  keys_down&=(~CONFIRM_PRESSED);
	      		    break;
	     case SDLK_SPACE: keys_down&=(~CANCEL_PRESSED);
	                    break;
	     
	   case 'a': case 'A': keys_down&=(~ACTION1_PRESSED); break;
	   case 'z': case 'Z': keys_down&=(~ACTION2_PRESSED); break;
	   case 'j': case 'J': keys_down&=(~PAN_LEFT_PRESSED); break;
	   case 'k': case 'K': keys_down&=(~PAN_RIGHT_PRESSED); break;
	   case 'p': case 'P': keys_down&=(~PAUSE_PRESSED); break;
	  }
       }
       
       if ( event.type == SDL_KEYDOWN ) {
	  keypressed=event.key.keysym.sym;
	   
	  switch (keypressed) {
	      
	   case 'a': case 'A':
	                     momentary|=ACTION1_PRESSED;
	                     keys_down|=ACTION1_PRESSED;
	                     break;
	     
	   case 'z': case 'Z':
	                     momentary|=ACTION2_PRESSED;
	                     keys_down|=ACTION2_PRESSED;
	                     break;  
	     
	   case SDLK_RETURN: momentary|=CONFIRM_PRESSED;
	                     keys_down|=CONFIRM_PRESSED;
	                     break;
	   case SDLK_SPACE:  momentary|=CANCEL_PRESSED;
	                     keys_down|=CANCEL_PRESSED;
	                     break;
	   case 'j': case 'J':
	                     momentary|=PAN_LEFT_PRESSED;
	                     keys_down|=PAN_LEFT_PRESSED;
	                     break;
	   case 'k': case 'K':
	                     momentary|=PAN_RIGHT_PRESSED;
	                     keys_down|=PAN_RIGHT_PRESSED;
	                     break;
	   case 'p': case 'P':
	                     momentary|=PAUSE_PRESSED;
	                     keys_down|=PAUSE_PRESSED;
	                     break;
	   case SDLK_ESCAPE: momentary|=MENU_PRESSED;
	                     keys_down|=MENU_PRESSED; 
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
	     
	   default:  *alphanum=keypressed; break;
	  }
       }
    }
    return (momentary<<16)+keys_down;
}
