/* Implements the font handling of the Super VMW Graph Library */

#include <GL/gl.h>

#include <stdio.h>  /* For File I/O */
#include <stdlib.h> /* For malloc/calloc */

/* The font used is a standard VGA font.          */
/* To use the "smallText" functions, the VGA font */
/*    has to have a smaller (4x5) version of the  */
/*    font from chars 0-127 mirrored at 128-255   */

GLubyte *font;

GLubyte high,low;

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


void vmwGLString(char *st,GLubyte *font,int xsize,int ysize) {
   
   int i,len;
   
   len=strlen(st);
   for(i=0;i<len;i++) {
      glBitmap(font_xsize,font_ysize,0.0,0.0,
	       font_xsize+1,0.0,font+(st[i]*font_ysize*font_scale));
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
