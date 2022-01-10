
all: circuit

run: circuit
		./circuit

binary_tree.o: binary_tree.cpp
		g++ -g -Wall -Wextra -o binary_tree.o -c binary_tree.cpp

parse_input.o: parse_input.cpp
		g++ -g -Wall -Wextra -o parse_input.o -c parse_input.cpp

main.o: main.cpp
		g++ -g -Wall -Wextra -o main.o -c main.cpp

circuit: binary_tree.o parse_input.o main.o
		g++ -g -Wall -Wextra -o circuit main.o parse_input.o binary_tree.o
		