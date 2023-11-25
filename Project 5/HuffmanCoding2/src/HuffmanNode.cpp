/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #5, 05/21/23

HuffmanNode implements an object that stores a character as a char, a character count as an
int, and two pointers to other HuffmanNode with names left and right.
*/

#include "HuffmanNode.h"

HuffmanNode::HuffmanNode() : HuffmanNode(0, 0) {}

HuffmanNode::HuffmanNode(char character) : HuffmanNode(character, 0, nullptr, nullptr) {}

HuffmanNode::HuffmanNode(char character, int count) : HuffmanNode(character, count, nullptr, nullptr) {}

HuffmanNode::HuffmanNode(char character, int count, HuffmanNode *left, HuffmanNode *right) : character(character), count(count), left(left), right(right) {}
