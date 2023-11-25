/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #4, 05/15/23

QuestionNode implements an object that stores a node type as a char, data as a
string, and two pointers to other QuestionNodes with names left and right.
*/

#include "QuestionNode.h"

QuestionNode::QuestionNode() : QuestionNode(0, "") {}

QuestionNode::QuestionNode(char type, string data)
    : QuestionNode(type, data, nullptr, nullptr) {}

QuestionNode::QuestionNode(char type, string data, QuestionNode *left, QuestionNode *right)
    : type(type), data(data), left(left), right(right) {}
