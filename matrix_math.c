#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


/*     xv,yv,zv vertex is the common vertex.
 *     x1,y1,z1 is end of vector 1
 *     x2,y2,z2 is end of vector 2
 *     vextor 2 should be counter-clockwise of vector1 due to right-hand-rule */ 

int calculate_normal(GLfloat xv,GLfloat yv,GLfloat zv, /* vertex */
		     GLfloat x1,GLfloat y1,GLfloat z1,
		     GLfloat x2,GLfloat y2,GLfloat z2,
		     GLfloat *result_x,GLfloat *result_y,GLfloat *result_z) {
 
    
   
    float vx,vy,vz,wx,wy,wz;
    
    float rx,ry,rz,length;
   
    vx=x1-xv;  vy=y1-yv;  vz=z1-zv;
    wx=x2-xv;  wy=y2-yv;  wz=z2-zv;
   
   
   /*
    *    |                      |
    *    |  vx     vy     vz    |  
    *    |                      |
    *    |  wx     wy     wz    |  = (vy*wz-wy*wz)i +  
    *    |                      |    (wx*vz-vx*wz)j +
    *    |  i       j      k    |    (vx*wy-wx*vy)k
    *    |                      |
    */
   
   
    rx=(vy*wz)-(wy*wz);
    ry=(wx*vz)-(vx*wz);
    rz=(vx*wy)-(wx*vy);
   
       /* NORMALIZE */
    length=sqrt((rx*rx)+(ry*ry)+(rz*rz));
   
    *result_x=rx/length;  *result_y=ry/length; *result_z=rz/length;
   
#ifdef DEBUG   
    printf("%f %f %f\n",*result_x,*result_y,*result_z);
#endif
   
    return 0;
    
}
