#define CARROT_TEXTURE            0
#define EYE_TEXTURE               1
#define ROBOT_FACE_TEXTURE        2
#define GRASS_TEXTURE             3
#define LEAVES_TEXTURE            4
#define NOSE_TEXTURE              5
#define SKY_TEXTURE               6
#define BROWN_TEXTURE             7
#define BROWN_WHITE_BROWN_TEXTURE 8
#define FLESH_TEXTURE             9
#define OCEAN_TEXTURE		 10
#define MOUNTAIN_TEXTURE	 11
#define CLIFF_TEXTURE            12
#define FOREST_TEXTURE           13
#define SAND_TEXTURE             14
#define SHALLOW_TEXTURE          15
#define TUNDRA_TEXTURE           16
#define SS_GRAY                  17
#define SS_TOP                   18
#define SS_BOTTOM                19
#define SS_THRUST                20
#define SS_NOTHRUST              21
#define SS_LEFT                  22
#define SS_RIGHT                 23
#define SS_BACK                  24
#define SHADOW_TEXTURE		 25
#define SPLASH_TEXTURE		 26
#define TOTAL_TEXTURES 27

extern GLuint textures[];

void LoadTexture(int x,int y,char *filename,int which_one,int transparent,
		 int repeat_type);

void LoadAlphaTexture(int x,int y,char *filename,int which_one,int transparent,
		 int repeat_type,int r,int g,int b);
