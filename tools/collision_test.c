#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793238462643383279502884197169399

#define D2R(x) (x*(PI/180.0)) 

int print_points(float x,float y,float direction,FILE *fff) {
   
   float x1,y1,xdelta,ydelta,theta;
   
   theta=D2R(direction);
   
//   printf("\n%f %f %f\n",x,y,direction);
   
   x1=sin(theta);
   y1=cos(theta);
   xdelta=(y1)/2;  /* 90 degrees out of phase */
   ydelta=(x1)/2;
   
   fprintf(fff,"%f %f\n", x1-xdelta, y1+ydelta);
   fprintf(fff,"%f %f\n", x1+xdelta, y1-ydelta);
   fprintf(fff,"%f %f\n",   -xdelta,   +ydelta);
   fprintf(fff,"%f %f\n",    xdelta,   -ydelta);
   fprintf(fff,"%f %f\n",-x1-xdelta,-y1+ydelta);
   fprintf(fff,"%f %f\n",-x1+xdelta,-y1-ydelta);
   fprintf(fff,"\n");
   return 1;
}

int main(int argc, char **argv) {
   
    float x,y,direction;
    FILE *ppp;
   
    //printf("Enter X,Y, and direction\n");
    //scanf("%f %f %f",&x,&y,&direction);
   
    x=0.0;y=0.0;
   
    for(direction=0.0;direction<360.0;direction+=10.0){
       ppp=popen("/usr/local/bin/gnuplot","w");
       fprintf(ppp,"set term gif size 128,128\n");
       fprintf(ppp,"set data style linespoints\n");
       fprintf(ppp,"set output \"%0.3f.gif\"\n",direction/1000.0);
       fprintf(ppp,"plot [-2:2] [-2:2] \"-\"\n");
       print_points(x,y,direction,ppp);
       fprintf(ppp,"e\n");
       fprintf(ppp,"quit\n");
       fclose(ppp);
    }
   return 0;  
}
