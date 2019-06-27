robots: robots.o getchar.o
	gcc -o $@ $^

%.o : %.c
	gcc -c -Wall -O2 -o $@ $<
