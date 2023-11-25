// CS 133 Project 4: 20 Questions

// Implementation of the Vader GUI functions 

#include "VaderGUI.h"

using namespace std;
using namespace sgl;

extern const string PREFIX;

// program constants ---------------------------------------------------------

// sound options
const bool MUSIC = true;
const bool SOUNDFX = true;
const double SOUND_PERCENTAGE = 0.6;  // how often Vader talks
int NUM_SOUNDS = 17;                  // # of mp3 files (up to vader17.mp3)
const int NUM_MUSICS = 9;             // # of mp3 files (up to empire9.mp3)

// text messages that appear on the window
// (these don't need to be constants, but it is bad practice to
// scatter various strings and messages throughout a GUI program's code.)
const string MUSIC_MESSAGE = "Music";
const string SFX_MESSAGE = "Sound FX";
const string YES_MESSAGE = "Yes";
const string NO_MESSAGE = "No";
const string ERROR_MESSAGE = "Error";
string TITLE = "The Sith Sense";

// file names, paths, URLs
const string SAVE_DEFAULT_FILE_NAME = PREFIX + "memory.txt";
const string MUSIC_FILE_NAME = PREFIX + "empire%d.mp3";
string BACKGROUND_IMAGE_FILE_NAME = PREFIX + "vader.png";
string SOUND_FILE_NAME = PREFIX + "vader%d.mp3";

// visual elements
const QFont FONT = GFont::toQFont("Sansserif-16-bold");
const string COLOR = "#06E2F0"; // light teal


// public member functions ---------------------------------------------------

// constructs and sets up GUI and components
VaderGUI::VaderGUI() {
    srand(time(0));
    if (ITS_A_TRAP) {
        // set up GUI settings to show the man himself, Admiral Ackbar
        TITLE = "It's a Trap!!!";
        BACKGROUND_IMAGE_FILE_NAME = PREFIX + "ackbar.png";
        SOUND_FILE_NAME = PREFIX + "ackbar%d.mp3";
        NUM_SOUNDS = 4;
    }
    
    game = new QuestionTree(this);
    
    // construct everybody
    frame = new GWindow();
    frame->setTitle(TITLE);
    frame->setCloseOperation(GWindow::CLOSE_EXIT);
    frame->setResizable(true);
    frame->setClickListener( [=](GEvent event){ this->keyPressed(event); });

    // adds the background image to the interface if the file exists
    vader = new GContainer();
    if (ensureFile(BACKGROUND_IMAGE_FILE_NAME)) {
        img = new GCanvas();
        img->setSize(1000, 300);
        img->drawImage(BACKGROUND_IMAGE_FILE_NAME);

        vader->add(img);
        img->setVisible(true);
        vader->setVisible(true);
    }
    frame->addToRegion(vader, GWindow::REGION_CENTER);

    // general background formatting
    frame->setBackground("black");
    vader->setMargin(0);
    vader->setPadding(0);
    frame->pack();
    frame->center();
    
    messageLabel = new GLabel();
    setupComponent(messageLabel, GWindow::REGION_SOUTH);

    // construct other components
    inputField = new GTextField(30);
    setupComponent(inputField, GWindow::REGION_SOUTH);
    inputField->setKeyListener([=](GEvent event) { this->actionPerformed(event); });
    
    bannerLabel = new GLabel();
    setupComponent(bannerLabel, GWindow::REGION_NORTH);

    statsArea = new GTextArea();
    setupComponent(statsArea, GWindow::REGION_EAST);
    statsArea->setEditable(false);
    
    yesButton = makeButton(YES_MESSAGE, GWindow::REGION_SOUTH);
    noButton = makeButton(NO_MESSAGE, GWindow::REGION_SOUTH);
    yesButton->setClickListener( [=](GEvent event){ keyPressed(event); } );
    noButton->setClickListener( [=](GEvent event){ this->keyPressed(event); });

    musicBox = makeCheckBox(MUSIC_MESSAGE, MUSIC, GWindow::REGION_EAST);
    soundBox = makeCheckBox(SFX_MESSAGE, SOUNDFX, GWindow::REGION_EAST);
    musicBox->setClickListener( [=](GEvent event){ this->keyPressed(event); });
    soundBox->setClickListener( [=](GEvent event){ this->keyPressed(event); });
    
    doEnabling();
    frame->setVisible(true);

    // start background thread to loop and play the actual games
    // (it has to be in a thread so that the game loop can wait without 
    // the GUI locking up)
    GThread::runInNewThreadAsync([=](){ this->run(); });
}

