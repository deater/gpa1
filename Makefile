CC = gcc
C_FLAGS = -Wall -O2
L_FLAGS = -L/usr/X11R6/lib -lGL -lGLU  -lX11 -lm -lICE -lXmu -lSDL


all:	gp1

gp1:	main.o guinea_pig.o matrix_math.o opener.o terrain.o vmw_glfont.o vmw_texture.o
	$(CC) -o gp1 main.o guinea_pig.o matrix_math.o opener.o terrain.o vmw_glfont.o vmw_texture.o $(L_FLAGS)

main.o:	main.c
	$(CC) $(C_FLAGS) -c main.c

guinea_pig.o:	guinea_pig.c
	$(CC) $(C_FLAGS) -c guinea_pig.c

matrix_math.o:	matrix_math.c
	$(CC) $(C_FLAGS) -c matrix_math.c

opener.o:	opener.c
	$(CC) $(C_FLAGS) -c opener.c

terrain.o:	terrain.c
	$(CC) $(C_FLAGS) -c terrain.c

vmw_glfont.o:	vmw_glfont.c
	$(CC) $(C_FLAGS) -c vmw_glfont.c

vmw_texture.o:	vmw_texture.c
	$(CC) $(C_FLAGS) -c vmw_texture.c

clean:
	rm -rf core gp1 *.o *~
