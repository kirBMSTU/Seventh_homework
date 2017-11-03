main.o: main.cpp
	g++ -c -o main.o main.cpp
HW7.o: HW7.cpp
	g++ -c -o HW7.o HW7.cpp
hw: main.o HW5.o
	g++ -o hw HW7.o main.o -Wall 