/** Outputs the given text onto the GUI. */
void VaderGUI::print(string text) {
    messageLabel->setText(text);
    if (CONSOLE_OUTPUT) {
        cout << text << " ";
    }
    messageLabel->setVisible(true);
}

/** Outputs the given text onto the GUI. */
void VaderGUI::printLine(string text) {
    messageLabel->setText(text);
    if (CONSOLE_OUTPUT) {
        cout << text << endl;
    }
}

/** Waits for the user to press Yes or No and returns the boolean result (
 * true if yes, false if no). */
bool VaderGUI::readBoolean() {
    setWaitingForBoolean(true);
    try {
        bool result = booleanQueue.pop(); 
        
        if (CONSOLE_OUTPUT) {
            cout << (result ? "yes" : "no") << endl;
        }
        return result;
    } catch (exception& e) {
        return false;
    } catch (...) {
        setWaitingForBoolean(false);
    }
    return false;
}

/** Waits for the user to type a line of text and returns that line. */
string VaderGUI::readLine() {
    return readLine("");
}


// private member functions ----------------------------------------------------

// Handles user interactions with the graphical components.
void VaderGUI::actionPerformed(GEvent event) {
    GInteractor* src = event.getInteractor();
    bool actionOccurred = true;
    if (src == yesButton) {
        yes();
    } else if (src == noButton) {
        no();
    } else if (src == inputField) {
        if(event.getKeyChar() == GEvent::KeyCode::ENTER_KEY && event.getEventType() == 33) {
            input();
        } else {
            actionOccurred = false;
        }
    } else if (src == musicBox) {
        // play or stop music
        if (musicClip != nullptr) {
            if (musicBox->isSelected()) {
                musicClip->play();        // TODO: loop!
            } else {
                musicClip->stop();
            }
        }
    } else {
        actionOccurred = false;
    }
    if(actionOccurred) {
        playSound();
    }
}

// turns on/off various graphical components when game events occur. Which 
// get shown and hidden depends on whether the program is currently waiting for 
// the user to click a button or enter text. Also displays current stats. 
void VaderGUI::doEnabling() {
    inputField->setVisible(waitingForString);
    if (waitingForString) {
        inputField->requestFocus();
    }
    yesButton->setVisible(waitingForBoolean);
    noButton->setVisible(waitingForBoolean);
    bannerLabel->setText(BANNER_MESSAGE);
    statsArea->setText(string_format(STATUS_MESSAGE, game->totalGames(), game->gamesWon()));
}

// prints out an error message and returns false if the file doesn't exist, 
// otherwise returns true
bool VaderGUI::ensureFile(string filename) {
    ifstream file(filename);
    if (!file.good()) { 
        cout << "Unable to open file \"" << filename << "\"" << endl;
    }   
    return file.good();
}

// response to pressing Enter on the input text field; completes user input
void VaderGUI::input() {
    try {
        // user pressed Enter on input text field; capture input
        string text = inputField->getText();
        inputField->setText("");
        stringQueue.push(text);
        waitingForString = false;
        doEnabling();
    } catch (exception& e) {
        cout << "exception reading input" << endl;
    }
}

// Responds to mouse clicks with either a yes or no reaction, depending on which 
// one was clicked. Plays a  sound a percentage of the time.
void VaderGUI::keyPressed(GEvent event) {
    if (!yesButton->isVisible() || event.isAltKeyDown() || event.isCtrlKeyDown()) {
        return;
    }
    GInteractor* key = event.getInteractor();
    if (key == yesButton) {
        yes();
    } else if (key == noButton) {
        no();
    }
    playSound();
}

// create one button at specified position/size and adds it to the GUI
GButton* VaderGUI::makeButton(string text, GWindow::Region region) {
    GButton* button = new GButton(text);
    setupComponent(button, region);
    button->setActionListener([=](GEvent event) { this->actionPerformed(event); });
    button->setBackground("#000000");
    button->setVisible(true);
    return button;
}

// create one checkbox at specified position/size and add it to the GUI. If 
// passed true the checkbox will be selected by default when the program loads. 
GCheckBox* VaderGUI::makeCheckBox(string text, bool selected,  GWindow::Region region) {
    GCheckBox* box = new GCheckBox(text, selected);
    setupComponent(box, region);
    box->setActionListener([=](GEvent event) { this->actionPerformed(event); });
    return box;
}

// response to a 'no' button click or typing 'n'
void VaderGUI::no() {
    try {
        booleanQueue.push(false);
        setWaitingForBoolean(false);
    } catch (exception& e) {}
}

