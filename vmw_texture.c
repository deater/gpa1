/* An implementation of my own legacy "PaintPro[gram] graphics format */

/* The format is seemingly very random, but it was sort of OK for */
/*     my skill level at the time */

/* Version 1 was just, in text ASCII, a list of COLOR followed on a 
 *    new line by num-across, a very primitive RLE [Run-Length-Encoding]
 *    Compression scheme [which I thought up on my own] */

/* Later versions supported 256 color mode, and made sure the BASIC
 *   loader worked */

/* There was an actual "PaintPro program, written in TurboPascal
 *   that was fairly decent considering.  It would edit in
 *   the EGA and VGA 16 color modes, and later mode13 320x200x256 */

/* The files were still pretty large, so Version 5 implemented
 *    "Packing", basically shoving the color and numacross into
 *    a 24 bit value.  This, along with block-reading rapidly
 *    reduced load times */

/* Version 6 added a fancy header, along with palette saving, and
 * an optimization of storing multiple 1-pixel runs in half the size.
 * Before this palette files were stored separately. */

/* The resulting file format is very similar [quite accidentally] to
 *    the PCX file format.  Why don't I make paintpro files obsolete?
 *    nostalgia mostly.  */

/* Paintpro files usually have the extension .AMG [AMazing Graphics,
 *    an inside joke], .PPP [Paint Pro Packed], .PRO, or .TB1 [from
 *    Tom Bombem */





#include <stdio.h>  /* For FILE I/O */
#include <string.h> /* For strncmp */
#include <fcntl.h>  /* for open()  */
#include <unistd.h> /* for lseek() */
#include <sys/stat.h> /* for file modes */


#include <GL/gl.h>


   /* Take a 24bit value [3 bytes] and split the top and bottom */
   /* 12 bits into 2 integers */
#define THREE_BYTES_INT1(a,b)   ( ( ( (int)(a))<<4)+ ((b)>>4) )
#define THREE_BYTES_INT2(b,c)   ( ( ( ( (int)(b))&0x0f)<<8)+ (c)) 

   /* Do the opposite.  Take 2 ints and make 3 bytes */

#define TWO_INTS_THREE_BYTES(a,b)  three_bytes[0]=((unsigned char)(((a)>>4)&0xff)); three_bytes[1]=((unsigned char) ( (((a)&0x0f)<<4)+(((b)>>8)&0x0f))); three_bytes[2]=((unsigned char)((b)&0xff));


typedef struct {
      char ppro_string[8];
      char version[4];
      int xsize;
      int ysize;
      int num_colors;
} vmwPaintProHeader;


#define VMW_ERROR_FILE    2
#define VMW_ERROR_INVALID 5

    unsigned char palette[256][3];


static int texture_x=0,texture_y=0,texture_alpha=0;

int vmwPutPixel(int x,int y,int color,GLubyte *texture) {
 
   
   if ((x<texture_x) && (y<texture_y)) {
//      printf("%i : %i\n",(y*(64*4))+x,palette[color][0]);
	     
      texture[(y*(texture_x*4))+(x*4)]=palette[color][0];
      texture[(y*(texture_x*4))+(x*4)+1]=palette[color][1];
      texture[(y*(texture_x*4))+(x*4)+2]=palette[color][2];
      if (texture_alpha && color==0) texture[(y*(texture_x*4))+(x*4)+3]=0;
      else texture[(y*(texture_x*4))+(x*4)+3]=255;
   }
}


int vmwDrawHLine(int x,int y,int run,int color,GLubyte *target) {
   
   int i;
   
   for(i=0;i<run;i++) {
      vmwPutPixel(x+i,y,color,target);  
      
   }
   
}

vmwPaintProHeader *vmwGetPaintProHeader(char *filename) {
 
    FILE *fff;
    static vmwPaintProHeader *header=NULL;
    unsigned char buffer[18];
    int i;
   
    if ( (fff=fopen(filename,"rb"))==NULL) {  /* b for w32 stupidity */
       printf("Error!  %s does not exist!\n",filename);
       return NULL;
    }
        
    if (fread(buffer,1,18,fff)!=18) {
       printf("Error!  Corrupted paintpro header!\n");
       return NULL;
    }
   
    fclose(fff);
   
    if (header==NULL) {
       if (( header=(vmwPaintProHeader *)calloc(1,sizeof(vmwPaintProHeader)))==NULL) {
          printf("Error!  Seriously low on memory!\n");
          return NULL;
       }
    }
    
       /* Load PAINTPRO string */
   for(i=0;i<8;i++) header->ppro_string[i]=buffer[i];
   for(i=0;i<4;i++) header->version[i]=buffer[i+8];   
   header->xsize=THREE_BYTES_INT1(buffer[12],buffer[13]);
   header->ysize=THREE_BYTES_INT2(buffer[13],buffer[14]);
   header->num_colors=THREE_BYTES_INT1(buffer[15],buffer[16]);
   
   return header;
}

    /*---------------------------------------------------------------*\
    |    vmwLoadPicPacked                                             |
    |  There is so much history in this function, I won't get into    |
    |       it here.  See the paintpro documentation found elsewhere  |
    \*---------------------------------------------------------------*/


