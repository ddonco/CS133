#ifndef QUESTIONTREE_H_
#define QUESTIONTREE_H_

#include <iostream>
#include <string>
/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #4, 05/15/23

QuestionTree implements the functions needed to play a game of 20 questions with the
computer as the opponent. The computer will repeatedly ask the client questions
until either the computer wins by guessing the correct answer or it fails to find
the right answer and looses. If the computer looses, it will ask the client for
the answer, it will ask for a question that would help identify the answer, and
it will ask for the yes/no answer to the question that will lead to the answer.
Additionally QuestionTree provides functionality to save a game, load a game and
get some simple stats on the games played in a session.
*/

#include "QuestionNode.h"
#include "UserInterface.h"

using namespace std;

class QuestionTree {
private:
    UserInterface *ui;  // Pointer to a UserInterface object.
    QuestionNode *root; // Pointer to the root node of the question tree.
    int _totalGames;    // Total games played.
    int _gamesWon;      // Count of games won by the computer.

    /* save takes a passed in pointer to an ostream object and a pointer to a QuestionNode
     * and recursively iterates from the provided node through all child nodes and
     * outputs the node type and data to the ostream. save iterates through the
     * nodes in a pre-order traversal.
    */
    void save(ostream *output, QuestionNode *node);
    /* load takes a passed in pointer to an istream object (a file) and a pointer to a QuestionNode
     * and iterates through the lines in the file to rebuild a saved QuestionTree. Each line
     * in the file represents a node in the tree where the type of node is either a 'Q' for a
     * question or an 'A' for an answer. The saved QuestionTree is expected to be in
     * pre-order traversal format.
    */
    void load(istream *input, QuestionNode *&node);
    /* save takes a passed in pointer to a reference of a QuestionNode. play recursively moves through
     * a QuestionTree to either present a question to the client or suggest an answer. By moving through
     * the tree, this function effectively plays a game of 20 questions. If the tree contains the
     * correct answer, it will output a message saying that he algorithm has won, it will increment
     * _gamesWon, and it will end the current game. If the tree doesn't contain the answer, this function
     * will prompt the client to enter the answer, a question to help guess the answer, and a 'yes', 'no'
     * reponse to the question.
    */
    void play(QuestionNode *&node);
    /* askYesNoQuestion takes a question as a string and a supplemental variable for the question as
     * a second string. This function will prompt the client with the question + var string and
     * wait for client input in the form of a 'yes' or 'no'. The client input is not case sensitive
     * and the response can be anything that starts with a 'y' for a yes, and anything that starts
     * with an 'n' for a no. This function returns true when the client's response is a yes, and false
     * otherwise.
    */
    bool askYesNoQuestion(string question, string var);
    /* askOpenQuestion takes a question as a string and a supplemental variable for the question as
     * a second string. This function will prompt the client with the question + var string and
     * waits for the client to input any string as a response. The function returns the client
     * entered string.
    */
    string askOpenQuestion(string question, string var);
    /* deleteTree takes a passed in pointer to a QuestionNode and recursively iterates through all nodes
     * in the tree. Once the leaves in the tree have been reached the function then deletes the nodes
     * working backward to the originating node thereby removing the QuestionTree from the heap.
    */
    void deleteTree(QuestionNode *node);

public:
    /* The QuestionTree constructor accepts a pointer to a user interface which will facilitate reading
     * strings from the client and outputing strings to the client. The constructor initializes a
     * new game of 20 questions with an empty tree.
    */
    QuestionTree(UserInterface *ui);
    /* The QuestionTree destructor deallocates all memory on the head used to store the tree.
    */
    ~QuestionTree();
    /* totalGames returns the total count of games played in one session.
    */
    int totalGames();
    /* gamesWon returns the count of games won by the algorithm in one session.
    */
    int gamesWon();
    /* play initiates a game of 20 questions and increments the count of games played. If play has been
     * called for a new game, the algorithm with start by asking the client if the answer is "computer".
     * From this point the client can provide the algorithm with new questions and answers to help
     * the algorithm learn and get better at the game. A game is finished when the algorithm guesses
     * the correct answer.
    */
    void play();
    /* save takes a pointer to an ostream object and outputs the data of the game to the ostream.
     * To save the game, the QuestionTree is traversed in a pre-order fashion and the data of each
     * node are written to the output.
    */
    void save(ostream *output);
    /* load takes a pointer to an istream object and parses the strings in the istream to reconstruct
     * a previous game. When reconstructing a previous game, load expects the lines of the isteam to
     * be arranged as a pre-order traversal of a binary tree and therefore build a QuestionTree using
     * this pre-order traversa assumption.
    */
    void load(istream *input);

    const string GUESS_MESSAGE = "Would your object happen to be ";
    const string ASK_OBJECT_MESSAGE = "I lose. What is your object? ";
    const string GET_QUESTION_MESSAGE = "Type a yes/no question to distinguish your item from ";
    const string GET_ANSWER_MESSAGE = "And what is the answer for your object? ";
};

#endif
