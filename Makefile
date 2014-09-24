CFLAGS = -std=c99 -Wall -g3

tilesolve : tilesolve.c

run : tilesolve
	./$^ < beetles.txt

clean :
	$(RM) tilesolve