GLubyte *vmwLoadTexture(int x1,int y1,GLubyte *texture,char *FileName,int alpha) 

  /* Retro comments */
/*{ Loads a paintpro image, filename, at location x1,y1      *\
\*  to offset where (vga=$A000) and loadspal if LOADPAL=true */
/*  Loadsapicture if Loadpic=true and returns error}         */

{

    int x,y,i;
    int ppro_fd;
    int color,numacross;
    int read_status;
    vmwPaintProHeader *ppro_header;
    unsigned char three_bytes[3];
    int broken=0;

    GLubyte *target;

   
    texture_x=x1; texture_y=y1; texture_alpha=alpha;
   
    if ( (ppro_header=vmwGetPaintProHeader(FileName))==NULL) {
       printf("ERROR!  Invalid Header in %s!\n",FileName);
       return NULL;
    }   
   

    texture=(GLubyte *)calloc(x1*y1*4,sizeof(GLubyte));
   
    target=texture;
   
       /* Open the file */                  
    ppro_fd=open(FileName,O_RDONLY);
    
    if (ppro_fd<0) {
       printf("ERROR!  File \"%s\" not found!\n",FileName);
       return NULL;
    }
   
       /* Check to see if its really a Paintpro File */
    if (strncmp(ppro_header->ppro_string,"PAINTPRO",8)) {
       printf("ERROR!  %s is NOT a paintpro file!\n",FileName);
       return NULL;
    }

       /* Check to see if it is the proper version (currently 6.0) */
    if (strncmp(ppro_header->version,"V6.1",4)) {
       if (!strncmp(ppro_header->version,"V6.0",4)) {
	  printf("Warning!  Broken 6.0 file! Please convert.\n");
	  broken=1;
       }
       else {
          printf("ERROR! %s unsupported, must be >=6.0\n",
	         ppro_header->version);
          return NULL;
       }
    }
      
       /*Load Palette*/
    if (ppro_header->num_colors>256) 
       printf("More than 256 colors not supported yet (%d)\n",
	      ppro_header->num_colors);
   
       /* Seek past the header */
    lseek(ppro_fd,18,SEEK_SET);
   
       /* Fun and games to convert the 24 bit color in paintpro to */
       /* 565 packed 16bit RGB */

       for(i=0;i<ppro_header->num_colors;i++) { 
          read_status=read(ppro_fd,&three_bytes,3);
	  palette[i][0]=three_bytes[0];
	  palette[i][1]=three_bytes[1];
	  palette[i][2]=three_bytes[2];
       }

   
   
    x=0;
    y=0;

    while (y<ppro_header->ysize) {
          /* Read in next 3 bytes */
       read_status=read(ppro_fd,&three_bytes,3);
       
          /* If we read less than 3, something is wrong */
       if (read_status<3) {
	  printf("Ran out of data too soon!\n");
	  break;
       }
       
       color=THREE_BYTES_INT1(three_bytes[0],three_bytes[1]);
       numacross=THREE_BYTES_INT2(three_bytes[1],three_bytes[2]);
       
          /* If int1 greater than 2047, we have two single pixels */
          /* of color int1-2048 and int2-2048                    */
       if (color>2047) {
	  if ((x<texture_x) && (y<texture_y))
          vmwPutPixel(x,y,color-2048,target);
          x++;
          if (x>=ppro_header->xsize) {
	     x=0; y++;
	  }
          vmwPutPixel(x,y,numacross-2048,target);
          x++;
          if (x>=ppro_header->xsize){
	     x=0;y++;
	  }
       }
       else {  /* Standard paintpro format */
	     /* Wrap if numacross is bigger than width */
          while ((x+numacross)>=(ppro_header->xsize)) {
	     vmwDrawHLine(x,y,((ppro_header->xsize)-x),color,target);
                /* Old versions of paintro created broken   */
	        /* Files which need an extra +1 after xsize */
	        /* In the following line */
	     numacross=numacross-((ppro_header->xsize+broken)-x);
	     x=0;
	     y++;
          }
	  
          if (numacross!=0) {
	     if (y>=ppro_header->ysize) {
		printf("Trying to draw past end of screen %d\n",y);
	     }
	     if (numacross > ppro_header->xsize-1) {
		printf("X too big?%d\n",numacross);
	     }
	     vmwDrawHLine(x,y,numacross,color,target);
	  }
          x=x+numacross;
       }
    }
    close(ppro_fd);
    return texture;
}
