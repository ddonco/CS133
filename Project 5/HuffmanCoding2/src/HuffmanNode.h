/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #5, 05/21/23

HuffmanNode implements an object that stores a character as a char, a character count as an
int, and two pointers to other HuffmanNode with names left and right.
*/

#ifndef HUFFMANNODE_H_
#define HUFFMANNODE_H_

class HuffmanNode {
public:
    char character;     // Node character.
    int count;          // Character count.
    HuffmanNode *left;  // Pointer to left child node.
    HuffmanNode *right; // Pointer to right child node.

    /*
    HuffmanNode constructor that takes no arguments. This constructor sets the character as 0,
    the count as 0, and the left and right pointers to null pointers.
    */
    HuffmanNode();
    /*
    HuffmanNode constructor that takes a character argument. This constructor sets the node
    character as the passed in character, the count as 0, and the left and right pointers
    to null pointers.
    */
    HuffmanNode(char character);
    /*
    HuffmanNode constructor that takes character and count arguments. This constructor sets the
    node character as the passed in character, the count as the passed in count, and the left
    and right pointers to null pointers.
    */
    HuffmanNode(char character, int count);
    /*
    HuffmanNode constructor that takes character, count, left child and right child arguments.
    This constructor sets the node character as the passed in character, the count as the passed
    in count, and the left child pointer to the passed in left pointer, and the right child
    pointer to the passed in right pointer.
    */
    HuffmanNode(char character, int count, HuffmanNode *left, HuffmanNode *right);
};

#endif
