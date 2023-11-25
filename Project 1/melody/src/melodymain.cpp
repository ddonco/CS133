// CS 133, Project 1: Melody
//
// updated 4/11/22
//
// Instructor-provided code.
// This program will allow you to use your Melody code to manipulate songs.
// When the program starts, type load and enter the name of the file you want to
// work with. You can then type play to hear it or any of the other commands to
// test you Melody's other functionality.

// Your code should be able to work with this code as provided. However, you may find
// it useful to alter the defines for DEFAULT_WHOLE_NOTE and SILENT_MODE in Note.h

#include <QApplication>
#include <fstream>
#include <iostream>
#include <queue>

// You can comment out the console.h include if you do not like the separate console that
// pops up
#include "Melody.h"
#include "console.h"
#include "gsound.h"
#include "gthread.h"

using namespace std;

// prints out an introduction describing how to use the program
void intro() {
    cout << "Welcome to MelodyMain. Type the word in the left column to do the action";
    cout << " on the right" << endl;
    cout << "load     : load a new input file" << endl;
    cout << "save     : output to a file" << endl;
    cout << "print    : prints the contents of the last loaded song" << endl;
    cout << "play     : play the last loaded song" << endl;
    cout << "reverse  : reverse the last loaded song" << endl;
    cout << "length   : print out the length of the last loaded song in seconds" << endl;
    cout << "tempo    : change the speed by a percentage" << endl;
    cout << "append   : appends notes from a second melody to the loaded one" << endl;
    cout << "quit     : exit the program" << endl
         << endl;
}

// takes two strings as parameters (one as a reference for efficiency and one
// as a value so as to be able to compare to a literal) and returns true if they
// contain the same letters ignoring casing. Returns false otherwise.
bool equalsIgnoreCase(const string &one, string two) {
    if (one.length() != two.length()) {
        return false;
    }
    for (int i = 0; i < one.length(); i++) {
        if (tolower(one[i]) != tolower(two[i])) {
            return false;
        }
    }
    return true;
}

// Prompts the user for a file name with the passed in prompt text.
// Checks to make sure the file exists. If it doesn't, prompts the user for
// a new file until they input a valid one and returns it.
// always returns a file that exists.
ifstream getFile(string prompt) {
    cout << prompt;
    string file;
    cin >> file;
    // try opening the file to make sure it exists and we can access it
    ifstream input;
    input.open(file);
    // keep prompting for a new file until we get one we can access
    while (!input.good()) {
        cout << "Invalid file. File name? ";
        cin >> file;
        input.open(file);
    }
    return input;
}

// pre: the ifstream is valid and contains data in the format:
//      <length> <pitch> <octave> <accidental> <repeat>
//      or, if it is a rest, in the format:
//      <length> R <repeat>
// returns a queue filled with the notes specified in the passed in
// ifstream. The notes will appear in the same order in the queue
// as they did in the file.
queue<Note> *read(ifstream &input) {
    queue<Note> *song = new queue<Note>();
    double duration;
    while (input >> duration) {
        string strPitch;
        input >> strPitch;
        Pitch pitch = (Pitch)(strPitch[0] - 'A');
        string repeat;
        // there are only two other values to read in if we have a rest
        if (pitch == R + 10) {
            input >> repeat;
            bool rep = equalsIgnoreCase(repeat, "FALSE") ? false : true;
            song->push(Note(duration, Pitch::R, rep));
        } else {
            // read the remaining four values since we know it isn't a rest
            int octave;
            input >> octave;
            string temp;
            input >> temp;
            Accidental accident = stringToAccidental.at(temp);
            input >> repeat;
            bool rep = equalsIgnoreCase(repeat, "FALSE") ? false : true;
            song->push(Note(duration, pitch, octave, accident, rep));
        }
    }
    return song;
}

int main() {
    intro();

    Melody *melody = NULL;

    string command = "nothing";
    while (!equalsIgnoreCase(command, "quit")) {
        cout << "What would you like to do? ";
        cin >> command;

        if (!(equalsIgnoreCase(command, "quit") || equalsIgnoreCase(command, "load")) && melody == NULL) {
            cout << "You must load a song before trying to manipulate it";
        } else if (equalsIgnoreCase(command, "load")) {
            ifstream input = getFile("File name? ");
            queue<Note> *song = read(input);
            melody = new Melody(song);
        } else if (equalsIgnoreCase(command, "play")) {
            melody->play();
        } else if (equalsIgnoreCase(command, "reverse")) {
            melody->reverse();
        } else if (equalsIgnoreCase(command, "save")) {
            cout << "Output file? ";
            string outFile;
            cin >> outFile;
            ofstream output(outFile);
            output << melody;
        } else if (equalsIgnoreCase(command, "print")) {
            cout << *melody;
        } else if (equalsIgnoreCase(command, "length")) {
            cout << melody->getTotalDuration() << " seconds long" << endl;
        } else if (equalsIgnoreCase(command, "tempo")) {
            cout << "Percentage? ";
            double tempo;
            cin >> tempo;
            melody->changeTempo(tempo);
        } else if (equalsIgnoreCase(command, "append")) {
            ifstream file = getFile("File name of second song? ");
            Melody *other = new Melody(read(file));
            melody->append(*other);
        } else if (!equalsIgnoreCase(command, "quit")) {
            cout << "Invalid command. Please try again.";
            intro();
        }
    }
    cout << "Goodbye!" << endl;

    // gracefully exit the program
    QApplication::quit();
    return 0;
}
