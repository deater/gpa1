/* All of my various attempts to get a useful display of text */
/* in openGL */

#include <GL/gl.h>

#include <stdio.h>  /* For File I/O */
#include <stdlib.h> /* For malloc/calloc */
#include <string.h> /* For strlen() */

/* The font used is a standard VGA font.          */
/* To use the "smallText" functions, the VGA font */
/*    has to have a smaller (4x5) version of the  */
/*    font from chars 0-127 mirrored at 128-255   */

GLubyte *font;

GLubyte high,low;

GLuint texture_font_list[144];
GLuint font_texture;
GLuint words_texture;


static int font_scale,font_xsize,font_ysize;

void double_size(GLubyte value) {

	int i;

	high=0; low=0;

	for(i=0;i<4;i++) {
		if ((value>>i)&1) {
			low|=3<<(i*2);
		}
	}

	for(i=0;i<4;i++) {
		if ((value>>(4+i))&1) {
			high|=3<<(i*2);
		}
	}
}


GLubyte *vmwLoadFont(char *namest,int xsize,int ysize,int numchars,int scale)
{
    unsigned char buff[16];
    FILE *f;
    int i,fonty,numloop;
    GLubyte *data;

    font_scale=scale;
    font_xsize=xsize*scale;
    font_ysize=ysize*scale;
   
    if ((scale<1) || (scale>2)) printf("Unsupported scale factor %i\n",scale);
   
    data=(GLubyte *)calloc(numchars*ysize*scale*scale,(sizeof(GLubyte)));
   
    f=fopen(namest,"r");
    if (f==NULL) {
       printf("ERROR loading font file %s.\n",namest);
       return NULL;
    }
    numloop=(numchars*ysize*scale*scale);
       
    fonty=0;
    while ( (!feof(f))&&(fonty<numloop)) {
       fread(buff,1,16,f);
       for(i=0;i<16;i++) {
          if (scale==1) data[fonty+(15-i)]=buff[i];
          if (scale==2) {
	     double_size(buff[i]);
	     data[fonty+(60-(i*4))]=high;
	     data[fonty+(61-(i*4))]=low;
	     data[fonty+(62-(i*4))]=high;
	     data[fonty+(63-(i*4))]=low;
	  }
       }
       fonty+=(ysize*scale*scale);	  
       
       
    }
       
    
    fclose(f);
    return data;
}


void vmwGLString(char *st,GLubyte *font) {
   
   int i,len;
   
   len=strlen(st);
   for(i=0;i<len;i++) {
      glBitmap(font_xsize,font_ysize,0.0,0.0,
	       font_xsize+1,0.0,font+(st[i]*font_ysize*font_scale));
   }
}

   /* font value 8 is a box */
void vmwGLShadowString(char *st,GLubyte *font) {
   
   int i,len;
   
   len=strlen(st);
   for(i=0;i<len;i++) {
      glBitmap(font_xsize,font_ysize,0.0,0.0,
	       font_xsize+1,0.0,font+(8*font_ysize*font_scale));
   }
}


#if 0

    /* Output a string at location x,y */   
void vmwTextXY(char *st,int x,int y,int col,int background,int overwrite,
	       vmwFont *font,vmwVisual *target)
{
    int lineon,i,xx,len;

    len=strlen(st);
    for(lineon=0;lineon<8;lineon++){
       for(i=0;i<len;i++)
	  for(xx=0;xx<8;xx++){
	     if ( (font->font_data[(st[i]*font->height)+lineon])&(128>>xx) )
		vmwPutPixel((x+(i*8)+xx),y+lineon,col,target);
	     else
	        if (overwrite) 
		   vmwPutPixel((x+(i*8)+xx),y+lineon,background,target);
	  }
     } 
}
   
    /* Assume this is a special font with a "small" font at locations   */
    /*       128-255 and display the string                             */
void vmwSmallTextXY(char *st,int x,int y,int col,int background,int overwrite,
		    vmwFont *font,vmwVisual *target)
{
    int lineon,i,xx,len;

     /* This will print out a small 4x5 font located in chars */
     /* 128-255 in a normal VGA font.  These are custom made  */
     /* fonts; they are non-standard */
   
    len=strlen(st);
    for(lineon=0;lineon<5;lineon++) {
       for(i=0;i<len;i++)
	  for(xx=0;xx<5;xx++) {
	     if ( (font->font_data[((st[i]+128)*font->height)+lineon])
		  &(128>>xx) )
	        vmwPutPixel((x+(i*5)+xx),y+lineon,col,target);
             else
	       if (overwrite) 
		  vmwPutPixel((x+(i*5)+xx),y+lineon,background,target);
	  }
    }
}

