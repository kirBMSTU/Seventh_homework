main.o: main.cpp
	g++ -c -o main.o main.cpp
hw: main.o
	g++ -o hw main.o -Wall
