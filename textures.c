#include <GL/gl.h>
#include <GL/glu.h>

#include "textures.h"
#include "vmw_texture.h"

GLuint textures[TOTAL_TEXTURES];

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

void LoadAlphaTexture(int x,int y,char *filename,int which_one,int transparent,
		 int repeat_type,int r,int g,int b) {


    static GLubyte *texture;
   
    
    texture=vmwLoadAlphaTexture(x,y,texture,filename,r,g,b);
    
    glBindTexture(GL_TEXTURE_2D,textures[which_one]);
   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x,
		 y ,0,GL_RGBA,GL_UNSIGNED_BYTE,texture);
   
}

