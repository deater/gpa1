CC = gcc

#
# for Linux
#

CFLAGS = -Wall -O2 `sdl-config --cflags`
LFLAGS = `sdl-config --libs` -lGL -lGLU -lm

#
# for windows with Cygwin32 and SDL installed
#
#LFLAGS = -lopengl32 -lGLU32 -lm -lSDL


all:	gpa1

gpa1:	main.o battle.o credits.o gl_helper.o guinea_pig.o joppatowne.o \
	keyboard.o main_menu.o matrix_math.o opener.o setup_enemies.o \
	spaceship.o story.o terrain.o textures.o tfv.o vmw_glfont.o \
	vmw_texture.o world.o
	$(CC) -o gpa1 main.o battle.o credits.o gl_helper.o guinea_pig.o \
		joppatowne.o keyboard.o main_menu.o matrix_math.o opener.o \
		setup_enemies.o spaceship.o story.o terrain.o textures.o \
		tfv.o vmw_glfont.o vmw_texture.o world.o \
		$(LFLAGS)

main.o:	main.c textures.h
	$(CC) $(CFLAGS) -c main.c

battle.o:	battle.c battle.h
	$(CC) $(CFLAGS) -c battle.c

credits.o:	credits.c credits.h
	$(CC) $(CFLAGS) -c credits.c

gl_helper.o:	gl_helper.c gl_helper.h
	$(CC) $(CFLAGS) -c gl_helper.c

guinea_pig.o:	guinea_pig.c guinea_pig.h
	$(CC) $(CFLAGS) -c guinea_pig.c

joppatowne.o:	joppatowne.c joppatowne.h
	$(CC) $(CFLAGS) -c joppatowne.c

keyboard.o:	keyboard.c keyboard.h
	$(CC) $(CFLAGS) -c keyboard.c

main_menu.o:	main_menu.c main_menu.h
	$(CC) $(CFLAGS) -c main_menu.c

matrix_math.o:	matrix_math.c matrix_math.h
	$(CC) $(CFLAGS) -c matrix_math.c

opener.o:	opener.c opener.h
	$(CC) $(CFLAGS) -c opener.c

setup_enemies.o:	setup_enemies.c setup_enemies.h
	$(CC) $(CFLAGS) -c setup_enemies.c

spaceship.o:	spaceship.c spaceship.h
	$(CC) $(CFLAGS) -c spaceship.c

story.o:	story.c story.h
	$(CC) $(CFLAGS) -c story.c

terrain.o:	terrain.c terrain.h
	$(CC) $(CFLAGS) -c terrain.c

textures.o:	textures.c textures.h
	$(CC) $(CFLAGS) -c textures.c

tfv.o:	tfv.c	tfv.h
	$(CC) $(CFLAGS) -c tfv.c

vmw_glfont.o:	vmw_glfont.c vmw_glfont.h
	$(CC) $(CFLAGS) -c vmw_glfont.c

vmw_texture.o:	vmw_texture.c vmw_texture.h
	$(CC) $(CFLAGS) -c vmw_texture.c

world.o:	world.c
	$(CC) $(CFLAGS) -c world.c

clean:
	rm -rf core gpa1 *.o *~
