#include <GL/gl.h>
#include "vmw_texture.h"

int main(int argc, char **argv) {
 
   GLubyte *texture;
   int i;
   
   texture=vmwLoadTexture(64,64,texture,"./textures/brown.amg",0);
   
   for(i=0;i<64;i++) printf("%i %i %i %i\n",*(texture+((0*64)+i*4)+0),
			    *(texture+((0*64*4)+i*4)+1),
			    *(texture+((0*64*4)+i*4)+2),
			    *(texture+((0*64*4)+i*4)+3));

			    
   
   return 0;
   
	    
   
}