// loads and plays/loops the sound/music file with the given file name
// loops the sound/music if passed true (warning: this does not currently work)
GSound* VaderGUI::playAudioClip(string url, bool loop) {
    if (!ensureFile(url)) {
        return nullptr;
    }

    GSound* clip = nullptr;
    try {
        clip = new GSound(url);
        if (loop) {
            clip->play(); // TODO: make it loop
        } else {
            clip->play();
        }
    } catch (exception& e) {
        if (CONSOLE_OUTPUT) {
            cout << "Error: Unable to load audio clip" << endl;
        }
    }
    return clip;
}

// plays the background theme music
void VaderGUI::playMusic() {
    if (musicBox->isSelected()) {
        try {
            if (musicClip == nullptr) {
                int ran = 1 + (int) (rand() / RAND_MAX * NUM_MUSICS);
                if (rand() / RAND_MAX < 0.66) {
                    ran = 1;   // 2/3 chance of picking default empire theme song
                }
                string filename = string_format(MUSIC_FILE_NAME, ran);
                musicClip = playAudioClip(filename, true);
            }
        } catch (exception& e) {
            if (CONSOLE_OUTPUT) {
                cout << e.what() << endl;
            }
        }
    }
}

// randomly picks a mp3 file and plays it
void VaderGUI::playSound() {
    double chance = (1.0 * rand()) / RAND_MAX;
    if (soundBox->isSelected() && chance <= SOUND_PERCENTAGE) {
        int ran = 1 + (int) ((1.0 * rand()) / RAND_MAX * NUM_SOUNDS);
        string filename = string_format(SOUND_FILE_NAME, ran);
        GThread::runInNewThreadAsync([=](){ this->playAudioClip(filename, false); } );
    }
}

// asks a question with the given initial text by displaying it on the interface
// and showing the text box. Waits for the user to enter text in the textbox and
// hit enter
string VaderGUI::readLine(string defaultValue) {
    inputField->setText(defaultValue);
    setWaitingForString(true);
    try {
        // grab/store text from box; clear the box text
        string result = stringQueue.pop(); 
        messageLabel->setText("");

        if (CONSOLE_OUTPUT) {
            cout << result << endl;
        }
        return result;
    } catch (exception& e) {
        return "";
    } catch(...) {
        setWaitingForString(false);
    } 
    return "";
}

// The basic game loop, which will be run in a separate thread. 
void VaderGUI::run() {
    // load audio resources
    playMusic();
    
    // load data
    saveLoad(false);
    
    // play many games
    do {
        if (CONSOLE_OUTPUT) cout << endl;;
        game->play();
        print(PLAY_AGAIN_MESSAGE);
    } while (readBoolean());

    // save data
    saveLoad(true);
    
    // bannerLabel->setVisible(false);
    
    // shut down
    // frame.setVisible(false);
    // frame.dispose();
    // System.exit(0);
}

// common code for asking the user whether they want to save or load
void VaderGUI::saveLoad(bool save) {
    print(save ? SAVE_MESSAGE : LOAD_MESSAGE);
    if (readBoolean()) {
        print(SAVE_LOAD_FILENAME_MESSAGE);
        string filename = readLine(SAVE_DEFAULT_FILE_NAME);
        cout << "\t \t " << filename << endl;
        try {
            if (save) {
                ofstream out (filename);
                game->save(&out);
            } else {
                ifstream in (filename);
                game->load(&in);
            }
        } catch (exception& e) {
            GOptionPane::showMessageDialog(e.what(), "Error Message",
                    GOptionPane::MESSAGE_ERROR);
            if (CONSOLE_OUTPUT) {
                cout << e.what() << endl;
            }
        }
    }
}

// sets standard colors, location and such for the given component and adds it to 
// the interface
void VaderGUI::setupComponent(GInteractor* comp, GWindow::Region region) {
    comp->setForeground(COLOR);
    comp->setColor(COLOR);
    comp->setBackground("black");
    frame->addToRegion(comp, region);
}

// sets the GUI to wait for a yes/no user input
void VaderGUI::setWaitingForBoolean(bool value) {
    waitingForBoolean = value;
    doEnabling();
}

// sets the GUI to wait for a text user input
void VaderGUI::setWaitingForString(bool value) {
    waitingForString = value;
    doEnabling();
}

// response to a 'yes' button click or typing 'y'
void VaderGUI::yes() {
    try {
        booleanQueue.push(true);  
        setWaitingForBoolean(false);
    } catch (exception& e) {}
}

