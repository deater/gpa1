#define ROBO_PIG_ENEMY 0
#define CUBE_ENEMY     1

#define NUM_ENEMIES    2

typedef struct {
    GLuint alive,dead; 
} enemy_list_t;

extern enemy_list_t enemies[NUM_ENEMIES];

void setup_enemies(void);
