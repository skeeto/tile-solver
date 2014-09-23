CFLAGS = -std=c99 -Wall -g

beetle : beetle.c

run : beetle
	./$^

clean :
	$(RM) beetle
