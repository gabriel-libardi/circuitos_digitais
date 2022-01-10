#include "parse_input.hpp"
#include "binary_tree.hpp"
#include <iostream>
using namespace std;


int main(int argc, char **argv) {

    BinaryTree *circuit = new_tree();
    string input_stream = "circuit.txt";
    read_input(input_stream, circuit);

    bool result = compute_circuit(circuit);
    cout << result << "\n";

    erase_tree(circuit);
}