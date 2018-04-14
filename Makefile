default: main

main.o : main.cpp
	g++ -o main.o main.cpp -lglut -lGLU -lGL -lm

main: main.o
	g++ -o main main.cpp -lglut -lGLU -lGL -lm