#include <iostream>
#include "course.h"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

// Main function to manage all course-related operations
void courseManagement(vector<Course>& courses) {
	int option = 0;
	bool done = false; // Controls the main menu loop
	bool valid = true; // Used for validation during updates

	// --- INITIALIZATION: LOAD DATA FROM FILE ---
	// Opens the courses.txt file to read existing course records into memory
	ifstream inFile("courses.txt");
	if (inFile) {
		courses.clear(); // Empty the vector before loading to prevent duplicates
		string line;

		// Read the file line-by-line
		while (getline(inFile, line)) {
			stringstream ss(line);
			string tname, tcode, tch;

			// Parse the pipe-delimited string into distinct variables
			getline(ss, tname, '|'); getline(ss, tcode, '|'); getline(ss, tch, '|');

			// Create a temporary Course object, populate it, and push it to the vector
			Course c;
			c.setCourseName(tname); c.setCourseCode(tcode); c.setCreditHours(stoi(tch));
			c.valid = true;
			courses.push_back(c);
		}
		inFile.close();
	}

	// --- MAIN MENU LOOP ---
	while (!done) {
		cout << "\n \n1. Add a course" << endl;
		cout << "2. View courses" << endl;
		cout << "3. Update course" << endl;
		cout << "4. Delete a course" << endl;
		cout << "5. Exit to main menu" << endl;
		cout << "Enter your option: ";

		cin >> option;
		switch (option) {

		case 1: { // ADD A NEW COURSE
			Course c;
			c.valid = true;
			string tname, tcode; int tch;

			cout << "Enter course name: ";
			cin.ignore(); // Clears the newline character from the input buffer
			getline(cin, tname);
			c.setCourseName(tname);
			if (!c.valid) break; // Exit case early if validation failed

			cout << "Enter course code: ";
			cin >> tcode;
			c.setCourseCode(tcode);

			// Uniqueness Check: Ensure no duplicate course codes exist in the system
			for (int i = 0; i < courses.size(); i++) {
				if (courses[i].getCourseCode() == c.getCourseCode()) {
					cout << "A course with this code already exists. Course not added." << endl;
					c.valid = false;
					break;
				}
			}
			if (!c.valid) break; // Exit case early if duplicate was found or code is invalid

			cout << "Enter credit hours: ";
			cin >> tch;
			c.setCreditHours(tch);
			if (!c.valid) break; // Exit case early if credit hours are out of bounds

			// Final Gate: If all checks pass, save the course
			if (c.valid) {
				courses.push_back(c); // Add to dynamic memory

				// Overwrite courses.txt with the updated vector to persist data
				ofstream outFile("courses.txt");
				for (int i = 0; i < courses.size(); i++) {
					outFile << courses[i].getCourseName() << "|"
						<< courses[i].getCourseCode() << "|"
						<< courses[i].getCreditHours() << endl;
				}
				outFile.close();
				cout << "Course added successfully!" << endl;
			}
			break;
		}

		case 2: { // VIEW ALL COURSES
			if (courses.empty()) {
				cout << "No courses to display." << endl; // Added empty check
			}
			else {
				// Iterate through the vector and print each course's details
				for (int i = 0; i < courses.size(); i++) {
					cout << "\nCourse Name: " << courses[i].getCourseName()
						<< " | Course Code: " << courses[i].getCourseCode()
						<< " | Credit Hours: " << courses[i].getCreditHours() << endl;
				}
			}
			break;
		}

		case 3: { // UPDATE AN EXISTING COURSE
			string code; cout << "Enter course code to update: "; cin >> code;
			bool found = false;

			// Search for the target course using its unique Course Code
			for (int i = 0; i < courses.size(); i++) {
				if (courses[i].getCourseCode() == code) {
					found = true;
					int option3;
					cout << "Update: 1. Course Name, 2. Credit Hours: " << endl << "Enter your option: ";
					cin >> option3;

					// Sub-menu for updating specific attributes
					switch (option3) {
					case 1: {
						cout << "Enter new course name: ";
						string n;
						cin.ignore();
						getline(cin, n);
						courses[i].setCourseName(n);
						break;
					}
					case 2: {
						cout << "Enter new credit hours: ";
						int ch; cin >> ch;
						// Inline validation for credit hours before updating
						if (ch > 1 and ch < 5) {
							courses[i].setCreditHours(ch);
							valid = true;
							break;
						}
						else {
							cout << "Invalid credit hours. Please enter a value between 2 and 4." << endl;
							valid = false;
							break;
						}
					}
					default: {
						cout << "Invalid option, Please try again." << endl;
						valid = false;
						break;
					}

					}

					// Auto-save: If the update was successful, overwrite the text file
					if (valid) {
						ofstream outFile("courses.txt");
						for (int k = 0; k < courses.size(); k++) { // Changed 'i' to 'k' to avoid shadowing outer loop
							outFile << courses[k].getCourseName() << "|"
								<< courses[k].getCourseCode() << "|"
								<< courses[k].getCreditHours() << endl;
						}
						outFile.close();
						cout << "Course updated successfully!" << endl;
						break;
					}
				}
			}
			if (!found) cout << "Course not found." << endl;
			break;
		}

		case 4: { // DELETE A COURSE
			string code; cout << "Enter course code to delete: "; cin >> code;
			bool found = false;

			// Locate the course to be removed
			for (int i = 0; i < courses.size(); i++) {
				if (courses[i].getCourseCode() == code) {
					courses.erase(courses.begin() + i); // Remove the course from the vector
					found = true;
					cout << "Course deleted successfully!" << endl;

					// Auto-save: Overwrite the text file without the deleted course
					ofstream outFile("courses.txt");
					for (int k = 0; k < courses.size(); k++) { // Changed 'i' to 'k' 
						outFile << courses[k].getCourseName() << "|"
							<< courses[k].getCourseCode() << "|"
							<< courses[k].getCreditHours() << endl;
					}
					outFile.close();
					break;
				}
			}
			if (!found) cout << "Course not found." << endl;
			break;
		}

		case 5: { // EXIT MODULE
			cout << "Exiting course management." << endl;
			done = true; // Breaks the while loop
			break;
		}

		default: { // HANDLE INVALID MENU INPUTS
			cout << "Invalid option, Please try again." << endl;
			break;
		}
		}
	}
}