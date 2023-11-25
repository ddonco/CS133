#include "TagManager.h"

TagManager::TagManager(vector<string> names) {
    if (names.size() == 0) {
        throw string("vector cannot have zero length");
    }

    tagRing = new TagNode(names[0]);
    TagNode *tn = tagRing;
    for (int i = 1; i < names.size(); i++) {
        TagNode *temp = new TagNode(names[i], nullptr);
        tn->next = temp;
        tn = tn->next;
    }
}

void TagManager::printTagRing() {
    TagNode *tn = tagRing;
    while (tn != nullptr) {
        cout << tn->name << "is trying to tag ";
        if (tn->next == nullptr) {
            cout << tagRing->name;
        } else {
            cout << tn->next->name;
        }
        cout << endl;
        tn = tn->next;
    }
}

void TagManager::printOutList() {
}

bool TagManager::tagRingContains(string name) {
    return false;
}

bool TagManager::outListContains(string name) {
    return false;
}

bool TagManager::isGameOver() {
    if (tagRing->next == nullptr) {
        return true;
    }
    return false;
}

string TagManager::winner() {
    if (tagRing->next == nullptr) {
        return tagRing->name;
    }
    return "";
}

void TagManager::tag(string name) {
}