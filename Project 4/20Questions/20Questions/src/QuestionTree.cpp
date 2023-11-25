/*
Dillon Donohue, CS 133, Spring 2023
Programming Assignment #4, 05/15/23

QuestionTree implements the functions needed to play a game of 20 questions with the
computer as the opponent. The computer will repeatedly ask the client questions
until either the computer wins by guessing the correct answer or it fails to find
the right answer and looses. If the computer looses, it will ask the client for
the answer, it will ask for a question that would help identify the answer, and
it will ask for the yes/no answer to the question that will lead to the answer.
Additionally QuestionTree provides functionality to save a game, load a game and
get some simple stats on the games played in a session.
*/

#include "QuestionTree.h"

QuestionTree::QuestionTree(UserInterface *ui) : ui(ui), root(nullptr), _totalGames(0), _gamesWon(0) {}

QuestionTree::~QuestionTree() {
    delete root;
}

void QuestionTree::deleteTree(QuestionNode *node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int QuestionTree::totalGames() {
    return _totalGames;
}

int QuestionTree::gamesWon() {
    return _gamesWon;
}

void QuestionTree::save(ostream *output) {
    save(output, root);
}

void QuestionTree::save(ostream *output, QuestionNode *node) {
    if (node != nullptr) {
        *output << node->type << ":" << node->data << endl;
        save(output, node->left);
        save(output, node->right);
    }
}

void QuestionTree::load(istream *input) {
    if (input->good()) {
        load(input, root);
    }
}

void QuestionTree::load(istream *input, QuestionNode *&node) {
    string line;
    if (getline(*input, line)) {
        char type = *(line.substr(0, 1).c_str());
        string data = line.substr(2);
        node = new QuestionNode(type, data);
        if (node->type == 'Q') {
            load(input, node->left);
            load(input, node->right);
        }
    }
}

bool QuestionTree::askYesNoQuestion(string question, string var) {
    ui->printLine(question + var);
    return ui->readBoolean();
}

string QuestionTree::askOpenQuestion(string question, string var) {
    ui->printLine(question + var);
    return ui->readLine();
}

void QuestionTree::play() {
    _totalGames++;
    if (root == nullptr) {
        root = new QuestionNode('A', "computer");
    }
    play(root);
}

void QuestionTree::play(QuestionNode *&node) {
    bool isYes;
    // If the current node is a question node, type is 'A', make a guess at the
    // answer. If the answer is not correct, as the client for the answer and
    // a new question.
    if (node->type == 'A') {
        isYes = askYesNoQuestion(GUESS_MESSAGE, node->data + "? ");
        if (isYes) {
            // Guessed answer is correct.
            _gamesWon++;
            ui->printLine("I win!");
        } else {
            // Guessed answer is wrong. Get the answer to make a new QuestionNode leaf,
            // get a new question to make a new QuestionNode internal node, and move
            // existing answer node to be a leaf of the new question node.
            string newObj = askOpenQuestion(ASK_OBJECT_MESSAGE, "");
            string newQuest = askOpenQuestion(GET_QUESTION_MESSAGE, node->data + ": ");
            isYes = askYesNoQuestion(GET_ANSWER_MESSAGE, "");
            QuestionNode *moveNode = node;
            QuestionNode *newQuestNode = new QuestionNode('Q', newQuest);
            QuestionNode *newAnsNode = new QuestionNode('A', newObj);
            node = newQuestNode;
            if (isYes) {
                // If the response to the question is 'yes' the new answer node goes to
                // the left of the question node and the previos answer node goes to the
                // right.
                node->left = newAnsNode;
                node->right = moveNode;
            } else {
                // If the response to the question is 'no' the previos answer node goes
                // to the left of the question node and the new answer node goes to the
                // right.
                node->left = moveNode;
                node->right = newAnsNode;
            }
        }
    } else {
        // If the current node is a question node, type is not 'A', ask the
        // question and use the response to move left or right.
        isYes = askYesNoQuestion(node->data, " ");
        if (isYes) {
            play(node->left);
        } else {
            play(node->right);
        }
    }
}
