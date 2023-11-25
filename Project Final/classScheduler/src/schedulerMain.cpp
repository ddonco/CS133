// CS 133 Final Project: Class Scheduler
// Alora, Tony Do, Phohanh Tran, Dillon Donohue

// This program is a class scheduler meant for all students at a community college.
// Students add themselves to the console by adding their name, student ID, and major.
// Students are all able to view the classes required for their major and can query
// the next class they must take to complete their major. Students can enroll in classes
// they have completed the prerequesites for by adding them to their planner. If they have time
// conflicts with a class they are trying to enroll in, and one that is already in their
// schedule, the student won't be able to enroll. If a student either drops a class or finishes,
// it will be removed from their planner.
// Students can add themselves to the waitlist of full classes, which will allow them to enter
// the class depending on the professor, and whether other students decide to drop the class.

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "CourseCatalog.h"
#include "CourseNode.h"
#include "Major.h"
#include "Student.h"
#include "Utilities.h"
#include "WeeklyPlanner.h"

// Outputs introduction message for user giving instructions for user input.
void intro() {
    std::cout << "Welcome to the class scheduler!" << std::endl;
    std::cout << "This application allows students to add or remove themselves" << std::endl;
    std::cout << "from the school as well as manage their course enrollments." << std::endl;
    std::cout << "Please follow the prompts to start the application and" << std::endl;
    std::cout << "take actions to update class schedules." << std::endl;
    std::cout << std::endl;
}

// checks if the input string is composed of number characters
bool isNumber(std::string number) {
    for (int i = 0; i < number.size(); i++) {
        if (!isdigit(number[i])) {
            return false;
        }
    }
    return true;
}

// gets a string user input (ie. for file names)
std::string getUserInput() {
    std::string userInput;
    std::getline(std::cin, userInput);
    return userInput;
}

// takes user input and returns the first character, lower cased if it is a letter
char getUserActionChar(std::string prompt) {
    std::cout << prompt << " ";
    std::string userInput = getUserInput();
    std::cout << std::endl;
    return tolower(userInput[0]);
}

// Prompts the user for a file name with the passed in prompt text.
// Checks to make sure the file exists. If it doesn't, prompts the user for
// a new file until they input a valid one and returns it.
// always returns a file that exists.
std::string getFileName(std::string prompt) {
    std::cout << prompt << " ";
    std::string fileName = getUserInput();
    // try opening the file to make sure it exists and we can access it
    std::ifstream input;
    input.open(fileName);
    // keep prompting for a new file until we get one we can access
    while (!input.good()) {
        std::cout << "Invalid file or file faled to open. Re-enter file name? ";
        fileName = getUserInput();
        input.open(fileName);
    }
    input.close();
    return fileName;
}

// prints the main actions a user can do to save changes
void saveActions() {
    std::cout << "Save actions:" << std::endl;
    std::cout << "1) Save in same file." << std::endl;
    std::cout << "2) Save in new file." << std::endl;
    std::cout << "3) Don't save." << std::endl;
}

// << override to transfer the contents of the input set to a stream
template <typename T>
std::ostream &operator<<(std::ostream &out, std::set<T> set) {
    for (T obj : set) {
        out << obj;
    }
    return out;
}

// builds a space delimited string of course names from a set of pointers to courses
std::string coursesToString(std::set<CourseNode *> courses) {
    std::ostringstream oss;
    int delimCount = 1;
    for (const CourseNode *course : courses) {
        oss << course->getCourseName();
        if (delimCount < courses.size()) {
            oss << " ";
        }
        delimCount++;
    }
    return oss.str();
}

// saves the contents of the school into the file with the input file name
void saveUsers(const std::string fileName, const std::map<int, Student *> &school) {
    if (!fileName.empty()) {
        std::ofstream outFile;
        outFile.open(fileName);
        for (const auto [id, student] : school) {
            outFile << student->getName() << ';' << id << ';' << student->getMajor()->getMajorName() << ';';

            std::set<CourseNode *> completed = student->getCompleted();
            outFile << coursesToString(completed) << ';';

            WeeklyPlanner stuPlanner = student->getPlanner();
            std::set<CourseNode *> planner = stuPlanner.getCoursesInPlanner();
            outFile << coursesToString(planner) << std::endl;
        }
        outFile.close();
    }
}

