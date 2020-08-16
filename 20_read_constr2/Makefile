CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
code: code.o
	g++ -o code code.o
code.o: code.cpp
	g++ $(CPPFLAGS) -c code.cpp

.PHONY: clean
clean:
	rm -f *.o *~ code
