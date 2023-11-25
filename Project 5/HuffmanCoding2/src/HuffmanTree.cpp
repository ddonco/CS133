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

#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(map<char, int> counts) {
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, HuffNodeCompare> pq;
    HuffmanNode *newNode;
    // Loop through a map of characters and character counts. Create a Huffman node for
    // each character. Add the Huffman nodes to a priority queue which sorts the queue
    // from smallest count to largest.
    for (auto const pair : counts) {
        newNode = new HuffmanNode(pair.first, pair.second);
        pq.push(newNode);
    }
    // Add EOF character to queue.
    newNode = new HuffmanNode(-1, 1);
    pq.push(newNode);
    // Build a Huffman tree from the queue.
    queueToTree(pq);
}

HuffmanTree::HuffmanTree(istream *in) : root(nullptr) {
    // Loop through the input stream and parse the Huffman encodings of the provided file.
    if (in->good()) {
        string character;
        while (getline(*in, character)) {
            string encoding;
            getline(*in, encoding);
            // Add a node to the Huffman tree as each character and encoding sequence are
            // read from the input stream.
            addNode(stoi(character), encoding);
        }
    }
}

void HuffmanTree::queueToTree(
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, HuffNodeCompare> &pq) {
    // Create new 'internal' tree Huffman nodes from the first to Huffman nodes in the
    // queue and set the left child to the first node and the right child to the
    // second node. Repeat this till all nodes in the queue have been added to the tree.
    while (pq.size() > 1) {
        HuffmanNode *firstNode = pq.top();
        pq.pop();
        HuffmanNode *secondNode = pq.top();
        pq.pop();
        int sum = firstNode->count + secondNode->count;
        HuffmanNode *newNode = new HuffmanNode(0, sum, firstNode, secondNode);
        pq.push(newNode);
    }
    root = pq.top();
    pq.pop();
}

void HuffmanTree::addNode(char character, string encoding) {
    if (encoding != "") {
        addNode(root, character, encoding);
    }
}

void HuffmanTree::addNode(HuffmanNode *&node, char character, string encoding) {
    // Recursively step through the provided encoding extracting one 0 or 1 bit at a time.
    // Add nodes to the tree based on the encoding values.
    if (encoding.size() == 0 && node == nullptr) {
        node = new HuffmanNode(character, 0);
    } else {
        if (node == nullptr) {
            node = new HuffmanNode();
        }
        // If the next encoding bit is a 0, move to the right from the current current node.
        // If the next encoding bit is a 1, move to the left.
        char direction = encoding[0];
        encoding = encoding.substr(1);
        if (direction == '0') {
            addNode(node->left, character, encoding);
        } else {
            addNode(node->right, character, encoding);
        }
    }
}

map<char, string> HuffmanTree::createEncodings() {
    createEncodings(root, "");
    return encodings;
}

void HuffmanTree::createEncodings(HuffmanNode *node, string encoding) {
    if (node != nullptr) {
        if (node->left == nullptr && node->right == nullptr) {
            encodings[node->character] = encoding;
        } else {
            createEncodings(node->left, encoding + "0");
            createEncodings(node->right, encoding + "1");
        }
    }
}

void HuffmanTree::compress(ifstream *input, OBitStream *output) {
    if (input->good()) {
        char character;
        // Loop through the characters in the input stream, get the binary encoding
        // for each character, and write the encodings to the output stream.
        while (input->get(character)) {
            output->writeBits(encodings[character]);
        }
        output->writeBits(encodings[EOF]);
    }
}

void HuffmanTree::decompress(IBitStream *input, OBitStream *output) {
    char character = 0;
    while (character != EOF) {
        character = decompress(root, input);
        if (character != EOF) {
            output->write(character);
        }
    }
}

char HuffmanTree::decompress(HuffmanNode *node, IBitStream *input) {
    // Recursively step through the input stream to decode bits to characters.
    // Once a leaf node is reached, get the character and write it to the output stream
    // to complete the deconding for this character.
    if (input->good()) {
        if (node->left == nullptr && node->right == nullptr) {
            return node->character;
        } else {
            // If the next bit is a 0, move to the left in the tree. If its a 1, go right.
            int direction = input->readBit();
            if (direction == 0) {
                return decompress(node->left, input);
            } else {
                return decompress(node->right, input);
            }
        }

    } else {
        return EOF;
    }
}
