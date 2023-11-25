// CS 131 Project 2

// This file is the main program that will use your WordGuesser program. It
// reads a dictionary of words to be used during the game and then plays a game
// with the user. This is a cheating version of a guessing game that delays
// picking an answer (word) to keep its options open.

// You can change the setting for SHOW_COUNT to see how many options are still
// left on each turn.

// You can change the setting for DICTIONARY_FILE to try running with the full
// scrabble dictionary

// WARNING: this file will (and should!) show compiler errors until you have
//          written headers and empty implementations for all of the required
//          classes and functions.

#include "WordGuesser.h"
#include <cctype>
#include <fstream>
#include <iostream>

using namespace std;

const string DICTIONARY_FILE = "dictionary.txt";
const bool SHOW_COUNT = true; // show # of choices left

// Plays one game with the user
void playGame(WordGuesser *guessManager) {
    while (guessManager->getGuessesLeft() > 0 &&
           guessManager->getPattern().find("-") != string::npos) {
        cout << "guesses : " << guessManager->getGuessesLeft() << endl;
        if (SHOW_COUNT) {
            cout << "words   : " << guessManager->getWords()->size() << endl;
        }
        set<char> guesses = guessManager->getGuesses();
        cout << string("guessed : ") << guesses << endl;
        cout << "current : " << guessManager->getPattern() << endl;
        cout << "Your guess? ";
        char ch;
        cin >> ch;
        ch = tolower(ch);
        if (guessManager->getGuesses().count(ch) == 1) {
            cout << "You already guessed that";
        } else {
            int count = guessManager->record(ch);
            if (count == 0) {
                cout << "Sorry, there are no " << ch << "'s" << endl;
            } else if (count == 1) {
                cout << "Yes, there is one " << ch << endl;
            } else {
                cout << "Yes, there are " << count << " " << ch << "'s" << endl;
            }
        }
        cout << endl;
    }
}

// reports the results of the game, including showing the answer
void showResults(WordGuesser *guessManager) {
    // if the game is over, the answer is the first word in the list
    // of words, so we use an iterator to get it
    set<string> *temp = guessManager->getWords();
    string answer = *(temp->begin());
    cout << "answer = " << answer << endl;
    if (guessManager->getGuessesLeft() > 0) {
        cout << "You beat me";
    } else {
        cout << "Sorry, you lose";
    }
}

// returns a string identical to the passed in string except that all
// its characters will be in lowercase
string toLowerCase(const string &word) {
    string result = "";
    for (char c : word) {
        result += tolower(c);
    }
    return result;
}

int main() {
    cout << "Welcome to the CS 133 word guessing game." << endl;
    cout << endl;

    // open the dictionary file and read dictionary into a vector
    ifstream file(DICTIONARY_FILE);
    vector<string> dictionary;
    string next;
    while (file >> next) {
        dictionary.push_back(toLowerCase(next));
    }

    // set basic parameters
    cout << "What length word do you want to use? ";
    int length;
    cin >> length;
    cout << "How many wrong answers allowed? ";
    int max;
    cin >> max;
    cout << endl;

    // set up the WordGuesser and start the game
    WordGuesser *guessManager = new WordGuesser(dictionary, length, max);
    set<string> *words = guessManager->getWords();
    if (words->empty()) {
        cout << "No words of that length in the dictionary.";
    } else {
        playGame(guessManager);
        showResults(guessManager);
    }
}
