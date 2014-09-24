CFLAGS = -std=c99 -Wall -O3 -g3
LDLIBS = -lm

all : tilegen tilesolve tiledraw

tilegen : tilegen.c
tilesolve : tilesolve.c
tiledraw : tiledraw.c

run : tilesolve
	./$^ < beetles.txt

clean :
	$(RM) tilesolve tilegen
