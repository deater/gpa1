typedef struct {
       /* non-saved state */
    int xsize,ysize,use_lighting;
   
       /* saved state */   
    int health,health_total,anger;
    float speed;
    int money;
    float direction,pigx,pigy,pigz;
    int gridx,gridy;
    int spaceship_active,in_spaceship;
    int whoami;
    int spaceship_gridx,spaceship_gridy;
    float spaceship_xoffset,spaceship_yoffset,spaceship_direction;
} game_state_type;
