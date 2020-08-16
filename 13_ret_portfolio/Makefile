CFLAGS=-std=gnu99 -pedantic -Wall -Werror -ggdb3 
ret_portfolio: retirement.c retirement.h
	gcc -o ret_portfolio $(CFLAGS) retirement.c -lm

.PHONY: clean
clean:
	rm -f *~ *.o ret_portfolio
