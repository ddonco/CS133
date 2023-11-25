// CS 133 Project 4: 20 Questions
//
// This main file allows you to run your program either with a text-based
// interface or with a graphical interface.

// Uncomment the GUI variable define below when you want to run with
// graphics. Leave it commented to run with just text.

//#define GUI

#ifndef GUI
    #include "TextInterface.h"
    #include "console.h"
#else
    #include "VaderGUI.h"
#endif


int main() {
#ifndef GUI
    TextInterface textMain;
    textMain.run();
#else
    new VaderGUI();
#endif
    return 0;

}
