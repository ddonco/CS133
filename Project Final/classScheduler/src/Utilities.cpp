// CS 133 Final Project: Class Scheduler
// Dillon Donohue
// Utility enums and functions.

#include "Utilities.h"

// get a string representation for a given WEEKDAYS enum value
std::string weekdaysToString(WEEKDAYS day) {
    if (day == monday) {
        return "Monday";
    } else if (day == tuesday) {
        return "Tuesday";
    } else if (day == wednesday) {
        return "Wednesday";
    } else if (day == thursday) {
        return "Thursday";
    } else if (day == friday) {
        return "Friday";
    } else {
        return "unknown";
    }
}

// parses a delimited string based on the passed in delimiter character and returns
// the delimited string values in a vector, the expected count of values can be
// specified or 0 can be passed in to expected if there is no expected count
std::vector<std::string> parseDelimitedLine(const std::string line, char delimiter, int expected) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    if (expected > 0) {
        for (int i = 0; i < expected - tokens.size(); i++) {
            tokens.push_back("");
        }
    }
    return tokens;
}

// parses a delimited string of weekday codes and returns a set of WEEKDAYs,
// weekday codes must correspond to WEEKDAY enum values (1 - 5)
std::set<WEEKDAYS> parseDelimitedDays(const std::string str, char delimiter) {
    std::vector<std::string> dayCodes = parseDelimitedLine(str, delimiter, 0);
    std::set<WEEKDAYS> days;
    for (std::string s : dayCodes) {
        int d = stoi(s);
        days.insert(static_cast<WEEKDAYS>(d));
    }
    return days;
}

// returns an integer time in 24hr string format
std::string intTimeToString(int time) {
    std::ostringstream oss;
    oss << time << ":00";
    return oss.str();
}