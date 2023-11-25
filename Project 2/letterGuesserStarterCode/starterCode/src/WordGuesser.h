/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #2, 04/20/23

WordGuesser takes a dictionary of words, a length of a word to guess, and a maximum number of guesses
to establish a word guesser such as used in a game like hangman. At initializaiton the WordGuesser
selects all words in the dictionary that have length equal to the provided length parameter.
WordGuesser provides member functions to guess letters in the word, one by one, and get the number
of guesses left as well as get the pattern of correctly guessed letters in the word. The word guesser
does not select a word at initialization, it maintains a list of possible words that match the guessed
letters and have the same pattern until the guessed letters force the WordGuesser to select a final
word. The objective of the WordGuesser is to avoid seleting a final word as long as possible to
make guessing the word as difficult as possible.
*/

#ifndef WORDGUESSER_H
#define WORDGUESSER_H

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class WordGuesser {
public:
    /*
    The WordGuesser constructor creates an initial set of possible words by selecting all words
    from the passed in dictionary that meet the provided length requirement. The constuctor
    also sets the maximum number of guesses allowed by the WordGuesser. The WordGuesser throws
    an exception if length is less than 1 or if maxGuesses is negative.
    */
    WordGuesser(vector<string> dictionary, int length, int maxGuesses);
    /*
    getWords returns the set of all words that match the lenght requirement and the current
    pattern of guessed letters.
    Parameters:
        none
    Returns:
        words       set<string>     The set of words currently held by the WordGuesser.
    */
    set<string> *getWords();
    /*
    getGuessesLeft returns the number of guesses left for the client. This number is the
    max guesses minus the number of guesses made by the client.
    Parameters:
        none
    Returns:
        guessesLeft     int         The number of guesses left.
    */
    int getGuessesLeft();
    /*
    getGuesses returns the set of letters that have been guessed.
    Parameters:
        none
    Returns:
        guesses     set<char>       The letters that have been guessed.
    */
    set<char> getGuesses();
    /*
    getPattern returns the pattern of correctly guessed letters that match the word or words
    held by the WordGuesser as the possible final word. getPattern throws an exception if there are
    no words that meet the word length and guessed letter constraints. In other words, if
    the WordGuesser can find no words that meet the client inputs, an exception will be thrown
    when this method is called.
    Parameters:
        none
    Returns:
        pattern     string      The pattern of correctly guessed letters.
    */
    string getPattern();
    /*
    record allows the client to guess a new letter and it returns the count of occurences of
    the guessed letter in the selected word(s). record throws an exception under several scenarios,
    1) the number of guesses remaining equals 0, 2) there are no words that meet the word
    size and guessed letter constraints, or 3) the character passed in to 'guess' has been
    used previously.
    Parameters:
        guess       char        A new letter to guess.
    Returns:
        count       int         The count of occurences of the guessed letter in the
                                selected word(s).
    */
    int record(char guess);

private:
    int guessesLeft;    // number of guesses left
    set<string> *words; // selected word(s)
    set<char> guesses;  // all guessed letters
    string pattern;     // the pattern of correctly guessed letters

    /*
    wordToPattern returns the matching letter pattern for the given word using the set of
    correctly guessed letters.
    Parameters:
        word        string          A word from which the letter pattern will be generated.
    Returns:
        pattern     string          The pattern of correctly guessed letters in the word.
    */
    string wordToPattern(string word);
    /*
    guessMatchCount returns the count of the given letter in the current pattern.
    Parameters:
        guess       char            A guessed letter.
    Returns:
        count       int             The count of the letter in the current pattern.
    */
    int guessMatchCount(char guess);
};

// print operator for a set of any type
// outputs all items in the set separated by spaces
/*
Operator override for the << ostream operator to allow for sending a set of
any data type to an output stream.
Parameters:
    out     ostream     The output stream to which the set will be sent.
    words   set<T>      A set of any data type to be sent to the output.
Returns:
    out     osteam      The output stream containing the set data.
*/
template <typename T>
ostream &operator<<(ostream &out, const set<T> &words) {
    for (const T &word : words) {
        cout << (T)word << " ";
    }
    return out;
}

#endif