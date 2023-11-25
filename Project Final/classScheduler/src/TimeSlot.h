// CS 133 Final Project: Class Scheduler
// Dillon Donohue, Tony Do
// The TimeSlot object stores the start and end time of the input course.

#ifndef _TIMESLOT_H_
#define _TIMESLOT_H_
#include "CourseNode.h"

// TimeSlot represents a time slot in a course schedule and can be used in a
// linked list fasion by assigning next to another TimeSlot instance
struct TimeSlot {
    CourseNode *course;
    int startTime;
    int endTime;
    TimeSlot *next;

    // TimeSlot constructor takes a pointer to a course from which it assigns
    // the start time and end time of the time slot, next is set to a nullptr
    TimeSlot(CourseNode *course) : course(course), next(nullptr) {
        startTime = course->getStartTime();
        endTime = startTime + course->getTimeLength();
    }
};

#endif