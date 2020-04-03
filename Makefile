all: program

program: main.o graph.o simulated_annealing.o quadratic_placement.o
	g++ -g3 main.o graph.o simulated_annealing.o quadratic_placement.o -o program -fopenmp

main.o: main.cpp
	g++ -g3 -c main.cpp -fopenmp

graph.o: graph.cpp
	g++ -g3 -c graph.cpp -fopenmp

simulated_annealing.o: simulated_annealing.cpp
	g++ -g3 -c simulated_annealing.cpp -fopenmp

quadratic_placement.o: quadratic_placement.cpp
	g++ -g3 -c quadratic_placement.cpp -fopenmp

clean:
	rm *.o
