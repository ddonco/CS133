// CS 133 Final Project: Class Scheduler
// Phohanh Tran
//
// A student object represents a user and/or past users and stores their information.

#include "Student.h"

// constructor takes strings containing student info, converts to stored versions
Student::Student(std::string name, Major *major, std::string strCompleted,
                 std::string strEnrolled) : name(name), major(major), strCompleted(strCompleted),
                                            strEnrolled(strEnrolled) {
    CourseCatalog *catalog = major->getCatalog();

    std::string token;
    // initializes Weeklyplanner with enrolled courses
    std::istringstream issEnrolled(strEnrolled);
    while (std::getline(issEnrolled, token, ' ')) {
        CourseNode *course = catalog->getCourse(token);
        if (course != nullptr) {
            course->decrementOpenSeats();
            planner.addCourse(course);
        } else {
            std::cout << "Course '" << token << "' not found in course catalog, skipped!" << std::endl;
        }
    }
    // initializes set of completed courses
    std::istringstream issCompleted(strCompleted);
    while (std::getline(issCompleted, token, ' ')) {
        CourseNode *course = catalog->getCourse(token);
        if (course != nullptr) {
            completed.insert(course);
        } else {
            std::cout << "Course '" << token << "' not found in course catalog, skipped!" << std::endl;
        }
    }

    // if the user has not taken a course, it is added to their specific requirements
    CourseNode *majorRequirements = catalog->getMajorCourseList(major->getMajorName());
    CourseNode *curr = majorRequirements;
    while (curr != nullptr) {
        if (completed.find(curr) == completed.end()) {
            required.push_back(curr);
        }
        curr = curr->next;
    }
}

// return true if the student has finished the passed in course
bool Student::finishedCourse(CourseNode *course) const {
    return completed.find(course) != completed.end() || course == nullptr;
}

// adds a course to the planner
void Student::addCourse(CourseNode *course) {
    planner.addCourse(course);
}

// removes a course from the planner
void Student::removeCourse(CourseNode *course) {
    planner.removeCourse(course);
}

// updates an enrolled course to become a completed course
void Student::completeCourse(CourseNode *course) {
    planner.removeCourse(course);
    completed.insert(course);
}

// returns the student's name
std::string Student::getName() const {
    return name;
}

// returns the student's major
Major *Student::getMajor() const {
    return major;
}

// returns courses the student has completed
std::set<CourseNode *> Student::getCompleted() const {
    return completed;
}

// returns student's weekly class schedule
WeeklyPlanner Student::getPlanner() const {
    return planner;
}

// prints courses the student has completed
void Student::printCompleted() const {
    std::cout << "You have completed: " << std::endl;
    for (CourseNode *course : completed) {
        std::cout << course->getCourseName() << std::endl;
    }
    std::cout << std::endl;
}

// prints student's weekly class schedule
void Student::printEnrolled() const {
    planner.printPlanner();
}

// prints required courses that have not been completed yet
void Student::printRequired() {
    std::cout << "You have yet to complete: " << std::endl;
    for (CourseNode *course : required) {
        std::cout << course->getCourseName() << std::endl;
    }
    std::cout << std::endl;
}
