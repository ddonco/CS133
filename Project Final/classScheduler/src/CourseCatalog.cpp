// CS 133 Final Project: Class Scheduler
// Dillon Donohue, Phohanh Tran
// The CourseCatalog object stores a map of all courses required for each major.

#include "CourseCatalog.h"
#include "Utilities.h"

CourseCatalog::CourseCatalog(std::string fileName) {
    std::ifstream input;
    input.open(fileName);
    std::string line;
    while (std::getline(input, line)) {
        CourseNode *majorList = nullptr;
        std::istringstream iss(line);
        std::string major;
        std::string courseDetails;
        iss >> major;
        while (iss >> courseDetails) {
            std::vector<std::string> details = parseDelimitedLine(courseDetails, ';', 4);
            std::string courseName = details[0];
            std::string startTime = details[1];
            std::string timeLength = details[2];
            std::string days = details[3];
            std::set<WEEKDAYS> daysOfWeek = parseDelimitedDays(days, ',');
            CourseNode *course = new CourseNode(courseName,
                                                stoi(startTime),
                                                stoi(timeLength),
                                                daysOfWeek);
            push_back(majorList, course);
        }
        allCourses[major] = majorList;
    }
    input.close();
}

// returns the list of courses required of a major
CourseNode *CourseCatalog::getMajorCourseList(std::string major) {
    return allCourses.at(major);
}

// returns the course object with the passed in course code and changes the passed in
// major object to the major that course is in
CourseNode *CourseCatalog::getCourse(std::string courseCode) {
    for (const auto &[major, course] : allCourses) {
        CourseNode *current = allCourses.at(major);
        while (current != nullptr) {
            if (current->getCourseName() == courseCode) {
                return current;
            }
            current = current->next;
        }
    }
    return nullptr;
}

// returns the department of the input course
std::string CourseCatalog::getCourseDep(std::string courseCode) {
    for (const auto &[major, course] : allCourses) {
        CourseNode *current = allCourses.at(major);
        while (current != nullptr) {
            if (current->getCourseName() == courseCode) {
                return major;
            }
            current = current->next;
        }
    }
    return std::string("");
}

// returns the course object that is a prerequesite for the course of the passed
// in course code. if it can't be found, returns nullptr
CourseNode *CourseCatalog::getPrereq(std::string courseCode) {
    CourseNode *course = getCourse(courseCode);
    CourseNode *curr = allCourses[getCourseDep(courseCode)];
    while (curr->next != nullptr) {
        if (curr->next == course) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

// adds a course to the end of the list of available courses
void CourseCatalog::push_back(CourseNode *&courseList, CourseNode *course) {
    CourseNode *current = courseList;
    if (courseList == nullptr) {
        courseList = course;
    } else {
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = course;
    }
}

// prints all the courses available at the school with the major they are required for
void CourseCatalog::printAll() const {
    for (const auto &[major, course] : allCourses) {
        std::cout << major << ":" << std::endl;
        std::cout << "------------------------------" << std::endl;
        CourseNode *current = course;
        while (current->next != nullptr) {
            current->print();
            current = current->next;
            std::cout << "~~~~~~~~~~" << std::endl;
        }
    }
    std::cout << std::endl;
}

// returns a vector with the names of all the majors available to students
std::vector<std::string> CourseCatalog::getMajors() {
    std::vector<std::string> majors;
    for (const auto [major, courses] : allCourses) {
        majors.push_back(major);
    }
    return majors;
}