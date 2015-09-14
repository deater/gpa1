CC = gcc

#
# for Linux
#

C_FLAGS = -Wall -O2 `sdl-config --cflags`
L_FLAGS = `sdl-config --libs` -lGL -lGLU -lm

#
# for windows with Cygwin32 and SDL installed
#
#L_FLAGS = -lopengl32 -lGLU32 -lm -lSDL


all:	gp1

gp1:	main.o battle.o credits.o gl_helper.o guinea_pig.o joppatowne.o keyboard.o main_menu.o matrix_math.o \
	opener.o setup_enemies.o spaceship.o story.o terrain.o textures.o tfv.o vmw_glfont.o \
	vmw_texture.o world.o
	$(CC) -o gp1 main.o battle.o credits.o gl_helper.o guinea_pig.o joppatowne.o keyboard.o main_menu.o \
	           matrix_math.o opener.o setup_enemies.o spaceship.o story.o terrain.o \
		   textures.o tfv.o vmw_glfont.o vmw_texture.o world.o \
		   $(L_FLAGS)

main.o:	main.c textures.h
	$(CC) $(C_FLAGS) -c main.c

battle.o:	battle.c battle.h
	$(CC) $(C_FLAGS) -c battle.c

credits.o:	credits.c credits.h
	$(CC) $(C_FLAGS) -c credits.c

gl_helper.o:	gl_helper.c gl_helper.h
	$(CC) $(C_FLAGS) -c gl_helper.c
	
guinea_pig.o:	guinea_pig.c guinea_pig.h
	$(CC) $(C_FLAGS) -c guinea_pig.c

joppatowne.o:	joppatowne.c joppatowne.h
	$(CC) $(C_FLAGS) -c joppatowne.c

keyboard.o:	keyboard.c keyboard.h
	$(CC) $(C_FLAGS) -c keyboard.c

main_menu.o:	main_menu.c main_menu.h
	$(CC) $(C_FLAGS) -c main_menu.c

matrix_math.o:	matrix_math.c matrix_math.h
	$(CC) $(C_FLAGS) -c matrix_math.c

opener.o:	opener.c opener.h
	$(CC) $(C_FLAGS) -c opener.c

setup_enemies.o:	setup_enemies.c setup_enemies.h
	$(CC) $(C_FLAGS) -c setup_enemies.c
	
spaceship.o:	spaceship.c spaceship.h
	$(CC) $(C_FLAGS) -c spaceship.c

story.o:	story.c story.h
	$(CC) $(C_FLAGS) -c story.c

terrain.o:	terrain.c terrain.h
	$(CC) $(C_FLAGS) -c terrain.c

textures.o:	textures.c textures.h
	$(CC) $(C_FLAGS) -c textures.c

tfv.o:	tfv.c	tfv.h
	$(CC) $(C_FLAGS) -c tfv.c

vmw_glfont.o:	vmw_glfont.c vmw_glfont.h
	$(CC) $(C_FLAGS) -c vmw_glfont.c

vmw_texture.o:	vmw_texture.c vmw_texture.h
	$(CC) $(C_FLAGS) -c vmw_texture.c

world.o:	world.c
	$(CC) $(C_FLAGS) -c world.c

clean:
	rm -rf core gp1 *.o *~
