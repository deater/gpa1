#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "terrain.h"
#include "textures.h"
#include "matrix_math.h"

/*
typedef struct map_element { 
   int terrain_type;
   int rotation;
   char *region_name;
   void *objects;
} map_element;
*/

extern GLuint terrain[];
extern GLuint textures[];

extern map_element world_map[40][40];

char region_names[8][25]={
   "Great Central Sea",
   "Southern Pampas",
   "New Andes",
   "Joppatowne Area",
   "Schwarzenwald",
   "Ocean City Area",
   "Arctic Base Area",
};

#define SOUTHERN_PAMPAS 1
#define NEW_ANDES       2
#define JOPPATOWNE_AREA 3
#define SCHWARZENWALD   4
#define OCEAN_CITY_AREA 5
#define ARCTIC_BASE_AREA 6


float terrain_heights[]={
      
0.0, /* define GRASS_TERRAIN       0 */
0.5, /*  #define FOREST_TERRAIN    1 */
0.0, /*  #define TUNDRA_TERRAIN    2 */
0.0,
0.0,
     0.0,
     0.0,
     0.0,
-0.25,  /*   #define OCEAN_TERRAIN     8 */
4.0,    /*   #define MOUNTAIN_TERRAIN  9 */
0.0,
     0.0,
     0.0,
     0.0,
     0.0,
     0.0,
0.0, /*   #define BEACH_TERRAIN       16 */
0.0, /*   #define BEACHCORNER_TERRAIN 17 */
0.0, /*   #define BEACHEND_TERRAIN    18 */
0.0, /*   #define CLIFF_TERRAIN       19 */
0.0, /*   #define CLIFFCORNER_TERRAIN 20 */
0.0,
0.0,
0.0,

3.0, /*   #define OCEAN_CITY_TERRAIN  24 */
1.0, /*  #define ARCTIC_BASE_TERRAIN 25 */
3.0  /*  #define JOPPATOWNE_TERRAIN  26 */
};


void init_hline(x1,x2,y, terrain, rotation, region) {
 
   int x;
   
   for(x=x1;x<=x2;x++) {
      world_map[x][y].terrain_type=terrain;
      world_map[x][y].rotation=rotation;
      world_map[x][y].region_name=region_names[region];
      world_map[x][y].objects=NULL;
   }
   
}


void init_vline(y1,y2,x, terrain, rotation, region) {
 
   int y;
   
   for(y=y1;y<=y2;y++) {
      world_map[x][y].terrain_type=terrain;
      world_map[x][y].rotation=rotation;
      world_map[x][y].region_name=region_names[region];
      world_map[x][y].objects=NULL;
   }
   
}

void init_point(x,y, terrain, rotation, region) {
 
  
      world_map[x][y].terrain_type=terrain;

   world_map[x][y].rotation=rotation;
      world_map[x][y].region_name=region_names[region];
      world_map[x][y].objects=NULL;
  
   
}

