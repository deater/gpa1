#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vmw_texture.h"

#define PI 3.141592653589793238462643383279502884197169399
  

#define checkImageWidth 64
#define checkImageHeight 64


static GLubyte texture1[checkImageHeight][checkImageWidth][4];
static GLubyte texture2[checkImageHeight][checkImageWidth][4];

static GLubyte *texture3,*eye_texture,*nose_texture,*leaf_texture;


static GLuint texName[6];


float direction=0.0,pigx=0.0,pigy=0.0,pigz=1.0;


void LoadTextures(void) {
   int i,j;


   
   
   
   texture3=vmwLoadTexture(64,64,texture3,"bob.amg",0);
   
   eye_texture=vmwLoadTexture(16,16,eye_texture,"eye.amg",0);
   
   nose_texture=vmwLoadTexture(16,16,nose_texture,"nose.amg",0);
   
   leaf_texture=vmwLoadTexture(64,64,leaf_texture,"leaves.amg",1);
   
   
   for(i=0;i<checkImageHeight;i++) {
      for (j=0;j<checkImageWidth;j++) {
      texture1[i][j][0]=(GLubyte) 0xcd;
      texture1[i][j][1]=(GLubyte) 0x81;
      texture1[i][j][2]=(GLubyte) 0x62;
      texture1[i][j][3]=(GLubyte) 255;
	 
      if ((i<20) || (i>40)) {
         texture2[i][j][0]=(GLubyte) 0xcd;
         texture2[i][j][1]=(GLubyte) 0x81;
         texture2[i][j][2]=(GLubyte) 0x62;
      }
	 
      else {
	 texture2[i][j][0]=(GLubyte) 0xFF;
         texture2[i][j][1]=(GLubyte) 0xFF;
         texture2[i][j][2]=(GLubyte) 0xFF;
      }
      texture2[i][j][3]=(GLubyte) 255;
	 
	 
	 
      }
   }
}

void init(void) {
   glClearColor(0.0,0.0,0.0,0.0);
   glShadeModel(GL_SMOOTH);
//   glEnable(GL_LIGHTING);
//   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   LoadTextures();
   glPixelStorei(GL_UNPACK_ALIGNMENT,1);
   
   glGenTextures(6,texName);
   
   glBindTexture(GL_TEXTURE_2D,texName[0]);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
		checkImageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,texture1);
   
   glBindTexture(GL_TEXTURE_2D,texName[1]);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
		checkImageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,texture2);
   
   glBindTexture(GL_TEXTURE_2D,texName[2]);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
		checkImageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,texture3);
      
   glBindTexture(GL_TEXTURE_2D,texName[3]);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16,
		16,0,GL_RGBA,GL_UNSIGNED_BYTE,eye_texture);
      
   glBindTexture(GL_TEXTURE_2D,texName[4]);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16,
		16,0,GL_RGBA,GL_UNSIGNED_BYTE,nose_texture);
   
   
      glBindTexture(GL_TEXTURE_2D,texName[5]);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64,
		64,0,GL_RGBA,GL_UNSIGNED_BYTE,leaf_texture);
}



float pig_cylinder[16][2]={
   
     {0.42694, 0.191342},
     {0.318553, 0.353553},
     {0.156342, 0.46194},
     {-0.035, 0.5},
     {-0.226342, 0.46194},
     {-0.388553, 0.353553},
     {-0.49694, 0.191342},
     {-0.535, 0},
     {-0.49694, -0.191342},
     {-0.388554, -0.353553},
     {-0.226342, -0.46194},
     {-0.0350001, -0.5},
     {0.156342, -0.46194},
     {0.318553, -0.353553},
     {0.42694, -0.191342},
     {0.465, 2.68221e-07}
};

