// CS 133 Final Project: Class Scheduler
// Dillon Donohue, Tony Do, Phohanh Tran
// The CourseNode object contains all course information, including number of total seats,
// open seats, number of people in the waitList, how long each class is, time the class starts,
// the days there is class, the name of the course, and the next course (if there is one).

#include "CourseNode.h"
#include "CourseCatalog.h"

// course node constuctor that takes the course name, start time, class time length,
// and days of week, it sets the next class to a nullptr
CourseNode::CourseNode(std::string courseName,
                       int startTime,
                       int timeLength,
                       std::set<WEEKDAYS> daysOfWeek) : CourseNode(courseName, startTime, timeLength, daysOfWeek, nullptr) {}

// course node constuctor that takes the course name, start time, class time length,
// days of week, and a pointer to the next class in the linked list series of classes
CourseNode::CourseNode(std::string courseName,
                       int startTime,
                       int timeLength,
                       std::set<WEEKDAYS> daysOfWeek,
                       CourseNode *next) : courseName(courseName),
                                           startTime(startTime),
                                           classTimeLength(timeLength),
                                           daysOfWeek(daysOfWeek),
                                           next(next) {

    this->openSeats = CLASS_CAPACITY;
    this->waitList = 0;
}

// return the name of the course
std::string CourseNode::getCourseName() const {
    return courseName;
}

// returns the start time of the course
int CourseNode::getStartTime() const {
    return startTime;
}

// returns the time length of the course in hours
int CourseNode::getTimeLength() const {
    return classTimeLength;
}

// returns a set of WEEKDAYS enums represeting the days of the week the class
// is held
std::set<WEEKDAYS> CourseNode::getDaysOfWeek() const {
    return daysOfWeek;
}

// returns the number of open seats in the class
int CourseNode::getOpenSeats() const {
    return openSeats;
}

// returns the wait list count of the class
int CourseNode::getWaitList() const {
    return waitList;
}

// increase the number of open seats by one so long as the number of open seats
// is less than or equal to the total seats
void CourseNode::incrementOpenSeats() {
    if (openSeats < CLASS_CAPACITY) {
        openSeats++;
    } else {
        incrementWaitlist();
    }
}

// decrease the number of open seats by one so long as the number of open seats is
// greater than or equal to 0
void CourseNode::decrementOpenSeats() {
    if (waitList > 0) {
        waitList--;
    } else if (openSeats > 0) {
        openSeats--;
    }
}

// increase the number of waitlist spots by one so long as the number of spots
// is less than or equal to the total spots
void CourseNode::incrementWaitlist() {
    if (waitList < WAITLIST_CAPACITY) {
        waitList++;
    } else {
        std::cout << "This class and it's waitlist are at capacity." << std::endl;
    }
}

// decrease the number of waitlist spots by one so long as the number of spots is
// greater than or equal to 0
void CourseNode::decrementWaitlist() {
    if (waitList > 0) {
        waitList--;
    }
}

// prints all course info
void CourseNode::print() {
    std::cout << courseName << ": Open seats " << openSeats << "/" << CLASS_CAPACITY << std::endl;
    std::cout << "Wait list: " << waitList << "/" << WAITLIST_CAPACITY << std::endl;
    std::cout << "start time: " << intTimeToString(startTime);
    std::cout << " to " << intTimeToString(startTime + classTimeLength) << std::endl;
    std::cout << "Meeting days: ";
    int size = 0;
    for (auto days : daysOfWeek) {
        size++;
        std::cout << weekdaysToString(days);
        if (size < daysOfWeek.size()) {
            std::cout << ", ";
        } else {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

// outputs an ostream object with the course name
std::ostream &CourseNode::operator<<(std::ostream &out) {
    out << courseName;
    return out;
}