void setup_map(void) {
   
    int i,j;

       /* Init world to ocean */
   
    for(i=0;i<40;i++) {
       for(j=0;j<40;j++) {
          world_map[i][j].terrain_type=OCEAN_TERRAIN;
	  world_map[i][j].rotation=0;
	  world_map[i][j].region_name=region_names[0];
	  world_map[i][j].objects=NULL;
       }
    }
   
       /* Setup southern pampas */
    init_hline(4,7,11, GRASS_TERRAIN, 0, SOUTHERN_PAMPAS);
    init_hline(3,8,12, GRASS_TERRAIN, 0, SOUTHERN_PAMPAS);
    init_hline(2,8,13, GRASS_TERRAIN, 0, SOUTHERN_PAMPAS);
    init_hline(2,7,14, GRASS_TERRAIN, 0, SOUTHERN_PAMPAS);
    init_hline(2,7,15, GRASS_TERRAIN, 0, SOUTHERN_PAMPAS);
    init_hline(3,7,16, GRASS_TERRAIN, 0, SOUTHERN_PAMPAS);
   
       /* Setup Joppatowne Area */
    init_hline(4,8,17, GRASS_TERRAIN, 0, JOPPATOWNE_AREA);
    init_hline(6,7,20, GRASS_TERRAIN, 0, JOPPATOWNE_AREA);
    init_vline(18,21,5, GRASS_TERRAIN, 0, JOPPATOWNE_AREA);
    
       /* Setup New Andes */
    init_vline(20,22,2, MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
    init_vline(17,22,3, MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
    init_vline(18,23,4, MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
    init_vline(26,27,4, MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
    init_vline(22,28,5, MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
    init_vline(27,28,6, MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
    init_vline(28,30,7, MOUNTAIN_TERRAIN, 0, NEW_ANDES);      
    init_vline(28,30,8, MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
    init_vline(30,31,9, MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
    init_vline(30,31,10, MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
    init_point(11,31,   MOUNTAIN_TERRAIN, 0, NEW_ANDES);   
   
       /* Setup Schwarzenwald */
    init_vline(21,25,6,FOREST_TERRAIN,0,SCHWARZENWALD);
    init_vline(21,24,7,FOREST_TERRAIN,0,SCHWARZENWALD);
    init_vline(23,24,8,FOREST_TERRAIN,0,SCHWARZENWALD); 
   
       /* Setup Ocean City Area */
    init_hline(7,8,25,GRASS_TERRAIN,0,OCEAN_CITY_AREA);
    init_hline(6,8,26,GRASS_TERRAIN,0,OCEAN_CITY_AREA);
    init_hline(7,8,27,GRASS_TERRAIN,0,OCEAN_CITY_AREA);
   
       /* Setup Arctic Base Area */
    init_hline(8,13,33,TUNDRA_TERRAIN,0,ARCTIC_BASE_AREA);
    init_hline(9,11,32,TUNDRA_TERRAIN,0,ARCTIC_BASE_AREA);
    init_point(13,32 ,TUNDRA_TERRAIN,0,ARCTIC_BASE_AREA);
    init_point(12,32,GRASS_TERRAIN,0,ARCTIC_BASE_AREA);
   
       /* Cliffs */
    init_hline(4,7,10,CLIFF_TERRAIN,90,SOUTHERN_PAMPAS);
    init_point(7,19,CLIFF_TERRAIN,90,JOPPATOWNE_AREA);
    init_point(10,29,CLIFF_TERRAIN,90,NEW_ANDES);
    init_point(13,31,CLIFF_TERRAIN,90,ARCTIC_BASE_AREA);
   
    init_hline(7,8,18,CLIFF_TERRAIN,270,JOPPATOWNE_AREA);
    init_point(2,23,CLIFF_TERRAIN,270,NEW_ANDES);
    init_point(5,29,CLIFF_TERRAIN,270,NEW_ANDES);
    init_point(7,31,CLIFF_TERRAIN,270,NEW_ANDES);
    init_hline(8,13,34,CLIFF_TERRAIN,270,ARCTIC_BASE_AREA); 
   
    init_vline(13,15,1,CLIFF_TERRAIN,0,SOUTHERN_PAMPAS);
    init_vline(17,18,2,CLIFF_TERRAIN,0,NEW_ANDES);
    init_vline(20,22,1,CLIFF_TERRAIN,0,NEW_ANDES);
    init_vline(26,27,3,CLIFF_TERRAIN,0,NEW_ANDES);
    init_point(7,33,CLIFF_TERRAIN,0,ARCTIC_BASE_AREA);
    init_point(6,30,CLIFF_TERRAIN,0,NEW_ANDES);
   
    init_vline(20,21,8,CLIFF_TERRAIN,180,SCHWARZENWALD);
    init_vline(23,24,9,CLIFF_TERRAIN,180,SCHWARZENWALD);
    init_point(9,28,CLIFF_TERRAIN,180,NEW_ANDES);
    init_point(9,26,CLIFF_TERRAIN,180,OCEAN_CITY_AREA);
   
       /* Angled Cliffs */ 
    init_point(3,11,CLIFFCORNER_TERRAIN,90,SOUTHERN_PAMPAS);   
    init_point(2,12,CLIFFCORNER_TERRAIN,90,SOUTHERN_PAMPAS);   
    init_point(2,19,CLIFFCORNER_TERRAIN,90,NEW_ANDES);   
    init_point(4,25,CLIFFCORNER_TERRAIN,90,NEW_ANDES);   
    init_point(8,32,CLIFFCORNER_TERRAIN,90,ARCTIC_BASE_AREA); 
   
    init_point(2,16,CLIFFCORNER_TERRAIN,0,SOUTHERN_PAMPAS); 
    init_point(3,23,CLIFFCORNER_TERRAIN,0,NEW_ANDES); 
    init_point(4,24,CLIFFCORNER_TERRAIN,0,NEW_ANDES); 
    init_point(4,28,CLIFFCORNER_TERRAIN,0,NEW_ANDES);   
    init_point(6,29,CLIFFCORNER_TERRAIN,0,NEW_ANDES);   
    init_point(8,31,CLIFFCORNER_TERRAIN,0,NEW_ANDES);      

    init_point(6,18,CLIFFCORNER_TERRAIN,270,JOPPATOWNE_AREA);    
   
    init_point(6,19,CLIFFCORNER_TERRAIN,180,JOPPATOWNE_AREA);
    init_point(8,22,CLIFFCORNER_TERRAIN,180,SCHWARZENWALD);
    init_point(9,29,CLIFFCORNER_TERRAIN,180,NEW_ANDES);   
    init_point(11,30,CLIFFCORNER_TERRAIN,180,NEW_ANDES);   
    init_point(12,31,CLIFFCORNER_TERRAIN,180,ARCTIC_BASE_AREA);   

       /* BEACH */
    init_vline(12,13,9,BEACH_TERRAIN,0,SOUTHERN_PAMPAS);
    init_point(8,15,BEACH_TERRAIN,0,SOUTHERN_PAMPAS);
    init_point(9,17,BEACH_TERRAIN,0,JOPPATOWNE_AREA);
    init_point(9,25,BEACH_TERRAIN,0,OCEAN_CITY_AREA);
    init_point(9,27,BEACH_TERRAIN,0,OCEAN_CITY_AREA);
    init_vline(32,33,14,BEACH_TERRAIN,0,ARCTIC_BASE_AREA);
   
       /* Beach Corners */
    init_point(8,11,BEACHCORNER_TERRAIN,0,SOUTHERN_PAMPAS);
    init_point(8,16,BEACHCORNER_TERRAIN,0,JOPPATOWNE_AREA);
   
    init_point(8,14,BEACHCORNER_TERRAIN,90,SOUTHERN_PAMPAS);

       /* Beach Ends */
    init_point(9,11,BEACHEND_TERRAIN,0,SOUTHERN_PAMPAS);
    init_point(9,16,BEACHEND_TERRAIN,0,SOUTHERN_PAMPAS);
   
    init_point(9,14,BEACHEND_TERRAIN,90,SOUTHERN_PAMPAS);

       /* Towns */
    init_point(5,18,JOPPATOWNE_TERRAIN,0,JOPPATOWNE_AREA);
    init_point(8,26,OCEAN_CITY_TERRAIN,90,OCEAN_CITY_AREA);
    init_point(10,33,ARCTIC_BASE_TERRAIN,0,ARCTIC_BASE_AREA);
   
}






void setup_terrain(void) {

   float normalx,normaly,normalz;

       /* Grass */
   terrain[GRASS_TERRAIN]=glGenLists(1);
   glNewList(terrain[GRASS_TERRAIN],GL_COMPILE);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,textures[GRASS_TEXTURE]);
   
   glBegin(GL_QUADS);
      glNormal3f(0.0,0.0,1.0);
      glTexCoord2f(0.0,0.0);
      glVertex3f(-2.0,-2.0,0.0);
   
      glTexCoord2f(1.0,0.0);
      glVertex3f(2.0,-2.0,0.0);
   
      glTexCoord2f(1.0,1.0);
      glVertex3f(2.0,2.0,0.0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(-2.0,2.0,0.0);
   glEnd();
   glDisable(GL_TEXTURE_2D);
   
   glEndList();
   
          /* Ocean City */
   terrain[OCEAN_CITY_TERRAIN]=glGenLists(1);
   glNewList(terrain[OCEAN_CITY_TERRAIN],GL_COMPILE);

   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,textures[GRASS_TEXTURE]);
   
   glBegin(GL_QUADS);
      glNormal3f(0.0,0.0,1.0);
      glTexCoord2f(0.0,0.0);
      glVertex3f(-2.0,-2.0,0.0);
   
      glTexCoord2f(1.0,0.0);
      glVertex3f(2.0,-2.0,0.0);
   
      glTexCoord2f(1.0,1.0);
      glVertex3f(2.0,2.0,0.0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(-2.0,2.0,0.0);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,textures[TILE_DOOR_TEXTURE]);
   glBegin(GL_QUADS);
      glNormal3f(0.0,-1.0,0.0);
      glTexCoord2f(1.0,1.0);
      glVertex3f(-2,-1,0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(-1,-1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(-1,-1,1);
   
      glTexCoord2f(1.0,0.0);
      glVertex3f(-2,-1,1);
   
          /* */
   
      glTexCoord2f(1.0,1.0);
      glVertex3f(1,-1,0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(2,-1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(2,-1,1);
   
      glTexCoord2f(1.0,0.0);
      glVertex3f(1,-1,1);
  
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,textures[TILE_WINDOW_TEXTURE]);
   glBegin(GL_QUADS);
      glNormal3f(0.0,-1.0,0.0);
      glTexCoord2f(1.0,2.0);
      glVertex3f(-1,-1,0);
   
      glTexCoord2f(0.0,2.0);
      glVertex3f(0,-1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(0,-1,2);
   
      glTexCoord2f(1.0,0.0);
      glVertex3f(-1,-1,2);
       /* back */
      glNormal3f(0.0,1.0,0.0);
      glTexCoord2f(1.0,1.0);
      glVertex3f(-1,1,0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(-2,1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(-2,1,1);
   
      glTexCoord2f(1.0,0.0);
      glVertex3f(-1,1,1);   
          /* back2 */
      glNormal3f(0.0,1.0,0.0);
      glTexCoord2f(1.0,2.0);
      glVertex3f(0,1,0);
   
      glTexCoord2f(0.0,2.0);
      glVertex3f(-1,1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(-1,1,2);
   
      glTexCoord2f(1.0,0.0);
      glVertex3f(0,1,2);   
          /* back3*/
      glNormal3f(0.0,1.0,0.0);
      glTexCoord2f(1.0,1.0);
      glVertex3f(2,1,0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(1,1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(1,1,1);
   
      glTexCoord2f(1.0,0.0);
      glVertex3f(2,1,1);   
   
          /* side1 */
      glNormal3f(-1.0,0.0,0.0);
      glTexCoord2f(2.0,1.0);
      glVertex3f(-2,1,0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(-2,-1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(-2,-1,1);
   
      glTexCoord2f(2.0,0.0);
      glVertex3f(-2,1,1);   
   
             /* side2 */
      glNormal3f(-1.0,0.0,0.0);
      glTexCoord2f(2.0,1.0);
      glVertex3f(-1,1,1);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(-1,-1,1);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(-1,-1,2);
   
      glTexCoord2f(2.0,0.0);
      glVertex3f(-1,1,2);   
   
             /* side3 */
      glNormal3f(-1.0,0.0,0.0);
      glTexCoord2f(2.0,1.0);
      glVertex3f(1,1,0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(1,-1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(1,-1,1);
   
      glTexCoord2f(2.0,0.0);
      glVertex3f(1,1,1);   
   
             /* -side1 */
      glNormal3f(1.0,0.0,0.0);
      glTexCoord2f(2.0,2.0);
      glVertex3f(0,1,0);
   
      glTexCoord2f(0.0,2.0);
      glVertex3f(0,-1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(0,-1,2);
   
      glTexCoord2f(2.0,0.0);
      glVertex3f(0,1,2);   
   
                /* -side2 */
      glNormal3f(1.0,0.0,0.0);
      glTexCoord2f(2.0,1.0);
      glVertex3f(2,1,0);
   
      glTexCoord2f(0.0,1.0);
      glVertex3f(2,-1,0);
   
      glTexCoord2f(0.0,0.0);
      glVertex3f(2,-1,1);
   
      glTexCoord2f(2.0,0.0);
      glVertex3f(2,1,1);   
   
   glEnd();
   glBindTexture(GL_TEXTURE_2D,textures[TILE_BLANK_TEXTURE]);  
   glBegin(GL_TRIANGLES);
   
          /* tri 1 */
      glNormal3f(-1.0,0,0);
      glTexCoord2f(0,0);
      glVertex3f(-2,1,1);
   
      glTexCoord2f(1,0);
      glVertex3f(-2,-1,1);
   
      glTexCoord2f(0.5,1);
      glVertex3f(-2,0,1.5);

          /* tri 2 */
      glNormal3f(-1.0,0,0);
      glTexCoord2f(0,0);
      glVertex3f(-1,1,2);
   
      glTexCoord2f(1,0);
      glVertex3f(-1,-1,2);
   
      glTexCoord2f(0.5,1);
      glVertex3f(-1,0,2.5);
   
       /* tri 3 */
      glNormal3f(1.0,0,0);
      glTexCoord2f(0,0);
      glVertex3f(0,1,2);
   
      glTexCoord2f(1,0);
      glVertex3f(0,-1,2);
   
      glTexCoord2f(0.5,1);
      glVertex3f(0,0,2.5);
   
          /* tri 4 */
      glNormal3f(-1.0,0,0);
      glTexCoord2f(0,0);
      glVertex3f(1,1,1);
   
      glTexCoord2f(1,0);
      glVertex3f(1,-1,1);
   
      glTexCoord2f(0.5,1);
      glVertex3f(1,0,1.5);
     
          /* tri 5 */
      glNormal3f(1.0,0,0);
      glTexCoord2f(0,0);
      glVertex3f(2,1,1);
   
      glTexCoord2f(1,0);
      glVertex3f(2,-1,1);
   
      glTexCoord2f(0.5,1);
      glVertex3f(2,0,1.5);
   
   glEnd();
   glBindTexture(GL_TEXTURE_2D,textures[TILE_ROOF_TEXTURE]);    
   glBegin(GL_QUADS);
   
        /* roof front 1 */
      glNormal3f(0.0,-0.447,0.89442);
      glTexCoord2f(0,0);
      glVertex3f(-2.1,-1.2,0.9);       
   
      glTexCoord2f(1,0);
      glVertex3f(-1,-1.2,0.9);       
   
      glTexCoord2f(1,1);
      glVertex3f(-1,0,1.5);       
   
      glTexCoord2f(0,1);
      glVertex3f(-2.1,0,1.5);       
   
           /* roof front 2 */
      glNormal3f(0.0,-0.447,0.89442);
      glTexCoord2f(0,0);
      glVertex3f(-1.1,-1.2,1.9);       
   
      glTexCoord2f(1,0);
      glVertex3f(0.1,-1.2,1.9);       
   
      glTexCoord2f(1,1);
      glVertex3f(0.1,0,2.5);       
   
      glTexCoord2f(0,1);
      glVertex3f(-1.1,0,2.5);       
   
           /* roof front 3 */
      glNormal3f(0.0,-0.447,0.89442);
      glTexCoord2f(0,0);
      glVertex3f(0.9,-1.2,0.9);       
   
      glTexCoord2f(1,0);
      glVertex3f(2.1,-1.2,0.9);       
   
      glTexCoord2f(1,1);
      glVertex3f(2.1,0,1.5);       
   
      glTexCoord2f(0,1);
      glVertex3f(0.9,0,1.5);       
   
           /* roof back 1 */
      glNormal3f(0.0,0.447,0.89442);
      glTexCoord2f(0,0);
      glVertex3f(-2.1,1.2,0.9);       
   
      glTexCoord2f(1,0);
      glVertex3f(-1,1.2,0.9);       
   
      glTexCoord2f(1,1);
      glVertex3f(-1,0,1.5);       
   
      glTexCoord2f(0,1);
      glVertex3f(-2.1,0,1.5);       
   
           /* roof back 2 */
      glNormal3f(0.0,0.447,0.89442);
      glTexCoord2f(0,0);
      glVertex3f(-1.1,1.2,1.9);       
   
      glTexCoord2f(1,0);
      glVertex3f(0.1,1.2,1.9);       
   
      glTexCoord2f(1,1);
      glVertex3f(0.1,0,2.5);       
   
      glTexCoord2f(0,1);
      glVertex3f(-1.1,0,2.5);       
   
           /* roof back 3 */
      glNormal3f(0.0,0.447,0.89442);
      glTexCoord2f(0,0);
      glVertex3f(0.9,1.2,0.9);       
   
      glTexCoord2f(1,0);
      glVertex3f(2.1,1.2,0.9);       
   
      glTexCoord2f(1,1);
      glVertex3f(2.1,0,1.5);       
   
      glTexCoord2f(0,1);
      glVertex3f(0.9,0,1.5);       
   
   glEnd();
   
   glDisable(GL_TEXTURE_2D);
   
   glEndList();
   terrain[JOPPATOWNE_TERRAIN]=terrain[OCEAN_CITY_TERRAIN];
/*******************************************************
 * OCEAN
 ********************************************************/
    terrain[OCEAN_TERRAIN]=glGenLists(1);
    glNewList(terrain[OCEAN_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[OCEAN_TEXTURE]);
   
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,-0.25);
    glEnd();
    glDisable(GL_TEXTURE_2D);
   
    glEndList();

/*************************************************************
 * TUNDRA
 * ************************************************************/
    terrain[TUNDRA_TERRAIN]=glGenLists(1);
    glNewList(terrain[TUNDRA_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[TUNDRA_TEXTURE]);
   
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,0);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,0);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
   
    glEndList();
   
 /*************************************************************
 * ARCTIC BASE
 * ************************************************************/
    terrain[ARCTIC_BASE_TERRAIN]=glGenLists(1);
    glNewList(terrain[ARCTIC_BASE_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[TUNDRA_TEXTURE]);
   
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,0);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,0);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,0);
    glEnd();

       /* roof */
    glBindTexture(GL_TEXTURE_2D,textures[ARCTIC_ROOF_TEXTURE]);
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0,0);
       glVertex3f(-1,-1,1);
   
       glTexCoord2f(1,0);
       glVertex3f(1,-1,1);
   
       glTexCoord2f(1,1);
       glVertex3f(1,1,1);
   
       glTexCoord2f(0,1);
       glVertex3f(-1,1,1);
   
    glEnd();
   
       /* door */
    glBindTexture(GL_TEXTURE_2D,textures[ARCTIC_DOOR_TEXTURE]);
    glBegin(GL_QUADS);
       glNormal3f(0.89442,0.0,0.447);
       glTexCoord2f(1,1);
       glVertex3f(1.5,-1.5,0);
   
       glTexCoord2f(0,1);
       glVertex3f(1.5,1.5,0);
   
       glTexCoord2f(0,0);
       glVertex3f(1,1,1);
   
       glTexCoord2f(1,0);
       glVertex3f(1,-1,1);
   
    glEnd();
   
          /* North window1 */
    glBindTexture(GL_TEXTURE_2D,textures[ARCTIC_WINDOW_TEXTURE]);
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.89442,0.447);
       glTexCoord2f(1,1);
       glVertex3f(1.5,1.5,0);
   
       glTexCoord2f(0,1);
       glVertex3f(-1.5,1.5,0);
   
       glTexCoord2f(0,0);
       glVertex3f(-1,1,1);
   
       glTexCoord2f(1,0);
       glVertex3f(1,1,1);
   
          /* West window */

       glNormal3f(-0.89442,0.0,0.447);
       glTexCoord2f(1,1);
       glVertex3f(-1.5,1.5,0);
   
       glTexCoord2f(0,1);
       glVertex3f(-1.5,-1.5,0);
   
       glTexCoord2f(0,0);
       glVertex3f(-1,-1,1);
   
       glTexCoord2f(1,0);
       glVertex3f(-1,1,1);
      
          /* South Window */
   
       glNormal3f(0.0,-0.89442,0.447);
       glTexCoord2f(1,1);
       glVertex3f(-1.5,-1.5,0);
   
       glTexCoord2f(0,1);
       glVertex3f(1.5,-1.5,0);
   
       glTexCoord2f(0,0);
       glVertex3f(1,-1,1);
   
       glTexCoord2f(1,0);
       glVertex3f(-1,-1,1);
   
    glEnd();
   
    glDisable(GL_TEXTURE_2D);
   
    glEndList();
/********************************************************
 * CLIFF
 * *******************************************************/
    
    terrain[CLIFF_TERRAIN]=glGenLists(1);
    glNewList(terrain[CLIFF_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[OCEAN_TEXTURE]);
   
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,-0.25);
    glEnd();
   
    glBindTexture(GL_TEXTURE_2D,textures[CLIFF_TEXTURE]);
   
    glBegin(GL_QUADS);
   
       glNormal3f(-1.0,0.0,0.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(2.0,2.0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,-2.0,0);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(2.0,2.0,0);
    glEnd();
   
    glDisable(GL_TEXTURE_2D);
   
    glEndList();
   
   
/********************************************************
 * CLIFFCORNER
 * *******************************************************/
    
    terrain[CLIFFCORNER_TERRAIN]=glGenLists(1);
    glNewList(terrain[CLIFFCORNER_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[OCEAN_TEXTURE]);
   
    glBegin(GL_TRIANGLES);
   
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,-0.25);

    glEnd();
   
    glBindTexture(GL_TEXTURE_2D,textures[CLIFF_TEXTURE]);

    
   
    glBegin(GL_QUADS);
   
       glNormal3f(-0.70710678,0.70710678,0.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(2.0,2.0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(-2.0,-2.0,0);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(2.0,2.0,0);
    glEnd();
   
    glBegin(GL_TRIANGLES);
   
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(2.0,2.0,0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2.0,-2.0,0);
   
       glTexCoord2f(0.5,0.5);
       glVertex3f(2.0,-2.0,0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
   
    glEndList();
   
/********************************************************
 * BEACH
 * *******************************************************/
    
    terrain[BEACH_TERRAIN]=glGenLists(1);
    glNewList(terrain[BEACH_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[SHALLOW_TEXTURE]);
   
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(0.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(0,2.0,-0.25);
    glEnd();
       
    glBindTexture(GL_TEXTURE_2D,textures[SAND_TEXTURE]);
   
    glBegin(GL_QUADS);
   
       glNormal3f(0.124,0.0,0.992278);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(0,-2,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(0,2.0,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,0);
    glEnd();
   
    glBindTexture(GL_TEXTURE_2D,textures[CLIFF_TEXTURE]);
   
    glBegin(GL_TRIANGLES);
    
       glNormal3f(0,-1,0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2,-2,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(0,-2,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2,-2,0);

       glNormal3f(0,1,0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2,2,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(0,2,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2,2,0);

       
   
    glEnd();
   
    glDisable(GL_TEXTURE_2D);
   
    glEndList();
   
/********************************************************
 * BEACH CORNER
 * *******************************************************/
    
    terrain[BEACHCORNER_TERRAIN]=glGenLists(1);
    glNewList(terrain[BEACHCORNER_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[SHALLOW_TEXTURE]);
   
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(0.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,0.0,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(0,0,-0.25);
    glEnd();
       
    glBindTexture(GL_TEXTURE_2D,textures[SAND_TEXTURE]);
   
    glBegin(GL_QUADS);
   
       glNormal3f(0.124,0.0,0.992278);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(0,-2,-0.25);
   
       glTexCoord2f(1.0,0.5);
       glVertex3f(0,0.0,-0.25);
   
       glTexCoord2f(0.0,0.5);
       glVertex3f(-2.0,0.0,0);
    glEnd();
   
    glBegin(GL_TRIANGLES);

       glNormal3f(0.124,0.0,0.992278);
       
       glTexCoord2f(0.0,0.5);
       glVertex3f(-2.0,0.0,0);
   
       glTexCoord2f(1.0,0.5);
       glVertex3f(0.0,0.0,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,0);
   
       glNormal3f(0.0,-0.124,0.992278);
       
       glTexCoord2f(0.5,0.0);
       glVertex3f(0.0,0.0,-0.25);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,2.0,0.0);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,0);
   
    glEnd();
   
   
    glBegin(GL_QUADS);

       glNormal3f(0.0,-0.124,0.992278);
       
       glTexCoord2f(0.5,0.0);
       glVertex3f(0.0,0.0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,0.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,0.0);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,2.0,0.0);
   
    glEnd();
   
    glBindTexture(GL_TEXTURE_2D,textures[CLIFF_TEXTURE]);
   
    glBegin(GL_TRIANGLES);
    
       glNormal3f(0,-1,0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2,-2,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(0,-2,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2,-2,0);

   
       glNormal3f(1,0,0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(2,0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2,2,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(2,2,0);

    glEnd();
   
    glDisable(GL_TEXTURE_2D);
   
    glEndList();
   
/********************************************************
 * BEACH ENDS
 * *******************************************************/
    
    terrain[BEACHEND_TERRAIN]=glGenLists(1);
    glNewList(terrain[BEACHEND_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
   
    glBindTexture(GL_TEXTURE_2D,textures[OCEAN_TEXTURE]);
   
    glBegin(GL_QUADS);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.5,0.0);
       glVertex3f(0.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,-0.25);
   
       glTexCoord2f(1.0,0.5);
       glVertex3f(2.0,0.0,-0.25);
   
       glTexCoord2f(0.5,0.5);
       glVertex3f(0.0,0.0,-0.25);
   
    glEnd();
   
    glBegin(GL_TRIANGLES);
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,-0.25);
   
       glTexCoord2f(0.5,0.0);
       glVertex3f(0.0,-2.0,-0.25);
   
       glTexCoord2f(0.5,0.5);
       glVertex3f(0.0,0.0,-0.25);

          /* 2 */
       glTexCoord2f(0.5,0.5);
       glVertex3f(0,0,-0.25);
   
       glTexCoord2f(1.0,0.5);
       glVertex3f(2.0,0.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,-0.25);
   
    glEnd();
   
    glBindTexture(GL_TEXTURE_2D,textures[SHALLOW_TEXTURE]);
   
    glBegin(GL_TRIANGLES);
   
       glNormal3f(0.0,0.0,1.0);
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,-0.25);
   
       glTexCoord2f(0.5,0.5);
       glVertex3f(0.0,0.0,-0.25);
   
       glTexCoord2f(0.0,0.5);
       glVertex3f(-2.0,0.0,-0.25);
          /* 2 */
       glTexCoord2f(0.0,0.5);
       glVertex3f(-2.0,0.0,-0.25);
   
       glTexCoord2f(0.5,0.5);
       glVertex3f(0.0,0.0,-0.25);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,2.0,-0.25);
          /* 3 */
       glTexCoord2f(0.5,0.5);
       glVertex3f(0.0,0.0,-0.25);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,-0.25);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,2.0,-0.25);
   
    glEnd();
       
    glBindTexture(GL_TEXTURE_2D,textures[SAND_TEXTURE]);
   
    glBegin(GL_TRIANGLES);
      
       glNormal3f(0.123091,-0.123091,0.984732);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,0.0,-0.25);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0,2,-0.25);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2,2.0,0.0);
   
    glEnd();
   
    glDisable(GL_TEXTURE_2D);
   
    glEndList();

/*********************************************************
 * MOUNTAIN
 * *******************************************************/
   
    terrain[MOUNTAIN_TERRAIN]=glGenLists(1);
    glNewList(terrain[MOUNTAIN_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[MOUNTAIN_TEXTURE]);
   
    glBegin(GL_TRIANGLES);
   
          /* Face 1 */

       calculate_normal(-2.0,2.0,0.0,
			-2.0,-2.0,0.0,
			0.0,0.0,4.0,
			&normalx,&normaly,&normalz);
       glNormal3f(normalx,normaly,normalz);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2.0,-2.0,0.0);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,0.0,4.0);
   
          /* Face 2 */
   
       calculate_normal(-2.0,-2.0,0.0,
			2.0,-2.0,0.0,
			0.0,0.0,4.0,
			&normalx,&normaly,&normalz);
       glNormal3f(normalx,normaly,normalz);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,0.0);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,0.0,4.0);
   
          /* Face 3 */
   
      calculate_normal(2.0,-2.0,0.0,
			2.0,2.0,0.0,
			0.0,0.0,4.0,
			&normalx,&normaly,&normalz);
       glNormal3f(normalx,normaly,normalz);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(2.0,-2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,2.0,0.0);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,0.0,4.0);
   
          /* Face 4 */
   
          calculate_normal(2.0,2.0,0.0,
			-2.0,2.0,0.0,
			0.0,0.0,4.0,
			&normalx,&normaly,&normalz);
       glNormal3f(normalx,normaly,normalz);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(2.0,2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2.0,2.0,0.0);
   
       glTexCoord2f(0.5,1.0);
       glVertex3f(0.0,0.0,4.0);
   
   
    glEnd();
    glDisable(GL_TEXTURE_2D);
   
    glEndList();
   
   
       /* Forest */
    terrain[FOREST_TERRAIN]=glGenLists(1);
    glNewList(terrain[FOREST_TERRAIN],GL_COMPILE);
   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[FOREST_TEXTURE]);
   
    glBegin(GL_QUADS);
   
          /* Face 1 */

       glNormal3f(0,-1,0);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,0.0);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,-2.0,0.5);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,-2.0,0.5);
   
             /* Face 2 */

       glNormal3f(1,0,0);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(2.0,-2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,2.0,0.0);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,0.5);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(2.0,-2.0,0.5);
   
             /* Face 3 */

       glNormal3f(0,1,0);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(2.0,2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2.0,2.0,0.0);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(-2.0,2.0,0.5);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(2.0,2.0,0.5);
   
             /* Face 4 */

       glNormal3f(-1,0,0);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,2.0,0.0);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(-2.0,-2.0,0.0);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(-2.0,-2.0,0.5);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,0.5);
   
             /* Top */

       glNormal3f(0,0,1);
   
       glTexCoord2f(0.0,0.0);
       glVertex3f(-2.0,-2.0,0.5);
   
       glTexCoord2f(1.0,0.0);
       glVertex3f(2.0,-2.0,0.5);
   
       glTexCoord2f(1.0,1.0);
       glVertex3f(2.0,2.0,0.5);
   
       glTexCoord2f(0.0,1.0);
       glVertex3f(-2.0,2.0,0.5);

    glEnd();
    glDisable(GL_TEXTURE_2D);
   
    glEndList();

}
   
