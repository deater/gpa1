void draw_carrot(float carrotx,float carroty,float carrotz,float direction) {
   
   glPushMatrix();

   glTranslatef(carrotx,carroty,carrotz);
   glRotatef(direction,0.0,0.0,1.0);
   
   glColor3f(0.9961,0.6445,0);
   
   glBegin(GL_TRIANGLES);
    
      glVertex3f(0.0,-0.5,0.5);
      glVertex3f(2.0,0,0.5);
      glVertex3f(0.0,0.5,0.5);
   
      glVertex3f(0.0,0.5,0.5);
      glVertex3f(2.0,0,0.5);
      glVertex3f(0.0,0.5,-0.5);
   
      glVertex3f(0.0,0.5,-0.5);
      glVertex3f(2.0,0,0.5);
      glVertex3f(0.0,-0.5,-0.5);
   
   
      glVertex3f(0.0,-0.5,-0.5);
      glVertex3f(2.0,0,0.5);
      glVertex3f(0.0,-0.5,0.5);
   
      /* TOP */
   
      glVertex3f(0.0,-0.5,0.5);
      glVertex3f(0.0,0.5,0.5);
      glVertex3f(0.0,0.5,-0.5);
   
   
      glVertex3f(0.0,0.5,-0.5);
      glVertex3f(0.0,-0.5,-0.5);
      glVertex3f(0.0,-0.5,0.5);
   
   
   glEnd();
   

   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   
   glBindTexture(GL_TEXTURE_2D,texName[5]);   
     glBegin(GL_QUADS);
   
     glTexCoord2f(0.0,0.0);
     glVertex3f(0.0,0.0,0.5);
     glTexCoord2f(0.0,1.0);
     glVertex3f(0.0,0.0,-0.5);
     glTexCoord2f(1.0,1.0);
     glVertex3f(-2.0,0.0,-0.5);
     glTexCoord2f(1.0,0.0);
     glVertex3f(-2.0,0.0,0.5);

     glTexCoord2f(0.0,0.0);
     glVertex3f(0.0,0.5,0.0);
     glTexCoord2f(0.0,1.0);
     glVertex3f(0.0,-0.5,0.5);
     glTexCoord2f(1.0,1.0);
     glVertex3f(-2.0,-0.5,0.0);
     glTexCoord2f(1.0,0.0);
     glVertex3f(-2.0,0.5,0.0);
   
   
   
     glEnd();
   
   
   glDisable(GL_TEXTURE_2D);
   
   
   
   
   glPopMatrix();
   
}
