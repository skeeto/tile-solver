CFLAGS = -std=c99 -Wall -O3 -g3

all : tilegen tilesolve

tilegen : tilegen.c
tilesolve : tilesolve.c

run : tilesolve
	./$^ < beetles.txt

clean :
	$(RM) tilesolve tilegen
