#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// The Course class represents a university academic subject/course.
class Course {
private:
	// Core course attributes
	string courseName;
	string courseCode;
	int creditHours;

public:
	// Flag used to track if the inputs provided during object creation/updating pass all validation rules
	bool valid = true;

	// Default constructor: Initializes a Course object with safe default/placeholder values
	Course() {
		courseName = "Unknown";
		courseCode = "XXX000";
		creditHours = 2;
	}

	// --- Getters (Accessors) ---
	// Methods to safely retrieve private data from outside the class
	string getCourseName() const { return courseName; }
	string getCourseCode() const { return courseCode; }
	int getCreditHours() const { return creditHours; }


	// --- Setters (Mutators) ---
	// Methods to assign values to private data, including strict validation gates

	void setCourseName(string name) {
		// Validates that the course name is not an empty string
		if (name.length() > 0) {
			courseName = name;
		}
		else {
			cout << "Course name cannot be empty!" << endl;
			valid = false;
		}
	}

	void setCourseCode(string code) {
		valid = true;

		// Validation Gate 1: Length must be exactly 6 characters
		if (code.length() != 6) {
			valid = false;
		}
		else {
			// Validation Gate 2: The first 3 characters must be alphabetic letters (A-Z or a-z)
			for (int i = 0; i < 3; i++) {
				if ((code[i] < 'A' or code[i] > 'Z') and (code[i] < 'a' or code[i] > 'z')) {
					valid = false;
				}
			}
			// Validation Gate 3: The last 3 characters must be numeric digits (0-9)
			for (int i = 3; i < 6; i++) {
				if (code[i] < '0' or code[i] > '9') {
					valid = false;
				}
			}
		}

		if (!valid) {
			cout << "Invalid course code. Please enter a code in the format XXX000." << endl;
		}
		else {
			// If all validations pass, assign the course code
			courseCode = code;
		}
	}

	void setCreditHours(int hours) {
		// Validates that the credit hours are between 2 and 4 (inclusive, since >1 and <5)
		if (hours > 1 and hours < 5) {
			creditHours = hours;
		}
		else {
			cout << "Invalid credit hours. Please enter a value between 2 and 4." << endl;
			valid = false;
		}
	}
};