#ifndef _TAGMANAGER_H
#define _TAGMANAGER_H

#include <iostream>
#include <string>
#include <vector>

#include "TagNode.h"

using namespace std;

class TagManager {
public:
    TagManager(vector<string> names);
    void printTagRing();
    void printOutList();
    bool tagRingContains(string name);
    bool outListContains(string name);
    bool isGameOver();
    string winner();
    void tag(string name);

private:
    TagNode *tagRing;
    TagNode *outList;
};

#endif