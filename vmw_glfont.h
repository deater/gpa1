GLubyte *vmwLoadFont(char *namest,int xsize,int ysize,int numchars,int scale);
void vmwGLString(char *st,GLubyte *font);
void vmwGLShadowString(char *st,GLubyte *font);
int setup_texture_font(char *filename);
int texture_put_string(char *string);
   
extern GLubyte *font;
extern GLuint texture_font_list[128];
extern GLuint font_texture;
extern GLuint words_texture;
