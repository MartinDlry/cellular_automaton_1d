main.ex : main.o CA1D.o 
	g++ main.o CA1D.o -o main.ex

main.o : main.cpp CA1D.hpp
	g++ -Wall -ansi -pedantic -std=c++11 -c main.cpp

CA1D.o : CA1D.cpp CA1D.hpp
	g++ -Wall -ansi -pedantic -std=c++11 -c CA1D.cpp

clean :
	-rm *.o *.ex
