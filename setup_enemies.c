void draw_robo_pig(float pigx,float pigy,float pigz,float direction) {
   
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   
   glPushMatrix();

   
   glTranslatef(pigx,pigy,pigz);
   glRotatef(direction,0.0,0.0,1.0);
   
   glBindTexture(GL_TEXTURE_2D,texName[0]);
   
   
      /* Back */
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,1.0,-1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(-2.0,1.0,1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(-2.0,-1.0,1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,-1.0,-1.0);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,texName[1]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,1.0,-1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,1.0,-1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,1.0,1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,1.0,1.0);

   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,1.0,1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,1.0,1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,-1.0,1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,-1.0,1.0);

   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,-1.0,1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,-1.0,1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,-1.0,-1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,-1.0,-1.0);

   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,-1.0,-1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,-1.0,-1.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,1.0,-1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0,1.0,-1.0);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,texName[2]);
   glBegin(GL_QUADS);
   
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0,1.0,-1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(2.0,1.0,1.0);
   glTexCoord2f(0.0, 0.0); glVertex3f(2.0,-1.0,1.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(2.0,-1.0,-1.0);
   
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

   return;
}