float pig_hemisphere[153][3]={

{0.015,	 	0.5, -0.94},
{0.015, 	0.46, -1.16},
{0.015, 	0.33, -1.32},
{0.015, 	0.17, -1.41},
{0.015, 	-0.02, -1.44},
{0.015, 	-0.18, -1.42},
{0.015, 	-0.35, -1.33},
{0.015, 	-0.47, -1.17},
{0.015, 	-0.5 ,-0.96},
{0.206342, 	0.46194, -0.94},
{0.191034, 	0.424985, -1.16},
{0.141286, 	0.30488, -1.32},
{0.0800562, 	0.15706, -1.41},
{0.00734633, 	-0.0184776, -1.44},
{-0.0538831, 	-0.166298, -1.42},
{-0.118939 ,	-0.323358, -1.33},
{-0.164861, 	-0.434223, -1.17},
{-0.176342, 	-0.46194, -0.96},
{0.368553,	 0.353553, -0.94},
{0.340269,	 0.325269, -1.16},
{0.248345,	 0.233345, -1.32},
{0.135208,	 0.120208, -1.41},
{0.00085783,	 -0.0141421, -1.44},
{-0.112279,	 -0.127279 ,-1.42},
{-0.232487,	 -0.247487, -1.33},
{-0.31734,	 -0.33234, -1.17},
{-0.338553,	 -0.353553, -0.96},
{0.47694,	 0.191342, -0.94},
{0.439985,	 0.176034, -1.16},
{0.31988,	 0.126286, -1.32},
{0.17206,	 0.0650562, -1.41},
{-0.00347757,	 -0.00765367, -1.44},
{-0.151298,	 -0.068883, -1.42},
{-0.308358,	 -0.133939, -1.33},
{-0.419223,	 -0.179861, -1.17},
{-0.44694,	 -0.191342, -0.96},
{0.515,		 -2.18557e-08, -0.94},
{0.475,		 -2.01072e-08, -1.16},
{0.345,		 -1.44248e-08, -1.32},
{0.185,		 -7.43094e-09, -1.41},
{-0.00500005,	 8.74228e-10, -1.44},
{-0.165,	 7.86805e-09, -1.42},
{-0.335,	 1.5299e-08, -1.33},
{-0.455,	 2.05444e-08, -1.17},
{-0.485,	 2.18557e-08, -0.96},
{0.47694,	 -0.191342, -0.94},
{0.439985,	 -0.176034, -1.16},
{0.31988,	 -0.126286, -1.32},
{0.17206,	 -0.0650562, -1.41},
{-0.00347757,	 0.00765367, -1.44},
{-0.151298,	 0.068883, -1.42},
{-0.308358,	 0.133939, -1.33},
{-0.419223,	 0.179861, -1.17},
{-0.44694,	 0.191342, -0.96},
{0.368553,	 -0.353553, -0.94},
{0.340269,	 -0.325269, -1.16},
{0.248345,	 -0.233345, -1.32},
{0.135208,	 -0.120208, -1.41},
{0.00085783,	 0.0141421, -1.44},
{-0.112279,	 0.127279 ,-1.42},
{-0.232487,	 0.247487, -1.33},
{-0.31734,	 0.33234, -1.17},
{-0.338553,	 0.353553, -0.96},
{0.206342,	 -0.46194, -0.94},
{0.191034,	 -0.424985, -1.16},
{0.141285,	 -0.30488, -1.32},
{0.0800561,	 -0.15706, -1.41},
{0.00734633,	 0.0184776, -1.44},
{-0.053883,	 0.166298, -1.42},
{-0.118939,	 0.323358, -1.33},
{-0.164861,	 0.434223, -1.17},
{-0.176342,	 0.46194, -0.96},
{0.0149999,	 -0.5, -0.94},
{0.0149999,	 -0.46, -1.16},
{0.015,		 -0.33, -1.32},
{0.015,		 -0.17, -1.41},
{0.015,		 0.02, -1.44},
{0.015,		 0.18, -1.42},
{0.015,		 0.35, -1.33},
{0.015,		 0.47, -1.17},
{0.015,		 0.5 ,-0.96},
{-0.176342,	 -0.46194, -0.94},
{-0.161034,	 -0.424985, -1.16},
{-0.111286,	 -0.30488, -1.32},
{-0.0500562,	 -0.15706, -1.41},
{0.0226536,	 0.0184776, -1.44},
{0.083883,	 0.166298, -1.42},
{0.148939,	 0.323358, -1.33},
{0.194861,	 0.434223, -1.17},
{0.206342,	 0.46194, -0.96},
{-0.338553,	 -0.353553, -0.94},
{-0.310269,	 -0.325269, -1.16},
{-0.218345,	 -0.233345, -1.32},
{-0.105208,	 -0.120208, -1.41},
{0.0291421,	 0.0141421, -1.44},
{0.142279,	 0.127279, -1.42},
{0.262487,	 0.247487, -1.33},
{0.34734,	 0.33234, -1.17},
{0.368553,	 0.353553, -0.96},
{-0.44694,	 -0.191342, -0.94},
{-0.409985,	 -0.176034, -1.16},
{-0.28988,	 -0.126285, -1.32},
{-0.14206,	 -0.0650561, -1.41},
{0.0334776,	 0.00765366, -1.44},
{0.181298,	 0.068883, -1.42},
{0.338358,	 0.133939, -1.33},
{0.449223,	 0.179861, -1.17},
{0.47694,	 0.191342, -0.96},
{-0.485,	 5.96244e-09, -0.94},
{-0.445,	 5.48544e-09, -1.16},
{-0.315,	 3.93521e-09, -1.32},
{-0.155,	 2.02723e-09, -1.41},
{0.035,		 -2.38498e-10, -1.44},
{0.195,		 -2.14648e-09, -1.42},
{0.365,		 -4.17371e-09, -1.33},
{0.485,		 -5.60469e-09, -1.17},
{0.515,		 -5.96244e-09, -0.96},
{-0.44694,	  0.191342, -0.94},
{-0.409985,	 0.176034, -1.16},
{-0.28988,	 0.126286, -1.32},
{-0.14206,	 0.0650562, -1.41},
{0.0334775,	 -0.00765367, -1.44},
{0.181298,	 -0.0688831, -1.42},
{0.338358,	 -0.133939, -1.33},
{0.449223,	 -0.179861, -1.17},
{0.47694,	 -0.191342, -0.96},
{-0.338553,	 0.353554, -0.94},
{-0.310269,	 0.325269, -1.16},
{-0.218345,	 0.233345, -1.32},
{-0.105208,	 0.120208, -1.41},
{0.0291421,	 -0.0141421, -1.44},
{0.142279,	 -0.127279, -1.42},
{0.262487,	 -0.247487, -1.33},
{0.34734,	 -0.33234, -1.17},
{0.368553,	 -0.353554, -0.96},
{-0.176342,	 0.46194, -0.94},
{-0.161034,	 0.424985, -1.16},
{-0.111286,	 0.30488, -1.32},
{-0.0500562,	 0.15706, -1.41},
{0.0226536,	 -0.0184776, -1.44},
{0.083883,	 -0.166298 ,-1.42},
{0.148939,	 -0.323358, -1.33},
{0.194861,	 -0.434223, -1.17},
{0.206342,	 -0.46194, -0.96},
{0.015,		 0.5 ,-0.94},
{0.015,		 0.46, -1.16},
{0.015,		 0.33, -1.32},
{0.015,		 0.17, -1.41},
{0.015,		 -0.02, -1.44},
{0.0149999,	 -0.18, -1.42},
{0.0149999,	 -0.35, -1.33},
{0.0149999,	  -0.47, -1.17},
{0.0149999,	 -0.5, -0.96}
};


