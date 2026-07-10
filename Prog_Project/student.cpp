#include <iostream>
#include "students.h"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

// Main function to manage all student-related operations and menus
void studentmanagment(vector<Student>& students) {
	int option = 0;
	bool done = false; // Controls the main menu loop

	// --- INITIALIZATION: LOAD DATA FROM FILE ---
	// Open the students.txt file to read existing student records into memory
	ifstream inFile("students.txt");
	if (inFile) {
		students.clear(); // Empty the vector to prevent duplicating records on reload
		string line;

		// Read the file line-by-line
		while (getline(inFile, line)) {
			stringstream ss(line);
			string tname, tid, tnid, tphone, tprog, tgen, tgpa, tlvl, td, tm, ty;

			// Parse the pipe-delimited string into distinct temporary variables
			getline(ss, tname, '|'); getline(ss, tid, '|'); getline(ss, tnid, '|');
			getline(ss, tphone, '|'); getline(ss, tprog, '|'); getline(ss, tgen, '|');
			getline(ss, tgpa, '|'); getline(ss, tlvl, '|');
			getline(ss, td, '|'); getline(ss, tm, '|'); getline(ss, ty, '|');

			// Reconstruct the Student object from the parsed data
			Student s;
			s.setname(tname); s.setstudentid(tid); s.setid(tnid);
			s.setphone(tphone); s.setprogram(tprog); s.setgender(tgen[0]);
			s.setgpa(stod(tgpa)); s.setlevel(stoi(tlvl));
			s.setDOB(stoi(td), stoi(tm), stoi(ty));
			s.valid = true;
			students.push_back(s); // Add to dynamic memory
		}
		inFile.close();
	}

	// --- MAIN MENU LOOP ---
	while (!done) {
		cout << "\n1. Add a student" << endl;
		cout << "2. Search for a student" << endl;
		cout << "3. Update student data" << endl;
		cout << "4. Delete a student" << endl;
		cout << "5. Display all students" << endl;
		cout << "6. Exit to main menu" << endl;
		cout << "Enter your option: ";
		cin >> option;

		switch (option) {

		case 1: { // ADD A NEW STUDENT
			Student s;
			s.valid = true;
			string tname, tstudentid, tnationalid, tphone_number, tprogram;
			int tday, tmonth, tyear;
			char tgender;
			double tgpa;
			int tlevel;

			// Gather user input and apply setter validations step-by-step
			cout << "Enter student name: ";
			cin.ignore();
			getline(cin, tname);
			s.setname(tname);
			if (!s.valid) { // Break early if validation fails
				s.valid = true;
				break;
			}

			cout << "Enter student ID: ";
			cin >> tstudentid;
			s.setstudentid(tstudentid);

			// Uniqueness Check: Ensure no duplicate student IDs exist
			for (int i = 0; i < students.size(); i++) {
				if (students[i].getstudentid() == s.getstudentid())
				{
					cout << "A student with this ID already exists. Student not added." << endl;
					s.valid = false;
					break;
				}
			}
			if (!s.valid) {
				s.valid = true;
				break;
			}

			cout << "Enter national ID: ";
			cin >> tnationalid;
			s.setid(tnationalid);

			// Uniqueness Check: Ensure no duplicate National IDs exist
			for (int i = 0; i < students.size(); i++) {
				if (students[i].getNationalID() == s.getNationalID())
				{
					cout << "A student with this ID already exists. Student not added." << endl;
					s.valid = false;
					break;
				}
			}
			if (!s.valid) {
				s.valid = true;
				break;
			}

			cout << "Enter phone number: ";
			cin >> tphone_number;
			s.setphone(tphone_number);
			if (!s.valid) {
				s.valid = true;
				break;
			}

			cout << "Enter program: ";
			cin.ignore();
			getline(cin, tprogram);
			s.setprogram(tprogram);
			if (!s.valid) {
				s.valid = true;
				break;
			}

			cout << "Enter date of birth (DD MM YYYY): ";
			cin >> tday >> tmonth >> tyear;
			s.setDOB(tday, tmonth, tyear);
			if (!s.valid) {
				s.valid = true;
				break;
			}

			cout << "Enter gender (M/F): ";
			cin >> tgender;
			s.setgender(tgender);
			if (!s.valid) {
				s.valid = true;
				break;
			}

			cout << "Enter GPA: ";
			cin >> tgpa;
			s.setgpa(tgpa);
			if (!s.valid) {
				s.valid = true;
				break;
			}

			cout << "Enter level: ";
			cin >> tlevel;
			s.setlevel(tlevel);
			if (!s.valid) {
				s.valid = true;
				break;
			}

			// Final Gate: If all inputs passed validation, save the student
			if (s.valid) {
				students.push_back(s); // Add to vector

				// Auto-save: Overwrite students.txt to persist the new record
				ofstream outFile("students.txt");
				for (int i = 0; i < students.size(); i++) {
					outFile << students[i].getname() << "|"
						<< students[i].getstudentid() << "|"
						<< students[i].getNationalID() << "|"
						<< students[i].getphone() << "|"
						<< students[i].getprogram() << "|"
						<< students[i].getgender() << "|"
						<< students[i].getGPA() << "|"
						<< students[i].getlevel() << "|"
						<< students[i].getday() << "|"
						<< students[i].getmonth() << "|"
						<< students[i].getyear() << endl;
				}
				outFile.close();
				cout << "Student added successfully!" << endl;
			}
			break;
		}

		case 2: { // SEARCH FOR A STUDENT
			int option2;
			cout << "Search by: 1. Student ID, 2. National ID, 3. Name: \nOption: ";
			cin >> option2;
			bool found = false;
			string option2input;

			// Sub-menu for different search filters
			switch (option2) {
			case 1: { // Search by Student ID
				cout << "Enter Student ID: ";
				cin >> option2input;
				for (int i = 0; i < students.size(); i++) {
					if (students[i].getstudentid() == option2input) {
						students[i].getinfo(); // Print student details
						found = true;
						break;
					}

				} if (!found) {
					cout << "Student not found." << endl;
				}

			} break;
			case 2: { // Search by National ID
				cout << "Enter National ID: ";
				cin >> option2input;
				for (int i = 0; i < students.size(); i++) {
					if (students[i].getNationalID() == option2input) {
						students[i].getinfo(); // Print student details
						found = true;
						break;
					}
				} if (!found) {
					cout << "Student not found." << endl;
				}
			} break;
			case 3: { // Search by Exact Name
				cout << "Enter Name: ";
				cin.ignore();
				getline(cin, option2input);
				for (int i = 0; i < students.size(); i++) {
					if (students[i].getname() == option2input) {
						students[i].getinfo(); // Print student details
						found = true;
						break;
					}
				} if (!found) {
					cout << "Student not found." << endl;
				}
			}
			}
			break; // Added missing break for case 2

		} break;

		case 3: { // UPDATE STUDENT DATA
			string id; cout << "Enter student ID to update: "; cin >> id;
			bool found = false;

			// Locate the specific student
			for (int i = 0; i < students.size(); i++) {
				if (students[i].getstudentid() == id) {
					found = true;
					int option3;
					cout << "1. GPA, 2. Program, 3. Level, 4. Phone: ";
					cin >> option3;
					cout << "Enter new value: ";

					// Sub-menu for updating specific attributes
					switch (option3) {
					case 1: { double n; cin >> n; students[i].setgpa(n); break; }
					case 2: { string p; cin.ignore(); getline(cin, p); students[i].setprogram(p); break; }
					case 3: { int l; cin >> l; students[i].setlevel(l); break; }
					case 4: { string ph; cin >> ph; students[i].setphone(ph); break; }
					}

					// Auto-save: Overwrite the text file with the updated data
					ofstream outFile("students.txt");
					for (int i = 0; i < students.size(); i++) {
						outFile << students[i].getname() << "|"
							<< students[i].getstudentid() << "|"
							<< students[i].getNationalID() << "|"
							<< students[i].getphone() << "|"
							<< students[i].getprogram() << "|"
							<< students[i].getgender() << "|"
							<< students[i].getGPA() << "|"
							<< students[i].getlevel() << "|"
							<< students[i].getday() << "|"
							<< students[i].getmonth() << "|"
							<< students[i].getyear() << endl;
					}
					outFile.close();
					break;
				}
			}
			if (!found) cout << "Student not found." << endl;
			break;
		}

		case 4: { // DELETE A STUDENT
			string id; cout << "Enter student ID to delete: "; cin >> id;
			bool found = false;

			// Locate the student to be removed
			for (int i = 0; i < students.size(); i++) {
				if (students[i].getstudentid() == id) {
					students.erase(students.begin() + i); // Remove from dynamic memory
					found = true; cout << "Student deleted successfully!" << endl;

					// Auto-save: Overwrite the file to persist the deletion
					ofstream outFile("students.txt");
					for (int i = 0; i < students.size(); i++) {
						outFile << students[i].getname() << "|"
							<< students[i].getstudentid() << "|"
							<< students[i].getNationalID() << "|"
							<< students[i].getphone() << "|"
							<< students[i].getprogram() << "|"
							<< students[i].getgender() << "|"
							<< students[i].getGPA() << "|"
							<< students[i].getlevel() << "|"
							<< students[i].getday() << "|"
							<< students[i].getmonth() << "|"
							<< students[i].getyear() << endl;
					}
					outFile.close();
					break;
				}
			}
			if (!found) cout << "Student not found." << endl;
			break;
		}

		case 5: { // DISPLAY ALL STUDENTS WITH SORTING
			if (students.empty()) {
				cout << "No students to display." << endl;
			}
			else {
				cout << "1. Sort by GPA (High-Low)\n2. Sort by Name (A-Z)\n3. Sort by ID (High-Low)\nEnter choice: ";
				int option5; cin >> option5;

				// Bubble Sort algorithms used to organize the vector before printing
				switch (option5) {
				case 1: // Sort Descending by GPA
					for (int i = 0; i < students.size() - 1; i++) {
						for (int j = 0; j < students.size() - i - 1; j++) {
							if (students[j].getGPA() < students[j + 1].getGPA()) swap(students[j], students[j + 1]);
						}
					}
					break;
				case 2: // Sort Ascending by Name (Alphabetical)
					for (int i = 0; i < students.size() - 1; i++) {
						for (int j = 0; j < students.size() - i - 1; j++) {
							if (students[j].getname() > students[j + 1].getname()) swap(students[j], students[j + 1]);
						}
					}
					break;
				case 3: // Sort Descending by Student ID
					for (int i = 0; i < students.size() - 1; i++) {
						for (int j = 0; j < students.size() - i - 1; j++) {
							if (students[j].getstudentid() < students[j + 1].getstudentid()) swap(students[j], students[j + 1]);
						}
					}
					break;
				}

				// Iterate through the newly sorted vector and display everyone
				for (int i = 0; i < students.size(); i++) {
					students[i].getinfo();
				}
			}
			break;
		}
		case 6: // EXIT MODULE
			cout << "Exiting system..." << endl;
			done = true; // Breaks the while loop
			break;
		default: // HANDLE INVALID MENU INPUTS
			cout << "Invalid option." << endl;
			break;
		}
	}
}