robots: robots.o
	gcc -o $@ $^

%.o : %.c
	gcc -c -Wall -O2 -o $@ $<
