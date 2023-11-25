// CS 133 Final Project: Class Scheduler
// Phohanh Tran, Dillon Donohue
// The Major object stores it's name, a catalog of all of the courses, and the courses that are
// required for that major.

#include "Major.h"

// Major constructor that takes the major name and a pointer to the course
// catalog from which the major determines the requires courses for the major
Major::Major(std::string majorName, CourseCatalog *courseCatalog) : majorName(majorName),
                                                                    catalog(courseCatalog) {
    degreeRequirements = catalog->getMajorCourseList(majorName);
}

// prints courses required for the major
void Major::printCourses() const {
    CourseNode *current = degreeRequirements;
    while (current->next != nullptr) {
        current->print();
        current = current->next;
    }
}

// returns the name of the major
std::string Major::getMajorName() const {
    return majorName;
}

// returns a pointer to the course catalog containing all majors
// and courses
CourseCatalog *Major::getCatalog() const {
    return catalog;
}