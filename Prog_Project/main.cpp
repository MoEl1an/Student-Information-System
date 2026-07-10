#include <iostream>
#include <vector>
#include "students.h"
#include "course.h"
#include "grades.h"

using namespace std;

// 1. Tell main that these functions exist in other files
void studentmanagment(vector<Student>& students);
void courseManagement(vector<Course>& courses);

// FIX: Match the actual function signature exactly!
void gradeManagement(vector<Grade>& grades, vector<Student>& students, vector<Course>& courses);

int main() {
    // 2. Create the actual database (the vectors)
    vector<Student> allStudents;
    vector<Course> allCourses;
    vector<Grade> allGrades;
    int option = 0;

    cout << "Welcome to the SIS!" << endl;

    // FIX: Add the while loop so the program doesn't instantly close
    while (option != 4) {
        cout << "\nPlease select an option: " << endl
            << "1. Student Management" << endl
            << "2. Course Management" << endl
            << "3. Grade Management" << endl
            << "4. Exit" << endl;

        // FIX: Actually take the user's input!
        cout << "Enter option: ";
        cin >> option;

        switch (option) {
        case 1: {
            studentmanagment(allStudents);
            break;
        }
        case 2: {
            courseManagement(allCourses);
            break;
        }
        case 3: {
            // FIX: Pass all three vectors to the grade management engine
            gradeManagement(allGrades, allStudents, allCourses);
            break;
        }
        case 4: {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        }
        default: {
            cout << "Invalid option. Try again." << endl;
            break;
        }
        }
    }

    return 0;
}