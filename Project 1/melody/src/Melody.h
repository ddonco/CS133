/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #1, 04/10/23

The Melody class is used to store a queue of Note objects, a representation of a song,
and provides an API to play the song, change the tempo, reverse the song, and more.
*/

#ifndef MELODY_H
#define MELODY_H

#include <iostream>
#include <queue>
#include <stack>
#include <string>

#include "Note.h"

using namespace std;

class Melody {
public:
    /*
    The Melody constructor accepts a pointer to a queue of Note objects representing
    a song. The passed in pointer must not be null.
    */
    Melody(queue<Note> *song);
    /*
    getTotalDuration returns the total duration of the song in seconds.
    Parameters:
        none
    Returns:
        duration    double      The total duration of the song in seconds.
    */
    double getTotalDuration() const;
    /*
    changeTempo changes the duration of each Note object in the song queue, and
    changes the total duration of the song. The tempo value passed in must
    be greater than zero.
    Parameters:
        tempo       double      The new tempo of the song, must be greater than zero.
    Returns:
        none
    */
    void changeTempo(double tempo);
    /*
    reverse will reverse the order of Note objects in the song queue, thereby reversing
    the song.
    Parameters:
        none
    Returns:
        none
    */
    void reverse();
    /*
    append will add the song from another Melody object to the end of the song of this
    Melody.
    Parameters:
        other       Melody      The Melody to be added to the end of this Melody.
    Returns:
        none
    */
    void append(Melody &other);
    /*
    play will loop through the Note objects of the song and play each one, thereby playing
    the song.
    Parameters:
        none
    Returns:
        none
    */
    void play();
    /*
    This << operator override modifys the operator behavior to print the entire song
    in scientific pitch notation.
    Parameters:
        none
    Returns:
        none
    */
    friend ostream &operator<<(ostream &out, Melody &song);

private:
    queue<Note> *songQ;   // A queue of Note objects making up a song.
    double totalDuration; // The total duration of the song in seconds.

    /*
    traverse is used to loop through the notes in the song and by default it sums
    and returns the total duration of the song. Traverse can optionally be used to
    play the song by passing in true to the play parameter.
    Parameters:
        play        bool        Play each Note of the song.
    Returns:
        duration    double      The total duration of the song.
    */
    double traverse(bool play);
};

#endif