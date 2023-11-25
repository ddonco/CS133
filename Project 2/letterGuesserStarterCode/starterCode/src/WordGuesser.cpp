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

#include "WordGuesser.h"

WordGuesser::WordGuesser(vector<string> dictionary, int length, int maxGuesses)
    : guessesLeft(maxGuesses) {
    if (length < 1 || maxGuesses < 0) {
        throw string(
            "word length must be greater than 0 and max guesses must be greater 0 or greater");
    }
    words = new set<string>;
    // Loop through dictionary and select words that match the specified length.
    for (int i = 0; i < dictionary.size(); i++) {
        if (dictionary[i].size() == length) {
            words->insert(dictionary[i]);
        }
    }
    // Initialize pattern.
    stringstream ss;
    ss << "-";
    for (int i = 0; i < length; i++) {
        ss << " -";
    }
    pattern = ss.str();
}

set<string> *WordGuesser::getWords() {
    return words;
}

int WordGuesser::getGuessesLeft() {
    return guessesLeft;
}

set<char> WordGuesser::getGuesses() {
    return guesses;
}

string WordGuesser::getPattern() {
    if ((*words).size() == 0) {
        throw string("no words match the size and guessed letter constaints");
    }
    return pattern;
}

int WordGuesser::record(char guess) {
    if (guessesLeft < 1) {
        throw string("0 guesses left");
    }
    if ((*words).size() == 0) {
        throw string("no words match the size and guessed letter constaints");
    }
    if (guesses.count(guess) == 1) {
        throw string("current guess has been previously used");
    }
    // Add guess to 'guesses'.
    guesses.insert(guess);
    map<string, set<string>> matches;
    // Loop through words, generate a pattern for each word (using the guessed letters),
    // and store the pattern as a key in the 'matches' map with the value being a set
    // of all words with that pattern.
    for (string word : *words) {
        string pat = wordToPattern(word);
        matches[pat].insert(word);
    }
    int mostMatchesCount = 0;
    // Loop through the 'matches' map and find the key, value pair with the most words in the set.
    // Update pattern to be the pattern with the most words.
    for (const auto &[pat, words] : matches) {
        set<string> wordsCast = (set<string>)words;
        if (words.size() > mostMatchesCount) {
            mostMatchesCount = words.size();
            pattern = pat;
        }
    }
    // Update 'words' to be the set with the most words.
    *words = matches[pattern];
    int matchCount = guessMatchCount(guess);
    if (matchCount == 0) {
        guessesLeft--;
    }
    return matchCount;
}

string WordGuesser::wordToPattern(string word) {
    stringstream ss;
    // Loop through letters in word and build a pattern with the letters in 'guesses'.
    for (int i = 0; i < word.size(); i++) {
        if (guesses.count(word[i]) == 1) {
            ss << word[i];
        } else {
            ss << "-";
        }
        if (i < word.size() - 1) {
            ss << " ";
        }
    }
    return ss.str();
}

int WordGuesser::guessMatchCount(char guess) {
    int count = 0;
    // Loop through pattern and count the number of times the guess character appears
    // in the pattern.
    for (int i = 0; i < pattern.size(); i++) {
        if (pattern[i] == guess) {
            count++;
        }
    }
    return count;
}