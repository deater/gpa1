#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793238462643383279502884197169399

#define D2R(x) ((x*PI)/180.0)

int main(int argc, char **argv) {
   
#ifdef DUMB
   int x=5,y=4;
   
   printf("x=%i y=%i\n",x,y);
   
   x=x^y;
   y=y^x;
   x=x^y;
   printf("x=%i y=%i\n",x,y);
#endif
   
   float x,y,z,rho=37.5,theta=0,phi=0;
   
   for(phi=-14.5;phi<14.5;phi+=1) {
      for(theta=-175;theta<175;theta+=10) {
         x=rho*sin(D2R(phi))*cos(D2R(theta));
         y=rho*sin(D2R(phi))*sin(D2R(theta));
	 z=rho*cos(D2R(phi));
         printf("%.2f %.2f %.2f\n",x,y,z);
      }
      printf("\n\n");
      
   }
   
   
   
}
