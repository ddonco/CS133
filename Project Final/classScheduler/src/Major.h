// CS 133 Final Project: Class Scheduler
// Phohanh Tran, Dillon Donohue
// The Major object stores it's name, a catalog of all of the courses, and the courses that are
// required for that major.

#ifndef _Major_h_
#define _Major_h_
#include "CourseCatalog.h"
#include "CourseNode.h"
#include <map>

class Major {
private:
    std::string majorName;
    CourseCatalog *catalog;
    CourseNode *degreeRequirements;

public:
    // Major constructor that takes the major name and a pointer to the course
    // catalog from which the major determines the requires courses for the major
    Major(std::string majorName, CourseCatalog *courseCatalog);

    // prints courses required for the major
    void printCourses() const;

    // return name of the major
    std::string getMajorName() const;

    // returns a pointer to the course catalog containing all majors
    // and courses
    CourseCatalog *getCatalog() const;
};
#endif