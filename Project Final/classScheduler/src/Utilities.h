// CS 133 Final Project: Class Scheduler
// Dillon Donohue
// Utility enums and functions.

#ifndef _UTILITIES_h_
#define _UTILITIES_h_
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// enum of days of the week
// cast int to enum value: static_cast<WEEKDAYS>(1) => monday
enum WEEKDAYS {
    monday = 1,
    tuesday,
    wednesday,
    thursday,
    friday
};

// get a string representation for a given WEEKDAYS enum value
std::string weekdaysToString(WEEKDAYS day);

// parses a delimited string based on the passed in delimiter character and returns
// the delimited string values in a vector, the expected count of values can be
// specified or 0 can be passed in to expected if there is no expected count
std::vector<std::string> parseDelimitedLine(const std::string line, char delimiter, int expected);

// parses a delimited string of weekday codes and returns a set of WEEKDAYs,
// weekday codes must correspond to WEEKDAY enum values (1 - 5)
std::set<WEEKDAYS> parseDelimitedDays(const std::string str, char delimiter);

// returns an integer time in 24hr string format
std::string intTimeToString(int time);

#endif