// takes the student id of a user
int getStudentId() {
    std::cout << "Student ID? ";
    std::string strId;
    std::getline(std::cin, strId);
    while (!isNumber(strId)) {
        std::cout << "ID should only contain numbers: ";
        std::getline(std::cin, strId);
    }
    return stoi(strId);
}

// prints the actions the user can do in relation to their personal courses,
// and major requirements
void printEnrollmentAction() {
    std::cout << "Student enrollment actions:" << std::endl;
    std::cout << "1) View your completed courses." << std::endl;
    std::cout << "2) View courses you still need to complete." << std::endl;
    std::cout << "3) View your enrollment planner." << std::endl;
    std::cout << "4) Add class to planner." << std::endl;
    std::cout << "5) Mark class completed." << std::endl;
    std::cout << "6) Remove class from planner." << std::endl;
    std::cout << "Q)uit" << std::endl;
}

// prompts the user to what to do
void handleEnrollmentAction(const int id, std::map<int, Student *> &school, CourseCatalog *catalog) {
    std::cout << "Welcome " << school.at(id)->getName() << "!" << std::endl;
    char command = 'i';
    while (command != 'q') {
        printEnrollmentAction();
        command = getUserActionChar("What would you like to do?");
        if (command == '1') { // view completed courses
            school.at(id)->printCompleted();
        } else if (command == '2') { // view courses courses that need to be completed
            school.at(id)->printRequired();
        } else if (command == '3') { // view student planner
            school.at(id)->printEnrolled();
        } else if (command == '4') { // add class to planner
            std::cout << "Enter course code of course to be added: ";
            std::string courseCode = getUserInput();

            CourseNode *course = catalog->getCourse(courseCode);
            if (course != nullptr) {
                CourseNode *prereq = catalog->getPrereq(courseCode);
                bool finPrereq = school.at(id)->finishedCourse(prereq);

                if (finPrereq) {
                    // remove open seat becasue student is added to class
                    course->decrementOpenSeats();
                    school.at(id)->addCourse(course);
                } else {
                    std::cout << "You haven't finished the prerequesites for this course yet."
                              << std::endl;
                }
            } else {
                std::cout << "Course code doesn't exist in course catalog." << std::endl;
            }
            std::cout << std::endl;
        } else if (command == '5') {
            std::cout << "Enter course code of completed course: ";
            std::string courseCode = getUserInput();
            CourseNode *course = catalog->getCourse(courseCode);
            // add open seat back to class
            course->incrementOpenSeats();
            school.at(id)->completeCourse(course);
            std::cout << std::endl;
        } else if (command == '6') { // remove class from planner
            std::cout << "Enter course code of course to be removed: ";
            std::string courseCode = getUserInput();

            CourseNode *course = catalog->getCourse(courseCode);
            if (course != nullptr) {
                // add open seat back to class
                course->incrementOpenSeats();
                school.at(id)->removeCourse(course);
            } else {
                std::cout << "Course code doesn't exist in course catalog." << std::endl;
            }
            std::cout << std::endl;
        } else if (command != 'q') {
            std::cout << "Invalid input, try again." << std::endl;
        }
    }
}

// reads from the default file of users to create the list of pre-existing enrolled students
void getUsers(std::string fileName, std::map<int, Student *> &school, std::map<std::string, Major *> majors) {
    std::ifstream in(fileName);

    std::string line;
    while (std::getline(in, line)) {
        std::vector<std::string> values = parseDelimitedLine(line, ';', 5);
        std::string name = values[0];
        std::string id = values[1];
        std::string strMajor = values[2];
        std::string completed = values[3];
        std::string enrolled = values[4];

        if (!isNumber(id)) {
            throw std::string("Student IDs must be a numbers.");
        }

        school[stoi(id)] = new Student(name, majors.at(strMajor), completed, enrolled);
    }
    in.close();
}

