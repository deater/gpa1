#define TFV_HEAD         0
#define TFV_TORSO        1
#define TFV_UPPER_ARM    2
#define TFV_LOWER_ARM    3
#define TFV_WAIST        4
#define TFV_UPPER_LEG    5
#define TFV_LOWER_LEG    6
#define TFV_SWORD        7

int make_rectangle(float x, float y, float z, int text1, int text2, int text3,
		                              int text4, int text5, int text6);
int setup_tfv(void);
int setup_tfe(void);
void draw_tfv(int head_twist,int waist_twist,int left_arm_angle,int left_elbow_angle,
	      int right_arm_angle,int right_elbow_angle,int left_leg_angle,
	      int left_knee_angle,int right_leg_angle,int right_knee_angle,
	      int show_sword,int whom);
