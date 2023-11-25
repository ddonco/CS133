// CS 133 Final Project: Class Scheduler
// Dillon Donohue, Tony Do, Phohanh Tran
// The CourseNode object contains all course information, including number of total seats,
// open seats, number of people in the waitList, how long each class is, time the class starts,
// the days there is class, the name of the course, and the next course (if there is one).

#ifndef _CourseNode_h_
#define _CourseNode_h_
#include "Utilities.h"
#include <iostream>
#include <set>
#include <string>

const int CLASS_CAPACITY = 30;
const int WAITLIST_CAPACITY = 10;

class CourseNode {
private:
    std::string courseName;
    int startTime;
    int classTimeLength;
    std::set<WEEKDAYS> daysOfWeek;
    int openSeats;
    int waitList;

public:
    // pointer to next course node in a linked list of course nodes
    CourseNode *next;

    // course node constuctor that takes the course name, start time, class time length,
    // days of week, and a pointer to the next class in the linked list series of classes
    CourseNode(std::string course,
               int startTime,
               int timeLength,
               std::set<WEEKDAYS> daysOfWeek,
               CourseNode *next);

    // course node constuctor that takes the course name, start time, class time length,
    // and days of week, it sets the next class to a nullptr
    CourseNode(std::string courseName,
               int startTime,
               int timeLength,
               std::set<WEEKDAYS> daysOfWeek);

    // return the name of the course
    std::string getCourseName() const;

    // returns the start time of the course
    int getStartTime() const;

    // returns the time length of the course in hours
    int getTimeLength() const;

    // returns a set of WEEKDAYS enums represeting the days of the week the class
    // is held
    std::set<WEEKDAYS> getDaysOfWeek() const;

    // returns the number of open seats in the class
    int getOpenSeats() const;

    // returns the wait list count of the class
    int getWaitList() const;

    // increase the number of open seats by one so long as the number of open seats
    // is less than or equal to the total seats
    void incrementOpenSeats();

    // decrease the number of open seats by one so long as the number of open seats is
    // greater than or equal to 0
    void decrementOpenSeats();

    // increase the number of waitlist spots by one so long as the number of spots
    // is less than or equal to the total spots
    void incrementWaitlist();

    // decrease the number of waitlist spots by one so long as the number of spots is
    // greater than or equal to 0
    void decrementWaitlist();

    // prints all course info
    void print();

    // outputs an ostream object with the course name
    std::ostream &operator<<(std::ostream &out);
};
#endif