CC = gcc
C_FLAGS = -Wall -O2
L_FLAGS = -L/usr/X11R6/lib -lGL -lGLU  -lX11 -lm -lICE -lXmu -lSDL


all:	gp1

gp1:	main.o gl_helper.o guinea_pig.o keyboard.o matrix_math.o opener.o \
	spaceship.o story.o terrain.o textures.o vmw_glfont.o vmw_texture.o
	$(CC) -o gp1 main.o gl_helper.o guinea_pig.o keyboard.o matrix_math.o \
	opener.o spaceship.o story.o terrain.o textures.o vmw_glfont.o vmw_texture.o $(L_FLAGS)

main.o:	main.c textures.h
	$(CC) $(C_FLAGS) -c main.c

gl_helper.o:	gl_helper.c gl_helper.h
	$(CC) $(C_FLAGS) -c gl_helper.c
	
guinea_pig.o:	guinea_pig.c guinea_pig.h
	$(CC) $(C_FLAGS) -c guinea_pig.c

keyboard.o:	keyboard.c keyboard.h
	$(CC) $(C_FLAGS) -c keyboard.c

matrix_math.o:	matrix_math.c matrix_math.h
	$(CC) $(C_FLAGS) -c matrix_math.c

opener.o:	opener.c opener.h
	$(CC) $(C_FLAGS) -c opener.c

spaceship.o:	spaceship.c spaceship.h
	$(CC) $(C_FLAGS) -c spaceship.c

story.o:	story.c story.h
	$(CC) $(C_FLAGS) -c story.c

terrain.o:	terrain.c terrain.h
	$(CC) $(C_FLAGS) -c terrain.c

textures.o:	textures.c textures.h
	$(CC) $(C_FLAGS) -c textures.c

vmw_glfont.o:	vmw_glfont.c vmw_glfont.h
	$(CC) $(C_FLAGS) -c vmw_glfont.c

vmw_texture.o:	vmw_texture.c vmw_texture.h
	$(CC) $(C_FLAGS) -c vmw_texture.c

clean:
	rm -rf core gp1 *.o *~
