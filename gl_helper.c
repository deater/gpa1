#include <GL/gl.h>
#include <GL/glu.h>

void reshape(int w,int h) {
   glViewport(0,0,(GLsizei)w,(GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //glTranslatef(0.0,0.0,-3.6);
}

