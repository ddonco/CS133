// CS 133 Final Project: Class Scheduler
// Dillon Donohue
// WeeklyPlanner object stores a list of the student's enrolled classes, representing their
// weekly classes.

#include "WeeklyPlanner.h"

WeeklyPlanner::WeeklyPlanner() : planner{} {
    // makes each day of the planner empty
    for (int i = monday; i <= friday; i++) {
        planner[static_cast<WEEKDAYS>(i)] = nullptr;
    }
}

// adds course timeslots in order of meet times
void WeeklyPlanner::addCourseHelper(CourseNode *course, TimeSlot *&ts) {
    if (ts == nullptr) {
        // Adds new TimeSlot if there are no time slots.
        ts = new TimeSlot(course);
    } else if (course->getStartTime() >= ts->endTime && ts->next == nullptr) {
        // Adds new TimeSlot at the end if course time is greater than all existing time slots.
        ts->next = new TimeSlot(course);
    } else if (course->getStartTime() < ts->startTime) {
        // Adds new TimeSlot at the beginning if course time is less than first time slot.
        TimeSlot *temp = ts;
        ts = new TimeSlot(course);
        ts->next = temp;
    } else if (course->getStartTime() >= ts->endTime &&
               (course->getStartTime() + course->getTimeLength()) <= ts->next->startTime) {
        // Adds new TimeSlot in between current time slot and next time slot if the course start
        // time is >= end of the current time slot and course end time is <= start of the
        // next time slot.
        TimeSlot *temp = ts->next;
        ts->next = new TimeSlot(course);
        ts->next->next = temp;
    } else {
        // If course start is greater than current time slot end and course end is greater
        // than next time slot start, move to next time slot.
        addCourseHelper(course, ts->next);
    }
}

// adds course to the planner
void WeeklyPlanner::addCourse(CourseNode *course) {
    if (!isCourseInPlanner(course)) {
        // Check if day and time is open.
        int endTime = course->getStartTime() + course->getTimeLength();
        if (timeIsOpen(course->getDaysOfWeek(), course->getStartTime(), endTime)) {
            // Add to planner.
            for (WEEKDAYS day : course->getDaysOfWeek()) {
                addCourseHelper(course, planner[day]);
            }
        } else {
            std::cout << "Time slot of selected course to add is already occupied!" << std::endl;
        }
    } else {
        std::cout << "Selected course to add is already in planner!" << std::endl;
    }
}

// removes the passed in course from the planner
void WeeklyPlanner::removeCourse(CourseNode *course) {
    if (isCourseInPlanner(course)) {
        // loop through each day in the planner to find time slots for the given course
        for (auto &[day, ts] : planner) {
            if (ts != nullptr) { // if the first time slot contains the course, remove it
                if (ts->course == course) {
                    TimeSlot *trash = ts;
                    ts = ts->next;
                    delete trash;
                } else { // loop through the time slot linked list to find and remove course
                    TimeSlot *curr = ts;
                    TimeSlot *prev = ts;
                    while (curr->next != nullptr && curr->course != course) {
                        prev = curr;
                        curr = curr->next;
                    }
                    TimeSlot *trash = curr;
                    prev->next = curr->next;
                    delete trash;
                }
            }
        }
    } else {
        std::cout << "Selected course to remove is not in planner!" << std::endl;
    }
}

// returns a set of all the courses stored in the planner
std::set<CourseNode *> WeeklyPlanner::getCoursesInPlanner() {
    std::set<CourseNode *> courses;
    for (auto &[day, time] : planner) {
        TimeSlot *curr = time;
        while (curr != nullptr) {
            courses.insert(curr->course);
            curr = curr->next;
        }
    }
    return courses;
}

// checks whether or not the passed in course is already in the planner, return true
// if course is in planner, returns false otherwise
bool WeeklyPlanner::isCourseInPlanner(CourseNode *course) {
    std::set<CourseNode *> enrolled = getCoursesInPlanner();
    return enrolled.find(course) != enrolled.end();
}

// checks all the occupied timeslots in the planner to see if the passed in times overlap
bool WeeklyPlanner::isOpenHelper(int startTime, int endTime, TimeSlot *ts) const {
    if (ts == nullptr) {
        return true;
    } else if ((startTime >= ts->startTime && startTime < ts->endTime) ||
               (endTime > ts->startTime && endTime <= ts->endTime) ||
               (startTime <= ts->startTime && endTime >= ts->endTime)) {
        return false;
    } else {
        return isOpenHelper(startTime, endTime, ts->next);
    }
}

// returns true if the passed in times on the passed in days are unoccupied in the planner, else
// returns false
bool WeeklyPlanner::timeIsOpen(std::set<WEEKDAYS> daysOfWeek, int startTime, int endTime) const {
    bool isOpen = true;
    for (WEEKDAYS courseDay : daysOfWeek) {
        isOpen = isOpenHelper(startTime, endTime, planner.at(courseDay));
    }
    return isOpen;
}

// prints the classes and their meeting times of each day
void WeeklyPlanner::printPlanner() const {
    std::cout << "Weekly Course Schedule" << std::endl;
    for (const auto &[day, time] : planner) {
        std::cout << weekdaysToString(day) << ": " << std::endl;
        TimeSlot *curr = time;
        while (curr != nullptr) {
            std::cout << "\t" << curr->course->getCourseName() << " "
                      << intTimeToString(curr->startTime) << " to "
                      << intTimeToString(curr->endTime) << ", " << std::endl;
            curr = curr->next;
        }
    }
    std::cout << std::endl;
}