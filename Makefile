CC = gcc
C_FLAGS = -Wall
L_FLAGS = -L/usr/X11R6/lib -lGL -lGLU  -lX11 -lm -lICE -lXmu -lSDL


all:	guinea_pig

guinea_pig:	guinea_pig.o vmw_glfont.o vmw_texture.o
	$(CC) -o guinea_pig guinea_pig.o vmw_glfont.o vmw_texture.o $(L_FLAGS)

guinea_pig.o:	guinea_pig.c
	$(CC) $(C_FLAGS) -c guinea_pig.c

vmw_glfont.o:	vmw_glfont.c
	$(CC) $(CFLAGS) -c vmw_glfont.c

vmw_texture.o:	vmw_texture.c
	$(CC) $(CFLAGS) -c vmw_texture.c

clean:
	rm -rf core guinea_pig *.o *~
