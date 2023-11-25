// CS 133 Project 4: 20 Questions
//
// To use the jGRASP debugger with this program, set a breakpoint
// and once the execution breaks, open 'this' or 'textMain' on the left,
// then look at its member variable 'tree'.  That's your QuestionTree.
// Open your 'tree' to see what it contains.

#include <string>
#include <iostream>
#include <fstream>
#include "UserInterface.h"
#include "QuestionTree.h"

using namespace std;

// A basic text user interface for the 20 questions game.
class TextInterface : public UserInterface {
public:

    // Constructs a text user interface and its question tree. 
    TextInterface();

    // Waits for the user to answer a yes/no question on the console and returns the
    // user's response as a boolean (true for anything that starts with "y" or "Y").
    bool readBoolean();

    // prints the passed in string to the console followed by a new line
    void printLine(string text);

    // prints a blank line to the console
    void printLine();

    // prints the passed in text to the console
    void print(string text);

    // reads a line of user input from the console and returns it
    string readLine();

    // repeatedly plays games and keeps track of game statistics
    void run();
private:
    QuestionTree* tree;

    // common code for asking the user whether they want to save or load
    // and to / from which file
    void loadAndSave(string message);

    // reads in the tree data stored in the file with the passed in name. Assumes
    // that data is in the correct format.
    void load(string filename);
  
    // saves the contents of the current game knowledge (the tree) to the file
    // with the passed in name. Replaces whatever is currently stored in that file
    void save(string filename);
};