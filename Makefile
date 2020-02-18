all: program

program: main.o graph.o
	g++ -g3 main.o graph.o -o program -fopenmp

main.o: main.cpp
	g++ -g3 -c main.cpp -fopenmp

graph.o: graph.cpp
	g++ -g3 -c graph.cpp -fopenmp

clean:
	rm *.o
