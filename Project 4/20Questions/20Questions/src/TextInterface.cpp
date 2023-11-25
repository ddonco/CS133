// CS 133 Project 4: 20 Questions
//
// To use the debugger with this program, set a breakpoint
// and once the execution breaks, open 'this' or 'textMain' on the left,
// then look at its member variable 'tree'.  That's your QuestionTree.
// Open your 'tree' to see what it contains.
// 
// (Your QuestionTree is constructed by this file on line 17.
// The overall loop to play games is around line 58.)

#include "TextInterface.h"

using namespace std;

// Constructs a text user interface and its question tree. 
TextInterface::TextInterface() {
    tree = new QuestionTree(this);
}

// Waits for the user to answer a yes/no question on the console and returns the
// user's response as a boolean (true for anything that starts with "y" or "Y").
bool TextInterface::readBoolean() {
    string answer = readLine();
    return answer.length() >= 1 && (answer[0] == 'y' || answer[0] == 'Y');
}

// prints the passed in string to the console followed by a new line
void TextInterface::printLine(string text) {
    cout << text << endl;
}

// prints a blank line to the console
void TextInterface::printLine() {
    cout << endl;
}

// prints the passed in text to the console
void TextInterface::print(string text) {
    cout << text;
}

// reads a line of user input from the console and returns it
string TextInterface::readLine() {
    string result;
    getline(cin, result);
    return result;
}

// private helper for overall game(s) loop
void TextInterface::run() {
    printLine("Welcome to the game of 20 Questions!");
    loadAndSave(LOAD_MESSAGE);
    
    // "Think of an item, and I will guess it in N tries."
    printLine();
    printLine(BANNER_MESSAGE);
        
    do {
        // play one complete game
        printLine();      // blank line between games
        tree->play();
        print(PLAY_AGAIN_MESSAGE);
    } while (readBoolean());   // prompt to play again
    
    // print overall stats
    // Games played: N ...  I have won: M
    cout << endl;
    printf(STATUS_MESSAGE, tree->totalGames(),  tree->gamesWon());

    loadAndSave(SAVE_MESSAGE);
    terminate();
}

// common code for asking the user whether they want to save or load
// and to / from which file
void TextInterface::loadAndSave(string message) {
    print(message);
    if (readBoolean()) {
        print(SAVE_LOAD_FILENAME_MESSAGE);
        string filename = PREFIX + readLine();
        try {
            if(message == LOAD_MESSAGE) {
                load(filename);
            } else {
                save(filename);
            }
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

// reads in the tree data stored in the file with the passed in name. Assumes
// that data is in the correct format.
void TextInterface::load(string filename) {
    ifstream* inFile = new ifstream(filename);
    tree->load(inFile);
    delete inFile;

}

// saves the contents of the current game knowledge (the tree) to the file
// with the passed in name. Replaces whatever is currently stored in that file
void TextInterface::save(string filename) {
    ofstream* outFile = new ofstream(filename);
    tree->save(outFile);
    outFile->close();
    delete outFile;
}
