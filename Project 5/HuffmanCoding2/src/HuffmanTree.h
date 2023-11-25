/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #5, 05/21/23

HuffmanTree implements an binary search tree representing a Huffman tree and can be used to both
encode text into a compressed bit state, or decode compressed bits back into ascii text. The
class provide the following member functions: 'createEncodings' to generate binary encodings
for ascii character, 'compress' to compress ascii text into bits using the generated Huffman
encodings, and 'decompress' to decode compressed bits into ascii text using supplied Huffman
encodings.
*/

#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

#include <iostream>
#include <map>
#include <queue>

#include "BitStream.h"
#include "HuffmanNode.h"

using namespace std;

/*
HuffNodeCompare defines a structure containing a comparison operator override for a priority
queue. The HuffNodeCompare override sorts Huffman nodes by their count parameter from
smallest to largest.
*/
struct HuffNodeCompare {
    bool operator()(const HuffmanNode *node1, const HuffmanNode *node2) {
        return node1->count > node2->count;
    }
};

class HuffmanTree {
private:
    HuffmanNode *root;           // Pointer to the root HuffmanNode of the tree.
    map<char, string> encodings; // The mad of encodings from character to encoding string.

    /*
    queueToTree takes a priority queue of Huffman nodes and builds a Huffman tree where the root
    parameter stores the root of the tree.
    */
    void queueToTree(priority_queue<HuffmanNode *, vector<HuffmanNode *>, HuffNodeCompare> &q);
    /*
    addNode takes a character and an IBitStream encoding of a character and adds a Huffman node
    to the Huffman tree. The provided encoding specifies the location in the tree at which
    the new node is added and the character property of the node stores the provided character.
    */
    void addNode(char character, string encoding);
    /*
    addNode takes a pointer to a reference of a node, a character, and a pointer to anIBitStream
    encoding. addNode recursively steps through a Huffman tree using the IButStream encosing
    to specify the direction to move at each node. Once the final position is reached, a new
    node is added to the Huffman tree and the character is set to the provided character.
    */
    void addNode(HuffmanNode *&node, char character, string encoding);
    /*
    createEncodings takes a pointer to a Huffman node and an encoding string. The function
    recursively steps through a Huffman tree to build the encoding string for each character
    in the tree. As the function completes the encoding for each character, it adds the
    character and the encoding to the encodings map.
    */
    void createEncodings(HuffmanNode *node, string encoding);
    /*
    decompress takes a pointer to a Huffman node and a pointer to an IBitStream. decompress
    recursively steps through a Huffman tree to decompress the bits in the passed in input.
    As each sequence of bits in the encoded input is decompressed to a character, the
    character is written to the output stream.
    */
    char decompress(HuffmanNode *node, IBitStream *input);

public:
    /*
    HuffmanTree constructor that takes a map of characters and the count of each character in a
    file. The constructor will build a Huffman tree using this map.
    */
    HuffmanTree(map<char, int> counts);
    /*
    HuffmanTree constructor that takes a pointer to an istream containing ascii table values for
    characters and the Huffman tree encodings for these characters. This consturctor will build
    a Huffman tree based on the contents of the istream.
    */
    HuffmanTree(istream *in);
    /*
    createEncodings builds a map of characters in the Huffman tree and the binary encoding of
    of each character (corresponds to the characters position in the tree). createEncodings
    returns the generated encodings.
    Parameters:
        none
    Returns:
        encodings   map<char, string>   A map containing all characters in the Huffman tree
                                        and their binary encodings.
    */
    map<char, string> createEncodings();
    /*
    compress takes in a pointer to an input file stream and a pointer to an output bit stream.
    The contents of the ifstream will be encoded using the character encodings of the
    Huffman tree to reduce the size of the data. The encoded text of the ifstream is output
    to the OBitStream.
    Parameters:
        input   ifstream*       An input file stream from whict text will be read and encoded.
        output  OBitStream*     An output bit stream to which the encoded text will be written.
    */
    void compress(ifstream *input, OBitStream *output);
    /*
    decompress takes a pointer to an input bit stream and a pointer to an output bit stream as
    pointers. decompress takes a stream of bits of compressed data and using a Huffman tree the
    data is decompressed into ascii characters. The decompressed ascii characters are output
    to the OBitStream.
    Parameters:
        input   IBitStream*     An input bit stream of compressed data to be decompressed using
                                a Huffman tree.
        output  ObitStream*     An output bit stream to which decompressed ascii characters are
                                written.
    */
    void decompress(IBitStream *input, OBitStream *output);
};

#endif
