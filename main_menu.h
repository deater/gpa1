#define VIEW_STORY 0
#define NEW_GAME   1
#define LOAD_GAME  2
#define CREDITS    3
#define QUIT       4
#define SAVE_GAME  5
#define CANCELED   6

int main_menu(int xsize, int ysize);
void putMenuOption(int x,int y,char *string,int physical_position,int position,
		   int greyed_out);
