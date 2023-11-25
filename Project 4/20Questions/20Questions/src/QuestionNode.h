/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #4, 05/15/23

QuestionNode implements an object that stores a node type as a char, data as a
string, and two pointers to other QuestionNodes with names left and right.
*/

#ifndef QUESTIONNODE_H_
#define QUESTIONNODE_H_

#include <string>

using namespace std;

struct QuestionNode {
    char type;              // Node type, either Q or A.
    string data;            // Node data, either a question or answer.
    QuestionNode *left;     // Pointer to the left child.
    QuestionNode *right;    // Pointer to the right child.

//    QuestionNode constructor that takes no arguments and sets the type as 0, the data as "",
//    nullpointers for the left and right properties.
    QuestionNode();

//    QuestionNode constructor that takes type and data as arguments, and sets
//    nullpointers for the left and right properties.
    QuestionNode(char type, string data);

//    QuestionNode constructor that takes type, data, left, and right as arguemtns to initialize
//    to initialize these parameters.
    QuestionNode(char type, string data, QuestionNode *left, QuestionNode *right);
};

#endif
