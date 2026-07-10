#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
#pragma once	
class Student { // Student class definition
private:
	string name;
	string studentid , nationalid;
	char gender;
	string phone_number;
	string program;
	int level;
	double gpa;
	int month, day, year; // Date of birth
public:
	bool valid = true;
	// Default Constructor - Shields against "Memory Junk"
	Student() {
		name = "";
		studentid = "00P0000";
		nationalid = "10000000000000";
		gender = 'U';
		phone_number = "00000000000";
		program = "General";
		level = 1;
		gpa = 0.0;
		day = 1; month = 1; year = 2000;
	}

	// the getters to access the private members of the class in the main function
	string getstudentid() const { return studentid; }
	string getNationalID() const { return nationalid; }
	string getname() const { return name; }
	double getGPA() const { return gpa; }
	string getphone() { return phone_number; }
	char getgender() { return gender; }
	int getday() { return day; }
	int getmonth() { return month; }
	int getyear() { return year; }
	string getprogram() { return program; }
	int getlevel() { return level; }

	// the setters to set the private members of the class in the main function with validation
	void setname(string name) {
		int spaces = 0;
		for (int i = 0; i < name.length(); i++) {
			if (name[i] == ' ') {
				spaces += 1; 
			} // checks if the name contains exactly one space (first and last name)
		}
		if (spaces != 1) {
			cout << "Invalid name. " << endl;
			valid = false;
		}
		else
		{
			this->name = name;
		}

	}
	void setid(string nationalid) {
		
		if (nationalid.length() != 14 or nationalid[0] == '0') {
			valid = false;
		} // checks if the national ID is exactly 14 digits long and does not start with '0'
		for (int i = 1; i < 14; i++) {
			if (valid and (nationalid[i] < '0' or nationalid[i] > '9')) {
				valid = false;
			}
		} // checks if all characters in the national ID (except the first one) are digits
		if (!valid) {
			cout << "Invalid national ID. " << endl;
			
		}
		if (valid) {
			this->nationalid = nationalid;
		} // if the national ID is valid, it is assigned to the class member variable
	}
	void setstudentid(string studentid) {
		
		if (studentid.length() == 7 and  (studentid[2] == 'P' or studentid[2] == 'p') ) {
			valid = true;
		}
		else {
			valid = false;
		}
		for (int i = 0; i < 2; i++) {
			if (valid and (studentid[i] < '0' or studentid[i] > '9') ) {
				valid = false;
			}
		}
		for (int i = 3; i < 7; i++) {
			if (valid and (studentid[i] < '0' or studentid[i] > '9')) {
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
	void setphone(string phone_number) {
	     valid = true;
		if (phone_number.length() != 11 or (phone_number[0] != '0' or phone_number[1] != '1')) {
			valid = false;
		}
		for (int i = 2; i < 11; i++) {
			if (valid and(phone_number[i] < '0' or phone_number[i] > '9')) {
				valid = false;
			}
		}
		if (!valid) {
			cout << "Invalid phone number. " << endl;
		}
		if (valid) {
			this->phone_number = phone_number;
		} // if the phone number is valid, it is assigned to the class member variable
	}
	void setDOB(int d, int m, int y) {
		// 1. Get the current system time
		time_t t = time(0);
		tm* now = localtime(&t);

		int currentYear = now->tm_year + 1900;
		int currentMonth = now->tm_mon + 1; // tm_mon is 0-11, so +1 makes it 1-12
		int currentDay = now->tm_mday;

		valid = true;

		// 2. Basic Date Validation (Gate 1)
		if (y > currentYear || m < 1 || m > 12 || d < 1 || d > 31) {
			valid = false;
		}

		// 3. The Age Logic (Gate 2: age >= 17)
		if (valid) {
			int age = currentYear - y;

			if (age < 17) {
				valid = false; // Definitely too young
			}
			else if (age == 17) {
				// If they are exactly 17 by year, check the month
				if (m > currentMonth) {
					valid = false; // Birthday hasn't happened yet this year
				}
				else if (m == currentMonth) {
					// If the month is also the same, check the day
					if (d > currentDay) {
						valid = false; // Birthday is later this month
					}
				}
			}
		}

		if (!valid) {
			cout << "Invalid Date of Birth. Student must be 17 or older." << endl;
		}
		else {
			this->day = d;
			this->month = m;
			this->year = y;
			
		}
	}
	void setgender(char gender) {
				if (gender == 'M' || gender == 'F' || gender == 'm' || gender == 'f') {
			this->gender = gender;
		}
		else {
			cout << "Invalid gender. Please enter 'M' or 'F'." << endl;
			valid = false;
		}
	}
	
	void setlevel(int level) {
		if (level >= 1 && level <= 4) {
			this->level = level;
		}
		else {
			cout << "Invalid level. Please enter a value between 1 and 4." << endl;
			valid = false;
		}
	} // Validates that the level is between 1 and 4 (inclusive) before setting it. If the input is invalid, it prints an error message.
	void setgpa(double gpa) {
		if (gpa >= 0.0 && gpa <= 4.0) {
			this->gpa = gpa;
		}
		else {
			cout << "Invalid GPA. Please enter a value between 0.0 and 4.0." << endl;
			valid = false;
		}
	
		
	} // Validates that the GPA is between 0.0 and 4.0 (inclusive) before setting it. If the input is invalid, it prints an error message.
	void setprogram(string program) {
		this->program = program;
	}
	void getinfo() {
		cout << "\n \nName: " << name << endl;
		cout << "Student Id: " << studentid << endl;
		cout << "National Id: " << nationalid << endl;
		cout << "Gender: " << gender << endl;
		cout << "Phone Number: " << phone_number << endl;
		cout << "Program: " << program << endl;
		cout << "Level: " << level << endl;	
		cout << "GPA: " << gpa << endl;
		cout << "Date of Birth: " << month << "/" << day << "/" << year << endl;

	} // Displays all the information of the student in a readable format.

};