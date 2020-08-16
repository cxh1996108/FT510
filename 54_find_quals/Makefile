CPPFLAGS=-std=c++11 -pedantic -Wall -Werror -ggdb3
find_quals: find.o profile.o
	g++ -o find_quals find.o profile.o
%.o: %.cpp
	g++ $(CPPFLAGS) -c $<

profile.o: profile.hpp

.PHONY: clean
clean:
	rm -r *.o *~ find_quals

