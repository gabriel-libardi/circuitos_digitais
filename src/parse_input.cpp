#include <fstream>
#include <iostream>
#include <string>
#include "binary_tree.hpp"
#include "parse_input.hpp"
using namespace std;


void read_input(string& input_stream, BinaryTree *circuit) {
    fstream circuit_txt;
    circuit_txt.open(input_stream, fstream::in);

    while (!circuit_txt.eof()) {
        string new_port_str;
        circuit_txt >> new_port_str;

        if (new_port_str == "$END00" || new_port_str == "OUTPUT") {
            circuit_txt.ignore(MAX_LINE, '\n');
            continue;
        }

        Port *new_port_ptr = new_port(new_port_str);
        string position;
        string father;

        circuit_txt >> position;
        circuit_txt >> father;

        int identity = (father[5] - '0') + (father[4] - '0')*10 + (father[3] - '0')*100;
        insert_port(circuit, new_port_ptr, position, op_convert(father), identity);
    }
}