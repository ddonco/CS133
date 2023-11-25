/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #1, 04/10/23

The Melody class is used to store a queue of Note objects, a representation of a song,
and provides an API to play the song, change the tempo, reverse the song, and more.
*/

#include "Melody.h"

Melody::Melody(queue<Note> *song) : songQ(song), totalDuration(0) {
    if (songQ == nullptr) {
        throw string("melody is null");
    }

    totalDuration = traverse(false);
}

double Melody::traverse(bool play) {
    double duration = 0;
    bool repeat = false;
    queue<Note> repeatNotes;
    for (int n = 0; n < songQ->size(); n++) {
        Note note = songQ->front();
        duration += note.getDuration();
        if (play) {
            note.play();
        }
        songQ->push(note);
        if (note.isRepeat() || repeat) {
            repeatNotes.push(note);
        }
        if (note.isRepeat() && !repeat) {
            repeat = true;
        } else if (note.isRepeat() && repeat) {
            repeat = false;
            int repeatSize = repeatNotes.size();
            for (int r = 0; r < repeatSize; r++) {
                duration += repeatNotes.front().getDuration();
                if (play) {
                    repeatNotes.front().play();
                }
                repeatNotes.pop();
            }
        }
        songQ->pop();
    }
    return duration;
}

double Melody::getTotalDuration() const {
    return totalDuration;
}

void Melody::changeTempo(double tempo) {
    if (tempo < 0) {
        throw string("tempo must be positive value");
    }
    totalDuration *= tempo;
    for (int n = 0; n < songQ->size(); n++) {
        Note note = songQ->front();
        note.setDuration(tempo * note.getDuration());
        songQ->push(note);
        songQ->pop();
    }
}

void Melody::reverse() {
    stack<Note> tempStack;
    int size = songQ->size();
    for (int n = 0; n < size; n++) {
        Note note = songQ->front();
        tempStack.push(note);
        songQ->pop();
    }
    for (int n = 0; n < size; n++) {
        songQ->push(tempStack.top());
        tempStack.pop();
    }
}

void Melody::append(Melody &other) {
    totalDuration += other.getTotalDuration();
    int size = other.songQ->size();
    for (int n = 0; n < size; n++) {
        Note note = other.songQ->front();
        songQ->push(note);
        other.songQ->push(note);
        other.songQ->pop();
    }
}

void Melody::play() {
    traverse(true);
}

ostream &operator<<(ostream &out, Melody &song) {
    for (int n = 0; n < song.songQ->size(); n++) {
        Note note = song.songQ->front();
        out << note << endl;
        song.songQ->push(note);
        song.songQ->pop();
    }
    return out;
}