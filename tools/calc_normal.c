#include <stdio.h>

#define GLfloat float

#include "matrix_math.h"

int main(int argc,char **argv) {
 
   float x1,y1,z1,x2,y2,z2,x3,y3,z3;
   float xresult,yresult,zresult;
   
   scanf("%f %f %f %f %f %f %f %f %f",&x1,&y1,&z1,&x2,&y2,&z2,&x3,&y3,&z3);
   
   calculate_normal(x1,y1,z1,x2,y2,z2,x3,y3,z3,&xresult,&yresult,&zresult);
   
   printf("%f %f %f\n",xresult,yresult,zresult);
      
   return 0;
   
}
