#include <SDL/SDL.h>

int main(int argc, char **argv) {
   

    int frames=0;
    int triangle,done=0,original_msecs=0,current_msecs=0;
    int time_passed;

       if ( SDL_Init(0)<0) {
	        printf("Error trying to init SDL: %s\n",SDL_GetError());
	        return -1;
       }
   
   
   
    original_msecs=SDL_GetTicks();

    while (!done) {
//       usleep(1);
       current_msecs=SDL_GetTicks();

       time_passed=(current_msecs-original_msecs);
       printf("%i\n",time_passed);
       

       
       if (time_passed>1000) done=1;    
    }
}