// prompts user for info to add as a new student to the school map with
// their student id as the key
void addStudent(std::map<int, Student *> &school, std::map<std::string, Major *> majors) {
    std::string name;
    std::string strId;
    std::string strMajor;
    std::string completed;
    std::string enrolled;

    std::cout << "Name? ";
    std::getline(std::cin, name);
    int id = getStudentId();
    std::cout << "Major? ";
    std::getline(std::cin, strMajor);

    std::cout << "Completed Courses? ";
    std::getline(std::cin, completed);

    std::cout << "Enrolled Courses? ";
    std::getline(std::cin, enrolled);
    std::cout << std::endl;

    school[id] = new Student(name, majors.at(strMajor), completed, enrolled);
}

// fills a map with Major objects and their name for the key
std::map<std::string, Major *> getMajors(CourseCatalog *catalog) {
    std::map<std::string, Major *> majors;
    for (std::string majorName : catalog->getMajors()) {
        // std::cout << majorName << std::endl;
        Major *major = new Major(majorName, catalog);
        majors[majorName] = major;
    }
    return majors;
}

// prints the possible majors a student can take
void printMajors(CourseCatalog *catalog) {
    std::vector<std::string> majors = catalog->getMajors();
    std::cout << "Available majors: ";
    if (majors.size() > 0) {
        std::cout << majors[0];
        for (int i = 1; i < majors.size(); i++) {
            std::cout << ", " << majors[i];
        }
        std::cout << std::endl
                  << std::endl;
    }
}

// prints the courses required for the user's major
void printMajorCourses(int id, const std::map<int, Student *> &school) {
    Major *toPrint = school.at(id)->getMajor();
    toPrint->printCourses();
}

// prints the main actions a user can do in the program
void printMainActions() {
    std::cout << "Main actions:" << std::endl;
    std::cout << "1) Add student." << std::endl;
    std::cout << "2) Remove student." << std::endl;
    std::cout << "3) Log in. " << std::endl;
    std::cout << "4) Print available majors. " << std::endl;
    std::cout << "5) Print course catalog." << std::endl;
    std::cout << "Q)uit" << std::endl;
}

int main() {
    intro();
    // Load course catalog from file.
    std::string catalogFileName = getFileName("Enter name of the course catalog file:");
    CourseCatalog *catalog = new CourseCatalog(catalogFileName);

    // Load majors from course catalog
    std::map<std::string, Major *> majors = getMajors(catalog);

    // Load saved students from file.
    std::string studentsFileName = getFileName("Enter name of the student list file:");
    std::cout << std::endl;
    std::map<int, Student *> school = {};
    getUsers(studentsFileName, school, majors);

    char command = 'i';
    while (command != 'q') {
        printMainActions();
        command = getUserActionChar(std::string("What would you like to do?"));
        if (command == '1') { // Add a student to the school
            addStudent(school, majors);
        } else if (command == '2') { // Remove a student from the school
            int id = getStudentId();
            school.erase(id);
        } else if (command == '3') { // allows user to provide their student id to edit
            int id = getStudentId(); // their personal student information
            if (school.find(id) == school.end()) {
                std::cout << std::endl
                          << "Provided student ID {" << id << "} not found!"
                          << std::endl
                          << std::endl;
            } else {
                handleEnrollmentAction(id, school, catalog);
            }
        } else if (command == '4') { // print available majors
            printMajors(catalog);
        } else if (command == '5') { // prints all available courses
            std::cout << "Course Catalog:" << std::endl;
            catalog->printAll();
        } else if (command != 'q') {
            std::cout << "Invalid input, try again." << std::endl;
        }
    }

    // save changes made to school (student directory)
    command = 'i';
    while (command != '1' && command != '2' && command != '3') {
        saveActions();
        command = getUserActionChar(std::string("Where would you like to save?"));
        if (command == '1') { // save in same file
            saveUsers(studentsFileName, school);
            std::cout << "Students saved to " << studentsFileName << std::endl;
        } else if (command == '2') { // save in new file
            std::cout << "Enter name of the student save file: ";
            studentsFileName = getUserInput();
            saveUsers(studentsFileName, school);
            std::cout << "Students saved to " << studentsFileName << std::endl;
        } else if (command == '3') { // don't save
            std::cout << "Changes will not be saved!" << std::endl;
        } else {
            std::cout << "Invalid input, try again." << std::endl;
        }
    }

    std::cout << "Application exited." << std::endl;
    return 0;
}