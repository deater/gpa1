typedef struct {
    float direction,pigx,pigy,pigz;
    int gridx,gridy;
    int spaceship_active,in_spaceship;
    int whoami;
    int spaceship_gridx,spaceship_gridy;
    float spaceship_xoffset,spaceship_yoffset,spaceship_direction;
} game_state_type;
