CFLAGS = -std=c99 -Wall -g3

beetle : beetle.c

run : beetle
	./$^ < beetles.txt

clean :
	$(RM) beetle
