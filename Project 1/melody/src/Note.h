// CS 133, Project 1: Melody
//
// Instructor-provided code.

// This file contains the definitions of the Accidental, Pitch and Note types.

// Accidentals are modifiers that specify a Note as either sharp flat or neither 
// (natural). 

// Pitches are what we commonly think of as a Note's value -  A, B, C, D, E, F or G.
// A pause in music (a rest) is represented here as having a pitch of R

// Notes represent musical notes. They have a pitch, accidental value, octave 
// (since we repeat the letters A-G every octave) and length. Notes also know if 
// they are at the beginning/end of a repeated section.

// Your code should be able to work with this code as provided. However, you may find
// it useful to alter the two following defines:

#define DEFAULT_WHOLE_NOTE 2000
    // The length in milliseconds of a whole note. Change this to a higher number 
    // if you can only hear some of the notes playing. Some systems can't keep up with
    // a fast tempo.

//#define SILENT_MODE
    // Uncomment the above line if you want to have your code print the notes instead 
    // of play them. This can be very helpful for debugging and when you are working in 
    // a place where you need to be quiet.


#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <map>
#include "gsound.h"

using namespace std;

// An Accidental represents a musical accidental; sharp, flat or natural.
enum Accidental { SHARP, NATURAL, FLAT};

// Represents a musical pitch. R represents a rest, no pitch.
enum Pitch { A, B, C, D, E, F, G, R};

// A map of the strng representation of each accidental value to that accidental value enum
const map<string, Accidental> stringToAccidental {
   {"SHARP", SHARP}, {"NATURAL", NATURAL}, {"FLAT", FLAT}
};

// A map of each accidental to its string representation
const map<int, string> accidentalToString {{0, "SHARP"}, {1, "NATURAL"}, {2, "FLAT"}};    


// A Note object represents a musical note in scientific music notation. 
// For example, middle C is represented as C4. The pitch is always a 
// letter A - G or R if it is a rest and the number represents what octave
// we want that pitch from. Octave 0 is usually the lowest octave available on
// a piano and pitches increase as the octave number increases

class Note {
private:
    Pitch note; // letter value of the note
    double duration; // the length of the note in seconds
    int octave; // the octave of the note
    Accidental accidental; // whether the note is sharp, flat or natural
    bool repeat; // true if this is the start or end of a repeated section
    sgl::GSound* player; // a media player to play this note so you can hear it
public:  

    // pre : duration > 0 and 0 <= octave <= 7, otherwise throws a string exception
    // constructs a note with the provided duration, pitch, octave, accidental 
    // and repeat settings.
    Note(double duration, Pitch note, int octave, Accidental accidental, bool repeat);

    // pre : duration > 0, otherwise throws a string exception
    // constructs a note with the passed in duration, pitch and repeat settings. 
    Note(double duration, Pitch note, bool repeat);

    // returns the length of the note in seconds
    double getDuration();

    // returns the Accidental value of the note
    Accidental getAccidental();

    // returns the octave of the note
    int getOctave();

    // returns the pitch of the note (A - G or R of it is a rest)
    Pitch getPitch();

    // pre : d must be greater than 0, otherwise a string exception is thrown
    //       sets the duration of the note to be the given time
    void setDuration(double d);

    // sets the accidental of the note to be the given accidental
    void setAccidental(Accidental a);

    // pre : octave must be greater than 0 and less than 7, 
    //       otherwise a string exception is thrown
    // sets the octave of the note to be the passed in octave
    void setOctave(int octave);

    // sets the pitch of the note to be the passed in pitch
    void setPitch(Pitch pitch);

    // sets the repeat of the note to be the passed in repeat
    void setRepeat(bool repeat);

    // returns true if the note is the beginning or ending note in a repeated section, 
    //  false otherwise
    bool isRepeat();

    // plays the sound this note represents if the note has a sound value. If it is a
    // rest pauses until the correct amount of time has elapsed.
    // NOTE: currently this ignores sharps and flats
    // NOTE: if the DEFAULT_WHOLE_NOTE is too short then you won't be able to hear
    //       the note on some machines. You can change this value at the top of
    //       Note.h
    void play();

};

// outputs a string in the format "<duration> <pitch> <repeat>" if the note is a rest,
//       otherwise outputs a string in the format: 
//       "<duration> <pitch> <octave> <accidental> <repeat>"
//       For example "2.3 A 4 SHARP true" and "1.5 R true".
ostream& operator<< (ostream& out, Note n);


#endif