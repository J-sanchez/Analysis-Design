/**
 * The C++ program defines structures and functions to load, display, and manage course data from a file through a menu-driven
 * interface.
 * 
 * @param filename The code you provided is a C++ program that manages course information. It reads course data from a file, stores it
 * in a map, and provides options to display the course list and details based on user input.
 * 
 * @return The main function returns an integer value of 0, which indicates successful execution of the program.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};
struct CompareCourse {
    bool operator()(const Course& a, const Course& b) const {
        return a.courseNumber < b.courseNumber;
    }
};
// Define the hash map (unordered_map)
unordered_map<string, Course> courseMap;

// Function prototypes
void loadData(const string& filename);
void printSortedList();
void printCourseInfo(const string& courseNumber);
void displayMenu();
void mainMenu();

/**
 * The function `loadData` opens a file specified by the filename parameter and displays an error message if the file cannot be opened.
 * 
 * @param filename The `filename` parameter in the `loadData` function is a reference to a constant string that represents the name of
 * the file from which data will be loaded.
 * 
 * @return In this code snippet, if the file cannot be opened successfully, the function will return without loading any data.
 */
void loadData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream courses(line);
        Course course;
        string prerequisitesList;

        getline(courses, course.courseNumber, ',');
        getline(courses, course.title, ',');
        getline(courses, prerequisitesList);

        istringstream prereqs(prerequisitesList);
        string prereq;
        while (getline(prereqs, prereq, ';')) {
            course.prerequisites.push_back(prereq);
        }

        courseMap[course.courseNumber] = course;
    }
    file.close();
}

/**
 * The function `printSortedList` creates a vector of courses from an unordered map.
 */
void printSortedList() {
    vector<Course> courses;
    for (unordered_map<string, Course>::iterator node = courseMap.begin(); node != courseMap.end(); ++node) {
        courses.push_back(node->second);
    }

    // Sort using the function object
    sort(courses.begin(), courses.end(), CompareCourse());

    for (size_t i = 0; i < courses.size(); ++i) {
        const Course& course = courses[i];
        cout << "  Number: " << course.courseNumber << endl;
        cout << " Title: " << course.title << endl;
        cout << " Prerequisites: ";
        if (!course.prerequisites.empty()) {
            for (size_t j = 0; j < course.prerequisites.size(); ++j) {
                cout << course.prerequisites[j] << " ";
            }
        } else {
            cout << "No Prereqs Found" << endl;
        }
        cout << endl << endl;
    }
}
//Print Course Information
void printCourseInfo(const string& courseNumber) {
    unordered_map<string, Course>::iterator node = courseMap.find(courseNumber);
    if (node != courseMap.end()) {
        const Course& course = node->second;
        cout << " Course Number: " << course.courseNumber << endl;
        cout << " Title: " << course.title << endl;
        cout << " Prerequisites: ";
        if (!course.prerequisites.empty()) {
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i] << " ";
            }
        } else {
            cout << "No Prereqs Found" << endl;
        }
        cout << endl;
    } else {
        cout << "Course not found." << endl;
    }
}
// Display Menu and Handle User Input

/**
 * The function `displayMenu` prints a menu with options for loading file data, printing all courses, printing course details, and
 * exiting.
 */
void displayMenu() {
    cout << "1. Load File Data" << endl;
    cout << "2. Print All Courses" << endl;
    cout << "3. Print Course Details" << endl;
    cout << "9. Exit" << endl;
}

void mainMenu() {
    int option;
    bool dataLoaded = false;

    while (true) {
        displayMenu();
        cout << "Enter Choice: " << endl;
        cin >> option;
        cin.ignore(); 
        switch (option) {
            case 1: {
                string filename;
                cout << "Enter filename: ";
                getline(cin, filename);
                loadData(filename);
                dataLoaded = true;
                break;
            }
            case 2:
                if (dataLoaded) {
                    printSortedList();
                } else {
                    cout << "Data Not Loaded. Load data first." << endl;
                }
                break;
            case 3: {
                if (dataLoaded) {
                    string courseNumber;
                    cout << "Enter course number: ";
                    getline(cin, courseNumber);
                    printCourseInfo(courseNumber);
                } else {
                    cout << "Data Not Loaded. Load data first." << endl;
                }
                break;
            }
            case 9:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
}

int main() {
    mainMenu();
    return 0;
}