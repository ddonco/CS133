// CS 133 Final Project: Class Scheduler
// Phohanh Tran
//
// A student object represents a user and/or past users and stores their information.

#ifndef _Student_h_
#define _Student_h_
#include "CourseNode.h"
#include "Major.h"
#include "WeeklyPlanner.h"
#include <iostream>
#include <set>
#include <vector>

class Student {
private:
    std::string name;
    Major *major;
    std::string strCompleted;
    std::string strEnrolled;

    std::vector<CourseNode *> required;
    std::set<CourseNode *> completed;
    WeeklyPlanner planner;

public:
    // constructor takes strings containing student info, converts to stored versions
    Student(std::string name, Major *major, std::string strCompleted,
            std::string strEnrolled);

    // return true if the student has finished the passed in course
    bool finishedCourse(CourseNode *course) const;

    // adds a course to the planner
    void addCourse(CourseNode *course);

    // removes a course from the planner
    void removeCourse(CourseNode *course);

    // updates an enrolled course to become a completed course
    void completeCourse(CourseNode *course);

    // returns the student's name
    std::string getName() const;

    // returns the student's major
    Major *getMajor() const;

    // returns courses the student has completed
    std::set<CourseNode *> getCompleted() const;

    // returns student's weekly class schedule
    WeeklyPlanner getPlanner() const;

    // prints courses the student has completed
    void printCompleted() const;

    // prints student's weekly class schedule
    void printEnrolled() const;

    // prints required courses that have not been completed yet
    void printRequired();
};
#endif