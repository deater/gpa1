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
#define WORLD_MAP_TEXTURE        27
#define MOON_MAP_TEXTURE         28
#define SUN_TEXTURE              29

#define TILE_ROOF_TEXTURE        30
#define TILE_DOOR_TEXTURE        31
#define TILE_WINDOW_TEXTURE      32
#define TILE_BLANK_TEXTURE       33
#define ARCTIC_ROOF_TEXTURE      34

#define ARCTIC_DOOR_TEXTURE      35
#define ARCTIC_WINDOW_TEXTURE    36
#define BUSHES_TEXTURE           37
#define DISINTEGRATE_TEXTURE     38
#define GREY_TEXTURE		 39

#define GREY_NOSE_TEXTURE	 40
#define GREY_EYE_TEXTURE	 41
#define DARK_SKIN_TEXTURE	 42
#define WHITE_TEXTURE		 43
#define WHITE_NOSE_TEXTURE	 44

#define ALBINO_EYE_TEXTURE	 45
#define TFV_FLESH_TEXTURE	 46
#define TFV_NAVY_TEXTURE	 47
#define TFV_JEANS_TEXTURE        48
#define TFV_SHOE_TEXTURE         49

#define TFV_FACE_TEXTURE         50
#define TFV_HAIR_TEXTURE	 51
#define TFV_LEFT_EAR_TEXTURE     52
#define TFV_RIGHT_EAR_TEXTURE    53
#define TFV_SWORD_TEXTURE        54

#define TFV_SWORD_ARROWS_TEXTURE 55
#define TFV_FACE2_TEXTURE        56
#define TFV_HAIR_BLACK_TEXTURE   57
#define TFV_FLESH2_TEXTURE       58
#define TFV_LIGHT_FLANNEL_TEXTURE 59

#define TFV_LEFT_EAR2_TEXTURE    60
#define TFV_RIGHT_EAR2_TEXTURE   61

#define TOTAL_TEXTURES 62

extern GLuint textures[];

void LoadTexture(int x,int y,char *filename,int which_one,int transparent,
		 int repeat_type);

void LoadAlphaTexture(int x,int y,char *filename,int which_one,int transparent,
		 int repeat_type,int r,int g,int b);
