/** CS 133 Project 4: 20 Questions
 * Graphical GUI
 * 
 * This creates a graphical window with a Star Wars image and prompts the 
 * user to play a game of 20 questions against the computer.
 * 
 * WARNING: this interface makes noise! 
 * 
 * WARNING: All of the required QuestionTree member function headers must exist
 *          in QuestionTree.h and you must at least have empty functions for
 *          each with something returned (if the funciton is supposed to return)
 *          in order for this to compile. 
 */


#ifndef _vadergui_h_
#define _vadergui_h_

#include <iomanip>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <memory>

#include "gwindow.h"
#include "glabel.h"
#include "gtextarea.h"
#include "gtextfield.h"
#include "gbutton.h"
#include "gcheckbox.h"
#include "gtypes.h"
#include "ginteractor.h"
#include "gfont.h"
#include "gcolor.h"
#include "gthread.h"
#include "gsound.h"
#include "goptionpane.h"
#include "gobjects.h"
#include "gcontainer.h"

#include "UserInterface.h"
#include "QuestionTree.h"
#include "BlockingQueue.h"

using namespace std;
using namespace sgl;

const bool CONSOLE_OUTPUT = true;  // set to true to print I/O messages

// set to true if it is a trap; false if it is not a trap
const bool ITS_A_TRAP = false;

/** takes a string with format arguments (%s, %d, etc) and enough arguments to fill it
 *  returns a string
 */
template<typename ... Args>
string string_format( const string format, Args ... args ) {
    int size_s = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if (size_s <= 0) { 
        throw runtime_error( "Error during formatting." ); 
    }
    auto size = static_cast<size_t>( size_s );
    auto buf = make_unique<char[]>( size );
    snprintf( buf.get(), size, format.c_str(), args ... );
    return string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside 
}


/** 
 * The graphical user interface (GUI) that talks to your QuestionTree
 * to play a graphical 20 questions game ("The Sith Sense").
 */
class VaderGUI : public UserInterface {
private:
    // data fields
    GWindow* frame;
    GLabel* bannerLabel;
    GContainer* vader;
    GTextArea* statsArea;
    GLabel* messageLabel;  
    GCheckBox* soundBox;
    GButton* yesButton, * noButton;
    GSound* musicClip;
    GTextField* inputField;
    GCheckBox* musicBox;
    
    QuestionTree* game;
    GCanvas* img;

    // these queues hold boolean or string user input waiting to be read
    BlockingQueue<bool> booleanQueue;
    BlockingQueue<string> stringQueue;
    bool waitingForBoolean = true;
    bool waitingForString = false;

    /** Handles user interactions with the graphical components. */
    void actionPerformed(GEvent event);
    
    // turns on/off various graphical components when game events occur
    void doEnabling();
    
    // prints out an error message and returns false if the file doesn't exist, 
    // otherwise returns true
    bool ensureFile(string filename);
    
    // response to pressing Enter on the input text field; completes user input
    void input();

    /** Part of the KeyListener interface.  Responds to key presses. */
    void keyPressed(GEvent event);
    
    // helper method to create one button at specified position/size
    GButton* makeButton(string text, GWindow::Region region);
    
    // helper method to create one button at specified position/size
    GCheckBox* makeCheckBox(string text, bool selected,  GWindow::Region region);

    // response to a 'no' button click or typing 'n'
    void no();
    
    // loads and plays/loops the sound/music file with the given file name
    GSound* playAudioClip(string url, bool loop);

    // plays the background theme music
    void playMusic();

    // randomly picks a mp3 file and plays it
    void playSound();

    // private helper for asking a question with the given initial text
    string readLine(string defaultValue);

    /* The basic game loop, which will be run in a separate thread. */
    void run();

    // common code for asking the user whether they want to save or load
    void saveLoad(bool save);
    
    // sets standard fonts, colors, location and such for the given component
    void setupComponent(GInteractor* comp, GWindow::Region region);
    
    // sets the GUI to wait for a yes/no user input
    void setWaitingForBoolean(bool value);
    
    // sets the GUI to wait for a text user input
    void setWaitingForString(bool value);

    // response to a 'yes' button click or typing 'y'
    void yes();

public:
    /** constructs and sets up GUI and components */
    VaderGUI();

    /** Outputs the given text onto the GUI. */
    void print(string text);
    
    /** Outputs the given text onto the GUI. */
    void printLine(string text = "");

    /** Waits for the user to press Yes or No and returns the boolean. */
    bool readBoolean();
   
    /** Waits for the user to type a line of text and returns that line. */
    string readLine();
};

#endif