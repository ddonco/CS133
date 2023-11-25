// CS 133, Project 1: Melody
//
// Instructor-provided implementation of Note.h. 
// You should not modify this file!

#include <iostream>
#include "Note.h"
#include "gthread.h"

using namespace std;


// pre : duration > 0 and 0 <= octave <= 7, otherwise throws a string exception
// constructs a note with the provided duration, pitch, octave, accidental 
// and repeat settings.
Note::Note(double duration, Pitch note, int octave, Accidental accidental, bool repeat) {
    if(duration <= 0 || octave < 0 || octave > 7) {
        throw string("Illegal parameter");
    }
    this->note = note;
    this->duration = duration;
    this->octave = octave;
    this->accidental = accidental;
    this->repeat = repeat;

    if(note == R) {
        this->player = NULL;
    } else {
        // loads the sound file for this note
        char noteChr = (char) (this->note + 'A');
        string name = noteChr + to_string(octave) + ".mp3";
        this->player = new sgl::GSound(name);
    }
}


// pre : duration > 0, otherwise throws a string exception
// constructs a note with the passed in duration, pitch and repeat settings. 
Note::Note(double duration, Pitch note, bool repeat) : Note(duration, note, 0, NATURAL, repeat) {}

// returns the length of the note in seconds
double Note::getDuration() {
   return duration;
}

// returns the Accidental value of the note
Accidental Note::getAccidental() {
   return accidental;
}

// returns the octave of the note
int Note::getOctave() {
   return octave;
}

// returns the pitch of the note (A - G or R of it is a rest)
Pitch Note::getPitch() {
   return note;
}

// pre : d must be greater than 0, otherwise a string exception is thrown
//       sets the duration of the note to be the given time
void Note::setDuration(double d) {
   if(d <= 0) {
      throw string("duration must be greater than 0");    
   }
   duration = d;
}

// sets the accidental of the note to be the given accidental
void Note::setAccidental(Accidental a) {
   accidental = a;
}

// pre : octave must be greater than 0 and less than 7, 
//       otherwise a string exception is thrown
// sets the octave of the note to be the passed in octave
void Note::setOctave(int octave) {
   if(octave < 0 || octave > 7) {
      throw string("illegal octave value passed - " + to_string(octave));    
   }
   this->octave = octave;
}

// sets the pitch of the note to be the passed in pitch
void Note::setPitch(Pitch pitch) {
   note = pitch;
}

// sets the repeat of the note to be the passed in repeat
void Note::setRepeat(bool repeat) {
   this->repeat = repeat;
}

// returns true if the note is the beginning or ending note in a repeated section, 
// false otherwise
bool Note::isRepeat() {
   return repeat;
}

// plays the sound this note represents if the note has a sound value. If it is a
// rest pauses until the correct amount of time has elapsed.
// NOTE: currently this ignores sharps and flats
// NOTE: if the DEFAULT_WHOLE_NOTE is too short then you won't be able to hear
//       the note on some machines. You can change this value at the top of
//       Note.h
void Note::play() {
    int length = (int)(duration * DEFAULT_WHOLE_NOTE);

#ifndef SILENT_MODE
    if(player != NULL) {
        player->play();
    }
    // wait the length of the note time while the note plays
    sgl::GThread::getQtGuiThread()->join(length);
    if(player != NULL) {
        player->stop();
    }
#else
    cout << *this << endl;
#endif
}


// outputs a string in the format "<duration> <pitch> <repeat>" if the note is a rest,
//       otherwise outputs a string in the format: 
//       "<duration> <pitch> <octave> <accidental> <repeat>"
//       For example "2.3 A 4 SHARP true" and "1.5 R true".
ostream& operator<< (ostream& out, Note n) {
    // convert our enum into a character
    char pitch = n.getPitch() + 'A';
    if(pitch == R) {
        out << n.getDuration() << " " << pitch << " " << n.isRepeat();
    } else {
        string accident = accidentalToString.at(n.getAccidental());
        string rep = n.isRepeat()? "true" : "false";
        out << n.getDuration() << " " << pitch << " " << n.getOctave() << " " 
            << accident << " " << rep;
    }
    return out;
}