int pig_hemisphere_triangles[128][4]={
{0, 9, 10, 1},
{1, 10, 11, 2},
{2, 11, 12, 3},
{3, 12, 13, 4},
{4, 13, 14, 5},
{5, 14, 15, 6},
{6, 15, 16, 7},
{7, 16, 17, 8},
{9, 18, 19, 10},
{10, 19, 20, 11},
{11, 20, 21, 12},
{12, 21, 22, 13},
{13, 22, 23, 14},
{14, 23, 24, 15},
{15, 24, 25, 16},
{16, 25, 26, 17},
{18, 27, 28, 19},
{19, 28, 29, 20},
{20, 29, 30, 21},
{21, 30, 31, 22},
{22, 31, 32, 23},
{23, 32, 33, 24},
{24, 33, 34, 25},
{25, 34, 35, 26},
{27, 36, 37, 28},
{28, 37, 38, 29},
{29, 38, 39, 30},
{30, 39, 40, 31},
{31, 40, 41, 32},
{32, 41, 42, 33},
{33, 42, 43, 34},
{34, 43, 44, 35},
{36, 45, 46, 37},
{37, 46, 47, 38},
{38, 47, 48, 39},
{39, 48, 49, 40},
{40, 49, 50, 41},
{41, 50, 51, 42},
{42, 51, 52, 43},
{43, 52, 53, 44},
{45, 54, 55, 46},
{46, 55, 56, 47},
{47, 56, 57, 48},
{48, 57, 58, 49},
{49, 58, 59, 50},
{50, 59, 60, 51},
{51, 60, 61, 52},
{52, 61, 62, 53},
{54, 63, 64, 55},
{55, 64, 65, 56},
{56, 65, 66, 57},
{57, 66, 67, 58},
{58, 67, 68, 59},
{59, 68, 69, 60},
{60, 69, 70, 61},
{61, 70, 71, 62},
{63, 72, 73, 64},
{64, 73, 74, 65},
{65, 74, 75, 66},
{66, 75, 76, 67},
{67, 76, 77, 68},
{68, 77, 78, 69},
{69, 78, 79, 70},
{70, 79, 80, 71},
{72, 81, 82, 73},
{73, 82, 83, 74},
{74, 83, 84, 75},
{75, 84, 85, 76},
{76, 85, 86, 77},
{77, 86, 87, 78},
{78, 87, 88, 79},
{79, 88, 89, 80},
{81, 90, 91, 82},
{82, 91, 92, 83},
{83, 92, 93, 84},
{84, 93, 94, 85},
{85, 94, 95, 86},
{86, 95, 96, 87},
{87, 96, 97, 88},
{88, 97, 98, 89},
{90, 99, 100, 91},
{91, 100, 101, 92},
{92, 101, 102, 93},
{93, 102, 103, 94},
{94, 103, 104, 95},
{95, 104, 105, 96},
{96, 105, 106, 97},
{97, 106, 107, 98},
{99, 108, 109, 100},
{100, 109, 110, 101},
{101, 110, 111, 102},
{102, 111, 112, 103},
{103, 112, 113, 104},
{104, 113, 114, 105},
{105, 114, 115, 106},
{106, 115, 116, 107},
{108, 117, 118, 109},
{109, 118, 119, 110},
{110, 119, 120, 111},
{111, 120, 121, 112},
{112, 121, 122, 113},
{113, 122, 123, 114},
{114, 123, 124, 115},
{115, 124, 125, 116},
{117, 126, 127, 118},
{118, 127, 128, 119},
{119, 128, 129, 120},
{120, 129, 130, 121},
{121, 130, 131, 122},
{122, 131, 132, 123},
{123, 132, 133, 124},
{124, 133, 134, 125},
{126, 135, 136, 127},
{127, 136, 137, 128},
{128, 137, 138, 129},
{129, 138, 139, 130},
{130, 139, 140, 131},
{131, 140, 141, 132},
{132, 141, 142, 133},
{133, 142, 143, 134},
{135, 0, 1, 136},
{136, 1, 2, 137},
{137, 2, 3, 138},
{138, 3, 4, 139},
{139, 4, 5, 140},
{140, 5, 6, 141},
{141, 6, 7, 142},
{142, 7, 8, 143}
};
   
