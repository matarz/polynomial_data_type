CPPFLAGS=-g

all: main.o polynomial.o
	g++ $(CPPFLAGS) -o a.out main.o polynomial.o

main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp

polynomial.o: polynomial.h polynomial.cpp
	g++ $(CPPFLAGS) -c polynomial.h polynomial.cpp

clean:
	rm -f *.o core p

