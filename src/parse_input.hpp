#ifndef __PARSE_INPUT_HPP__
#define __PARSE_INPUT_HPP__


#include <fstream>
#include <iostream>
#include <string>
#include "binary_tree.hpp"
using namespace std;


#define MAX_LINE 256


void read_input(string& input_stream, BinaryTree *circuit);


#endif