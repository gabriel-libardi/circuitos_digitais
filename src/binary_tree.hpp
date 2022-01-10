#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__


#include <string>
using namespace std;


typedef enum {INP = 0, AND = 1, OR = 2, NOT = 3} gate;


struct Port {
    gate operation;
    int ID;
    bool value;
};

struct Node {
    Port *data_ptr;
    Node *left_subtree;
    Node *right_subtree;
};

typedef Node* BinaryTree;


BinaryTree *new_tree();
Node *new_node(Port *new_element);

void erase_tree(BinaryTree *binary_tree);
void erase_nodes(Node *subtree);

bool is_tree_empty(BinaryTree *binary_tree);
gate op_convert(string& operation);
Port *new_port(string& port_str);
void add_head(BinaryTree *binary_tree, Port *new_element);
Node *get_head(BinaryTree *binary_tree);
bool _compute_circuit(Node *head);
bool compute_circuit(BinaryTree *circuit);
Node *search_tree(Node *circuit, gate father_op, int ID);
void insert_port(BinaryTree *circuit, Port *new_port, string& position, gate father_op, int ID);

size_t height(BinaryTree *binary_tree);
size_t num_nodes(BinaryTree *binary_tree);
long balance_factor(Node *node);

void pre_order(BinaryTree *binary_tree, void (*function)(Port *));
void in_order(BinaryTree *binary_tree, void (*function)(Port *));
void post_order(BinaryTree *binary_tree, void (*function)(Port *));


#endif