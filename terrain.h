#define NUM_TERRAINS      32

#define WALKABLE_LIMIT    7

   /* Walkable */
#define GRASS_TERRAIN     0
#define FOREST_TERRAIN    1
#define TUNDRA_TERRAIN    2

   /* Obstacle */
#define OCEAN_TERRAIN     8
#define MOUNTAIN_TERRAIN  9

   /* Edge/Transition */
#define BEACH_TERRAIN       16
#define BEACHCORNER_TERRAIN 17
#define BEACHEND_TERRAIN    18
#define CLIFF_TERRAIN       19
#define CLIFFCORNER_TERRAIN 20

   /* Towns */
#define OCEAN_CITY_TERRAIN  24
#define ARCTIC_BASE_TERRAIN 25
#define JOPPATOWNE_TERRAIN  26


typedef struct map_element {
      int terrain_type;
      int rotation;
      char *region_name;
      void *objects;
} map_element;

extern float terrain_heights[];


void setup_map(void);
void setup_terrain(void);