float pig_face[20][3]={
{0.144, -0.269, 1.70366},
{-0.125, -0.269, 1.70366},
{-0.035, -0.499, 1.015},
{0.144, -0.08,1.70366},
{0.426, 0.191, 1.015},
{0.318, 0.353, 1.015},
{0.156, 0.461, 1.015},
{-0.035, 0.5,1.015},
{-0.125, -0.08, 1.70366},
{-0.226, 0.461, 1.015},
{-0.388, 0.353, 1.015},
{-0.496, 0.191, 1.015},
{-0.535, 0, 1.015},
{-0.496, -0.191, 1.015},
{-0.388, -0.353, 1.015},
{-0.226, -0.461, 1.015},
{0.156, -0.461, 1.015},
{0.318, -0.353, 1.015},
{0.426, -0.191, 1.015},
{0.464, 0, 1.015}
};
   

int pig_face_triangles[36][4]={
 
{0, 1, 2, 0},
{3, 4, 5, 2},
{6, 3, 5, 0},
{4, 6, 5, 0},
{4, 7, 6, 0},
{7, 3, 6, 0},
{8, 3, 7, 0},
{9, 8, 7, 0},
{4, 9, 7, 0},
{4, 10, 9,0},
{10, 8, 9,0},
{11, 8,10,1},
{4, 11,10,0},
{4, 12,11,0},
{12, 8,11,0},
{1, 8, 12,0},
{13, 1,12,0},
{4, 13,12,0},
{4, 14,13,0},
{14, 1,13,0},
{15, 1,14,0},
{4, 15,14,0},
{4, 2, 15,0},
{2, 1, 15,0},
{4, 16, 2,0},
{16, 0, 2,0},
{17, 0, 16,0},
{4, 17, 16,0},
{4, 18, 17,0},
{18, 0, 17,0},
{4, 19, 18,0},
{19, 0, 18,0},
{4, 3, 19,0},
{3, 0, 19,0},
{1, 3, 8,0},
{1, 0, 3,0}
};


