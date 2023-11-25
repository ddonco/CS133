// CS 133 Project 4: 20 Questions

// Interface describing abstract user interaction operations.
// This interface is implemented by the graphical and text UIs for the game.
// Your QuestionTree interacts with the UI through this interface.
// @author Allison Obourn
// @version 2021/08/03

// Uncomment the USING_QT define if you want to run the program in QtCreator.
// This will allow you to rovide user input and not have to type "res/" before
// all the file names. If you are using VSCode keep it commented out.

//#define USING_QT

#ifndef _userinterface_h_
#define _userinterface_h_
#undef UserInterface

#include <string>
#include <iostream>

using namespace std;

#ifdef USING_QT
const string PREFIX = "res/";
#include "console.h"
#else
const string PREFIX = "";
#endif

class UserInterface {
public:

    virtual void print(string text) = 0;
    virtual void printLine(string text) = 0;
    virtual string readLine() = 0;
    virtual bool readBoolean() = 0;

    // various messages that are output by the user interface
    // (your QuestionTree does not need to refer to these messages)
    const string PLAY_AGAIN_MESSAGE = "Challenge me again? ";
    const string SAVE_MESSAGE = "Shall I remember these games? ";
    const string LOAD_MESSAGE = "Shall I recall our previous games? ";
    const string SAVE_LOAD_FILENAME_MESSAGE = "What is the file name? ";
    const char* STATUS_MESSAGE = "Games played: %d\nI won: %d\n";
    const string BANNER_MESSAGE = "Think of an item, and I will guess it.";
};

#endif
