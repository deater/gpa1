#define NUM_TERRAINS      10

#define GRASS_TERRAIN     0
#define MOUNTAIN_TERRAIN  1
#define OCEAN_TERRAIN     2
#define FOREST_TERRAIN    3
#define BEACH_TERRAIN     4
#define BEACHCORNER_TERRAIN 5
#define BEACHEND_TERRAIN    6
#define TUNDRA_TERRAIN      7
#define CLIFF_TERRAIN       8
#define CLIFFCORNER_TERRAIN 9

typedef struct map_element {
      int terrain_type;
      int rotation;
      char *region_name;
      void *objects;
} map_element;

void setup_map(void);
void setup_terrain(void);