float pig_feet[4][8][3]={
     {
{0.245, -0.5, 0.195},
{0.245, -0.4, 0.195},
{0.445, -0.4, 0.195},
{0.445, -0.5, 0.195},
{0.245, -0.5, 0.585},
{0.245, -0.4, 0.585},
{0.445, -0.4, 0.585},
{0.445, -0.5, 0.585}
     },
 {
{-0.485, -0.51, 0.325},
{-0.485, -0.41, 0.325},
{-0.285, -0.41, 0.325},
{-0.285, -0.51, 0.325},
{-0.485, -0.51, 0.715},
{-0.485, -0.41, 0.715},
{-0.285, -0.41, 0.715},
{-0.285, -0.51, 0.715}
 },
   {
      
{0.245, -0.5, -0.825},
{0.245, -0.4, -0.825},
{0.445, -0.4, -0.825},
{0.445, -0.5, -0.825},
{0.245, -0.5, -0.435},
{0.245, -0.4, -0.435},
{0.445, -0.4, -0.435},
{0.445, -0.5, -0.435}
   },
   
 {
{-0.485, -0.51, -0.725},
{-0.485, -0.41, -0.725},
{-0.285, -0.41, -0.725},
{-0.285, -0.51, -0.725},
{-0.485, -0.51, -0.335},
{-0.485, -0.41, -0.335},
{-0.285, -0.41, -0.335},
{-0.285, -0.51, -0.335}
 }
};

int pig_feet_triangles[6][4]={
    
{0, 1, 2, 3},
{6, 7, 3, 2},
{7, 6, 5, 4},
{4, 5, 1, 0},
{1, 5, 6, 2},
{4, 0, 3, 7}
};
  


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

void draw_good_pig(float pigx,float pigy,float pigz,float direction) {
   
   int i,j,k;

   
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
   
   glPushMatrix();

   
   glTranslatef(pigx,pigy,pigz);

   glRotatef(direction,0.0,0.0,1.0);
   glRotatef(90,1,0,0);
   
      /* Draw body-tube */
   glColor3f(0.803,0.5,0.384);

      
   glBindTexture(GL_TEXTURE_2D,texName[1]);
      
   glBegin(GL_TRIANGLES);   
   for(i=0;i<16;i++) {
  
      glTexCoord2f(0.0,0.0);
      glVertex3f(-1,
		 pig_cylinder[i][1],
		 pig_cylinder[i][0]);
      glTexCoord2d(0.0,1.0);
      glVertex3f(1,
		 pig_cylinder[i][1],
		 pig_cylinder[i][0]);
      j=i+1;
      if (j>=16) j=0;
      glTexCoord2d(1.0,1.0);
      glVertex3f(1,
		 pig_cylinder[j][1],
		 pig_cylinder[j][0]);
            
      glTexCoord2d(1.0,1.0);
      glVertex3f(1,
		 pig_cylinder[j][1],
		 pig_cylinder[j][0]);
      
      glTexCoord2d(1.0,0.0);
      glVertex3f(-1,
		 pig_cylinder[j][1],
		 pig_cylinder[j][0]);
      glTexCoord2d(0.0,0.0);
      glVertex3f(-1,
		 pig_cylinder[i][1],
		 pig_cylinder[i][0]);      
   }
   glEnd();
   glDisable(GL_TEXTURE_2D);
   
      /* draw hemisphere back */
   

   
   glBegin(GL_QUADS);   
   for(i=0;i<128;i++) {   
      for(j=0;j<4;j++) {
         glVertex3f(pig_hemisphere[pig_hemisphere_triangles[i][j]][2],
		    pig_hemisphere[pig_hemisphere_triangles[i][j]][1],
		    pig_hemisphere[pig_hemisphere_triangles[i][j]][0]);
      }
   }
   glEnd();
   
   
       /* draw nose */
//   glColor3f(1.0,1.0,1.0);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,texName[4]);
   glBegin(GL_QUADS);   
   glTexCoord2f(1.0,0.0);
   glVertex3f(1.705, -0.08, -0.125);
      glTexCoord2f(0.0,0.0);
   glVertex3f(1.705, -0.08,  0.145);
      glTexCoord2f(0.0,1.0);
   glVertex3f(1.705, -0.27,  0.145);
      glTexCoord2f(1.0,1.0);
   glVertex3f(1.705, -0.27, -0.125);
   glEnd();
   glDisable(GL_TEXTURE_2D);
   
       /* draw face */
   
//   	 glEnable(GL_TEXTURE_2D); 
//	 glBindTexture(GL_TEXTURE_2D,texName[3]);
  
   for(i=0;i<35;i++) {   
      
      if (pig_face_triangles[i][3]) {
   	 glEnable(GL_TEXTURE_2D); 
	 glBindTexture(GL_TEXTURE_2D,texName[3]);	 
      }
      glBegin(GL_TRIANGLES);       
      
      for(j=0;j<3;j++) {

	 if (pig_face_triangles[i][3]==1) {
	    switch(j) {
	     case 0: glTexCoord2f(0.0,0.0); break;
	     case 1: glTexCoord2f(0.5,1.0); break;
	     case 2: glTexCoord2f(1.0,0.5); break;
	    }
	 }
	 
	 if (pig_face_triangles[i][3]==2) {
	    switch(j) {
	     case 0: glTexCoord2f(0.0,1.0); break;
	     case 1: glTexCoord2f(1.5,0.5); break;
	     case 2: glTexCoord2f(0.0,0.0); break;
	    }
	 }
	    
	    
         glVertex3f(pig_face[pig_face_triangles[i][j]][2],
		    pig_face[pig_face_triangles[i][j]][1],
		    pig_face[pig_face_triangles[i][j]][0]);
      }
      glEnd();
      
      if (pig_face_triangles[i][3]) glDisable(GL_TEXTURE_2D);
   }

   
   
       /* draw feet */
      
   glColor3f(0.75,0.0,0.75);
   
   glBegin(GL_QUADS);   
   
   for(k=0;k<4;k++) {
      for(i=0;i<6;i++) {   
         for(j=0;j<4;j++) {
            glVertex3f( pig_feet[k][pig_feet_triangles[i][j]][2],
		       pig_feet[k][pig_feet_triangles[i][j]][1],
		       pig_feet[k][pig_feet_triangles[i][j]][0]);
	 }
      }
   }
   glEnd();
       /* draw ears */
   
   glBegin(GL_QUADS);
   glVertex3f(0.695,0.376399,-0.420208);
   glVertex3f(1.025,0.376399,-0.420208);
   glVertex3f(1.025,0.146586,-0.613044);
   glVertex3f(0.695,0.146586,-0.613044);

   glVertex3f(0.695, 0.407392,0.317956);
   glVertex3f(1.025,0.407392,0.317956);
   glVertex3f(1.025,0.161647,0.490029);
   glVertex3f(0.695,0.161647,0.490029);
   glEnd();
   
   glPopMatrix();
}
   
   


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

