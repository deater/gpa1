
CC = gcc
C_FLAGS = -Wall
L_FLAGS = -L/usr/X11R6/lib -lGL -lGLU -lglut -lX11 -lm -lICE -lXmu


all:	guinea_pig

guinea_pig:	guinea_pig.o vmw_texture.o
	$(CC) -o guinea_pig guinea_pig.o vmw_texture.o $(L_FLAGS)

guinea_pig.o:	guinea_pig.c
	$(CC) $(C_FLAGS) -c guinea_pig.c

vmw_texture.o:	vmw_texture.c
	$(CC) $(CFLAGS) -c vmw_texture.c

clean:
	rm -rf core guinea_pig *.o *~
