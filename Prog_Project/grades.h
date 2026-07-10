#pragma once
#include <iostream>
#include <string>

using namespace std;

// The Grade class acts as a junction/relational entity linking a specific student to a specific course.
class Grade {
private:
	// Core relational attributes
	string studentid;
	string courseCode;

	// Scoring attributes
	int midterm;
	int finalExam;

public:
	// Flag used to track if the inputs provided during object creation/updating pass all validation rules
	bool valid = true;

	// Default constructor: Initializes a Grade object with safe default/placeholder values to prevent memory junk
	Grade() {
		studentid = "00P0000";
		courseCode = "XXX000";
		midterm = 0;
		finalExam = 0;
	}

	// --- Getters (Accessors) ---
	// Methods to safely retrieve private data from outside the class
	string getStudentID() const { return studentid; }
	string getCourseCode() const { return courseCode; }
	int getMidterm() { return midterm; }
	int getFinalExam() { return finalExam; }

	// Dynamically calculates the total mark by adding midterm and final scores together
	int getTotalGrade() { return midterm + finalExam; }

	// --- Setters (Mutators) ---
	// Methods to assign values to private data, including strict validation gates

	void setstudentid(string studentid) {
		valid = true;

		// Validation Gate 1: Check if length is exactly 7 and the 3rd character is 'P' or 'p'
		if (studentid.length() == 7 and (studentid[2] == 'P' or studentid[2] == 'p')) {
			valid = true;
		}
		else {
			valid = false;
		}

		// Validation Gate 2: Ensure the first two characters are numeric digits (Year prefix)
		for (int i = 0; i < 2; i++) {
			if (studentid[i] < '0' or studentid[i] > '9') {
				valid = false;
			}
		}

		// Validation Gate 3: Ensure the last four characters are numeric digits
		for (int i = 3; i < 7; i++) {
			if (studentid[i] < '0' or studentid[i] > '9') {
				valid = false;
			}
		}

		if (!valid) {
			cout << "Invalid student ID. " << endl;
		}
		if (valid) {
			this->studentid = studentid;
		} // if the student ID is valid, it is assigned to the class member variable
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
			// Validation Gate 3: The last 3 characters must be numeric digits
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

	void setMidterm(int midterm) {
		// Validates that the midterm grade is clamped between 0 and 40
		if (midterm >= 0 and midterm <= 40) {
			this->midterm = midterm;
		}
		else {
			cout << "Invalid midterm grade. Please enter a value between 0 and 40." << endl;
		}
	}

	void setFinalExam(int finalExam) {
		// Validates that the final exam grade is clamped between 0 and 60
		if (finalExam >= 0 and finalExam <= 60) {
			this->finalExam = finalExam;
		}
		else {
			cout << "Invalid final exam grade. Please enter a value between 0 and 60." << endl;
		}
	}

	// Utility function to print a quick summary of the specific grade record to the console
	void getinfo() {
		cout << "\nStudent ID: " << studentid << endl;
		cout << "Course Code: " << courseCode << endl;
		cout << "Final Grade: " << getTotalGrade() << endl;
	}

};