void display(void) {
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   glLoadIdentity();
   gluLookAt(-10.0,0.0,5.0,
	     0.0,0.0,0.0,
	     0.0,0.0,1.0);
   

   
       /* Draw grassy field */
   glPushMatrix();
   glColor3f(0.4102,0.543,0.1328);
   glBegin(GL_QUADS);
   glVertex3f(-5,-5,0);
   glVertex3f(-5,5,0);
   glVertex3f(5,5,0);
   glVertex3f(5,-5,0);
   glEnd();
   glPopMatrix();

   
//   draw_robo_pig(pigx,pigy,pigz,direction);
      draw_good_pig(pigx,pigy,pigz,direction);

   draw_carrot(-4.0,3.0,0.5,90);
   
   glFlush();
   glutSwapBuffers();
   
}

void reshape(int w,int h) {
   glViewport(0,0,(GLsizei)w,(GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0,0.0,-3.6);
}

void keyboard(unsigned char key, int x, int y) {

 switch(key) {

      case 's': 
    glRotated(22,0, 0, 1);
    display();    
    break;
  case 'x': 
    glRotated(22,0, 1, 0);
    display();    
    break;

    case 'w': 
    glRotated(22,1, 0, 0);
    display();    

    
  case 'a': 
    glTranslatef(0.0, 0.0, -1.0);
    display();    
    break;
  case 'z': 
    glTranslatef(0.0, 0.0, 1.0);
    display();    
    break;
    
  case 'k': 

     direction-=10;
     display();
     break;
    
  case 'j': 
      direction+=10;    
      display();
      break;
    
  case 'i': 
         pigy+=sin( (direction*PI)/180.0);
         pigx+=cos( (direction*PI)/180.0);
    
    display();
    break;
    
  case 'm': 
         pigy-=sin( (direction*PI)/180.0);
         pigx-=cos( (direction*PI)/180.0);
    
    display();
    break;
    
  case 27:
     exit(0);
     break;
 default: break;
}
}

int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(640,480);
   glutInitWindowPosition(100,100);
   
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
