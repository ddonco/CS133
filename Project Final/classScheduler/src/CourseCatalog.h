// CS 133 Final Project: Class Scheduler
// Dillon Donohue, Phohanh Tran
// The CourseCatalog object stores a map of all courses required for each major.

#ifndef _CourseCatalog_h_
#define _CourseCatalog_h_
#include "CourseNode.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

class CourseCatalog {
private:
    // Stores department names and pointers to the first CourseNode for the course list of
    // each department
    std::map<std::string, CourseNode *> allCourses;

    // adds a course to the end of the list of available courses
    void push_back(CourseNode *&courseList, CourseNode *course);

public:
    // the course catalog constructor takes a file name to a saved course catalog, it then parses
    // the course data and all courses by major
    CourseCatalog(std::string fileName);

    // returns the list of courses required of a major
    CourseNode *getMajorCourseList(std::string major);

    // returns the course object with the passed in course code and changes the passed in
    // major object to the major that course is in
    CourseNode *getCourse(std::string courseCode);

    // returns the department of the input course
    std::string getCourseDep(std::string courseCode);

    // returns the course object that is a prerequesite for the course of the passed
    // in course code
    CourseNode *getPrereq(std::string courseCode);

    // prints all the courses available at the school with the major they are required for
    void printAll() const;

    // returns a vector with the names of all the majors available to students
    std::vector<std::string> getMajors();
};
#endif