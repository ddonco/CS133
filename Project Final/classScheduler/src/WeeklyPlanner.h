// CS 133 Final Project: Class Scheduler
// Dillon Donohue
// WeeklyPlanner object stores a list of the student's enrolled classes, representing their
// weekly classes.

#ifndef _WeeklyPlanner_h_
#define _WeeklyPlanner_h_
#include <map>
#include <set>
#include <vector>

#include "CourseNode.h"
#include "TimeSlot.h"
#include "Utilities.h"

class WeeklyPlanner {
private:
    std::map<WEEKDAYS, TimeSlot *> planner;

public:
    // Class constructor
    WeeklyPlanner();

    // adds course timeslots in order of meet times
    void addCourseHelper(CourseNode *course, TimeSlot *&ts);

    // adds course to the planner
    void addCourse(CourseNode *course);

    // removes the passed in course from the planner
    void removeCourse(CourseNode *course);

    // returns a set of all the courses stored in the planner
    std::set<CourseNode *> getCoursesInPlanner();

    // checks whether or not the passed in course is already in the planner, return true
    // if course is in planner, returns false otherwise
    bool isCourseInPlanner(CourseNode *course);

    // checks all the occupied timeslots in the planner to see if the passed in times overlap
    bool isOpenHelper(int startTime, int endTime, TimeSlot *ts) const;

    // returns true if the passed in times on the passed in days are unoccupied in the planner, else
    // returns false
    bool timeIsOpen(std::set<WEEKDAYS> daysOfWeek, int startTime, int endTime) const;

    // prints the classes and their meeting times of each day
    void printPlanner() const;
};
#endif