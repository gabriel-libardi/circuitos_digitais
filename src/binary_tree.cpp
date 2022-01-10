#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "binary_tree.hpp"
using namespace std;


BinaryTree *new_tree() {
    BinaryTree *new_empty_tree = (BinaryTree *)malloc(sizeof(BinaryTree));

    if (new_empty_tree == NULL) {
        return NULL;
    }

    *new_empty_tree = NULL;
    return new_empty_tree;
}


bool identity(bool byte) {
    return byte;
}


Port *new_port(string& port_str) {
    Port *new_port = (Port *)malloc(sizeof(Port));
    (new_port->operation).insert(0, port_str, 0, 3);
    new_port->ID = (port_str[5] - '0') + (port_str[4] - '0')*10 + (port_str[3] - '0')*100;
    new_port->value = 0;

    return new_port;
}


Node *new_node(Port *new_element) {
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node == NULL) {
        return NULL;
    }

    new_node->left_subtree = NULL;
    new_node->right_subtree = NULL;
    new_node->data_ptr = new_element;

    return new_node;
}


void erase_tree(BinaryTree *binary_tree) {
    if (binary_tree == NULL) {
        return;
    }

    erase_nodes(*binary_tree);
    free(binary_tree);
}


void erase_nodes(Node *subtree) {
    if (subtree) {
        erase_nodes(subtree->left_subtree);
        erase_nodes(subtree->right_subtree);
        (subtree->data_ptr->operation).~string();
        free(subtree->data_ptr);
        free(subtree);
    }
}


bool is_tree_empty(BinaryTree *binary_tree) {
    return (binary_tree == NULL) || (*binary_tree == NULL);
}


void add_head(BinaryTree *binary_tree, Port *new_element) {
    Node *new_node_ptr = new_node(new_element);
    new_node_ptr->left_subtree = *binary_tree;
    *binary_tree = new_node_ptr;
}


Node *get_head(BinaryTree *binary_tree) {
    return *binary_tree;
}


bool _compute_circuit(Node *head) {
    if (head->data_ptr->operation == "INP") {
        return head->data_ptr->value;

    } else if (head->data_ptr->operation == "AND") {
        return _compute_circuit(head->left_subtree) && _compute_circuit(head->right_subtree);

    } else if (head->data_ptr->operation == "OR-") {
        return _compute_circuit(head->left_subtree) || _compute_circuit(head->right_subtree);

    } else {
        return !_compute_circuit(head->left_subtree);
    }
}


bool compute_circuit(BinaryTree *circuit) {
    return _compute_circuit(get_head(circuit));
}



Node *search_tree(Node *circuit, string& father_op, int ID) {
    if (circuit == NULL) {
        return NULL;

    } else if (circuit->data_ptr->operation == father_op && circuit->data_ptr->ID == ID) {
        return circuit;

    } else {
        Node *left_search = search_tree(circuit->left_subtree, father_op, ID);
        Node *right_search = search_tree(circuit->right_subtree, father_op, ID);

        return (left_search != NULL) ? left_search : right_search;
    }
}


void insert_port(BinaryTree *circuit, Port *new_port, string& position, string& father_op, int ID) {
    if (new_port->operation == "INP") {
        string trash_str;
        bool input;

        cin >> trash_str;
        cin >> input;

        new_port->value = input;
    }

    Node *father = search_tree(get_head(circuit), father_op, ID);

    if (father == NULL) {
        add_head(circuit, new_port);

    } else if (position == "U" || position == "L") {
        Node *new_node_ptr = new_node(new_port);
        father->left_subtree = new_node_ptr;

    } else if (position == "R") {
        Node *new_node_ptr = new_node(new_port);
        father->right_subtree = new_node_ptr;
    }
}


size_t height(BinaryTree *binary_tree) {
    if (is_tree_empty(binary_tree)) {
        return 0;
    }

    size_t left_height = height(&((*binary_tree)->left_subtree));
    size_t right_height = height(&((*binary_tree)->right_subtree));

    return (right_height < left_height) ? (left_height + 1) : (right_height + 1);
}


size_t num_nodes(BinaryTree *binary_tree) {
    if (is_tree_empty(binary_tree)) {
        return 0;
    }

    size_t num_left = num_nodes(&((*binary_tree)->left_subtree));
    size_t num_right = num_nodes(&((*binary_tree)->right_subtree));

    return (num_left + num_right + 1);
}


long balance_factor(Node *node) {
    return (height(&(node->left_subtree)) - height(&(node->right_subtree)));
}


void pre_order(BinaryTree *binary_tree, void (*function)(Port *)) {
    if (binary_tree == NULL) {
        return;

    } else if (*binary_tree != NULL) {
        (*function)((*binary_tree)->data_ptr);

        pre_order(&((*binary_tree)->left_subtree), function);
        pre_order(&((*binary_tree)->right_subtree), function);
    }
}


void in_order(BinaryTree *binary_tree, void (*function)(Port *)) {
    if (binary_tree == NULL) {
        return;

    } else if (*binary_tree != NULL) {

        in_order(&((*binary_tree)->left_subtree), function);
        (*function)((*binary_tree)->data_ptr);
        in_order(&((*binary_tree)->right_subtree), function);
    }
}


void post_order(BinaryTree *binary_tree, void (*function)(Port *)) {
    if (binary_tree == NULL) {
        return;

    } else if (*binary_tree != NULL) {
        post_order(&((*binary_tree)->left_subtree), function);
        post_order(&((*binary_tree)->right_subtree), function);

        (*function)((*binary_tree)->data_ptr);
    }
}