#endif
#if 0
int texture_outtext(char *string,GLuint texture) {
   
    static GLubyte texture_data[128][128][4];

    unsigned char buff[16];
    FILE *f;
    int i,j,row,col;
   
    f=fopen(filename,"r");
    if (f==NULL) {
       printf("ERROR loading font file %s.\n",filename);
       return -1;
    }

    for(i=0;i<128;i++) for (j=0;j<128;j++) {
       texture_data[i][j][0]=0;
       texture_data[i][j][1]=0;
       texture_data[i][j][2]=0;
       texture_data[i][j][3]=255;
    }
       
   
    for(row=0;row<12;row++) {
       for(col=0;col<12;col++) {
	  fread(buff,1,16,f);
	  for(j=0;j<8;j++) {
	     for(i=7;i>=0;i--) {
		if (buff[j]&(1<<i)) {
		   texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [0] =255;
		   texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [1] =255;
		   texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [2] =255;
		   texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [3] =255;
		}
		else {
		    texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [0] =0;
		    texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [1] =0;
		    texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [2] =0;
		    texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [3] =255;
		}
	     }
	  }
       }
    }
    
    fclose(f);

#ifdef BIG_ENDIAN
       glPixelStorei(GL_UNPACK_SWAP_BYTES,1);
#endif
   
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glGenTextures(1,&font_texture);
    glBindTexture(GL_TEXTURE_2D,font_texture);
   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128,
		   128 ,0,GL_RGBA,GL_UNSIGNED_BYTE,texture_data);

   

   
    for(j=0;j<12;j++) {
       for(i=0;i<12;i++) {
	  texture_font_list[j*12+i]=glGenLists(1);
	  glNewList(texture_font_list[j*12+i],GL_COMPILE);
	  glEnable(GL_TEXTURE_2D);  
	  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
          glBindTexture(GL_TEXTURE_2D,font_texture);
	  glBegin(GL_QUADS);

	    glNormal3f(0,0,1);
	    glTexCoord2f((j*9+9)/128.0,(i*9)/128.0);
	    glVertex3f(-0.5,0,-0.5);
	  glTexCoord2f( (j*9)/128.0 ,(i*9)/128.0);
	    glVertex3f(-0.5,0,0.5);
	  glTexCoord2f( (j*9)/128.0,(i*9+9)/128.0);
	    glVertex3f(0.5,0,0.5);
	  glTexCoord2f( (j*9+9)/128.0,(i*9+9)/128.0);
	    glVertex3f(0.5,0,-0.5);

	  	    glNormal3f(0,0,1);
	    glTexCoord2i((j*9+9),(i*9));
	    glVertex3f(-0.5,0,-0.5);
	  glTexCoord2i( (j*9) ,(i*9));
	    glVertex3f(-0.5,0,0.5);
	  glTexCoord2i( (j*9),(i*9+9));
	    glVertex3f(0.5,0,0.5);
	  glTexCoord2i( (j*9+9),(i*9+9));
	    glVertex3f(0.5,0,-0.5);

	  glDisable(GL_TEXTURE_2D);  
	  
	  glEnd();
	  glEndList();
	  
       }
       
    }
   
}
#endif

int setup_texture_font(char *filename) {

	static GLubyte texture_data[128][128][4];

	unsigned char buff[16];
	FILE *f;
	int i,j,row,col;

	f=fopen(filename,"r");
	if (f==NULL) {
		printf("ERROR loading font file %s.\n",filename);
		return -1;
	}

	for(i=0;i<128;i++) for (j=0;j<128;j++) {
		texture_data[i][j][0]=0;
		texture_data[i][j][1]=0;
		texture_data[i][j][2]=0;
		texture_data[i][j][3]=255;
	}

	for(row=0;row<12;row++) {
		for(col=0;col<12;col++) {
			fread(buff,1,16,f);
				for(j=0;j<8;j++) {
					for(i=7;i>=0;i--) {
		if (buff[j]&(1<<i)) {
			texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [0] =255;
			texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [1] =255;
			texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [2] =255;
			texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [3] =255;
		}
		else {
			texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [0] =0;
			texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [1] =0;
			texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [2] =0;
			texture_data[ (col*9)+(7-i) ] [ (row*9)+j ] [3] =255;
					}
				}
			}
		}
	}

	fclose(f);

#ifdef BIG_ENDIAN
	glPixelStorei(GL_UNPACK_SWAP_BYTES,1);
#endif

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&font_texture);
	glBindTexture(GL_TEXTURE_2D,font_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128,
		128 ,0,GL_RGBA,GL_UNSIGNED_BYTE,texture_data);

	for(j=0;j<12;j++) {
		for(i=0;i<12;i++) {
			texture_font_list[j*12+i]=glGenLists(1);
			glNewList(texture_font_list[j*12+i],GL_COMPILE);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D,font_texture);
			glBegin(GL_QUADS);

			glNormal3f(0,0,1);
			glTexCoord2f((j*9+9)/128.0,(i*9)/128.0);
			glVertex3f(-0.5,0,-0.5);
			glTexCoord2f( (j*9)/128.0 ,(i*9)/128.0);
			glVertex3f(-0.5,0,0.5);
			glTexCoord2f( (j*9)/128.0,(i*9+9)/128.0);
			glVertex3f(0.5,0,0.5);
			glTexCoord2f( (j*9+9)/128.0,(i*9+9)/128.0);
			glVertex3f(0.5,0,-0.5);
#if 0
			glNormal3f(0,0,1);
			glTexCoord2i((j*9+9),(i*9));
			glVertex3f(-0.5,0,-0.5);
			glTexCoord2i( (j*9) ,(i*9));
			glVertex3f(-0.5,0,0.5);
			glTexCoord2i( (j*9),(i*9+9));
			glVertex3f(0.5,0,0.5);
			glTexCoord2i( (j*9+9),(i*9+9));
			glVertex3f(0.5,0,-0.5);
#endif
			glDisable(GL_TEXTURE_2D);
			glEnd();
			glEndList();
		}
	}
	return 0;

}

int texture_put_string(char *string) {

	int i;

	for(i=0;i<strlen(string);i++) {
		glCallList(texture_font_list[(int)string[i]]);
		glTranslatef(1.0,0,0);
	}
	return 0;
}


