#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> 
#include "grades.h"
#include "students.h"
#include "course.h"

using namespace std;

// Helper Function: Converts a raw percentage score into a 4.0 scale GPA point value.
double getGPAPoints(int totalMark) {
	if (totalMark >= 90) return 4.0;
	if (totalMark >= 85) return 3.7;
	if (totalMark >= 80) return 3.3;
	if (totalMark >= 75) return 3.0;
	if (totalMark >= 70) return 2.7;
	if (totalMark >= 65) return 2.4;
	if (totalMark >= 60) return 2.2;
	if (totalMark >= 50) return 2.0;
	return 0.0; // Fail
}

// Helper Function: Converts a raw percentage score into a standard Letter Grade.
string getLetter(int totalMark) {
	if (totalMark >= 90) return "A ";
	if (totalMark >= 85) return "A-";
	if (totalMark >= 80) return "B+";
	if (totalMark >= 75) return "B ";
	if (totalMark >= 70) return "C+";
	if (totalMark >= 65) return "C ";
	if (totalMark >= 60) return "D+";
	if (totalMark >= 50) return "D ";
	return "F "; // Fail
}

void gradeManagement(vector<Grade>& grades, vector<Student>& students, vector<Course>& courses) {
	// --- 1. INITIALIZATION: LOAD ALL DATA FROM PERSISTENT TEXT FILES ---

	// Load existing Students into memory to enable relational cross-checking
	ifstream stuFile("students.txt");
	if (stuFile) {
		students.clear();
		string line;
		while (getline(stuFile, line)) {
			stringstream ss(line);
			string tname, tid, tnid, tphone, tprog, tgen, tgpa, tlvl, td, tm, ty;

			// Parse the pipe-delimited text file
			getline(ss, tname, '|'); getline(ss, tid, '|'); getline(ss, tnid, '|');
			getline(ss, tphone, '|'); getline(ss, tprog, '|'); getline(ss, tgen, '|');
			getline(ss, tgpa, '|'); getline(ss, tlvl, '|');
			getline(ss, td, '|'); getline(ss, tm, '|'); getline(ss, ty, '|');

			// Reconstruct the Student object
			Student s;
			s.setname(tname); s.setstudentid(tid); s.setid(tnid);
			s.setphone(tphone); s.setprogram(tprog); s.setgender(tgen[0]);
			s.setgpa(stod(tgpa)); s.setlevel(stoi(tlvl));
			s.setDOB(stoi(td), stoi(tm), stoi(ty));
			s.valid = true;
			students.push_back(s);
		}
		stuFile.close();
	}

	// Load existing Courses into memory
	ifstream crsFile("courses.txt");
	if (crsFile) {
		courses.clear();
		string line;
		while (getline(crsFile, line)) {
			stringstream ss(line);
			string tname, tcode, tch;
			getline(ss, tname, '|'); getline(ss, tcode, '|'); getline(ss, tch, '|');

			Course c;
			c.setCourseName(tname); c.setCourseCode(tcode); c.setCreditHours(stoi(tch));
			c.valid = true;
			courses.push_back(c);
		}
		crsFile.close();
	}

	// Load existing Grades into memory
	ifstream inFile("grades.txt");
	if (inFile) {
		grades.clear();
		string line;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string tstudentid, tcoursecode, tmidterm, tfinal;

			getline(ss, tstudentid, '|');
			getline(ss, tcoursecode, '|');
			getline(ss, tmidterm, '|');
			getline(ss, tfinal, '|');

			Grade g;
			g.setstudentid(tstudentid);
			g.setCourseCode(tcoursecode);
			g.setMidterm(stoi(tmidterm));
			g.setFinalExam(stoi(tfinal));
			g.valid = true;
			grades.push_back(g);
		}
		inFile.close();
	}

	// --- 2. MAIN GRADES MENU LOOP ---
	bool done = false;
	int option = 0;
	while (!done) {
		cout << "\n--- Grades Management ---" << endl;
		cout << "1. Enter grades\n2. View grades\n3. Update grade\n4. Delete grade\n5. Calculate GPA\n6. Generate Transcript\n7. Exit to main menu\nOption: ";
		cin >> option;

		switch (option) {
		case 1: { // ADD A NEW GRADE RECORD
			Grade g;
			string sid, ccode;
			int mid, fin;
			bool studentExists = false, courseExists = false;

			cout << "Enter Student ID: "; cin >> sid;

			// Relational Check 1: Ensure the student actually exists in the database
			for (int i = 0; i < students.size(); i++) {
				if (students[i].getstudentid() == sid) {
					studentExists = true;
					break;
				}
			}
			if (!studentExists) {
				cout << "Error: Student ID not found in system!" << endl;
				break;
			}

			cout << "Enter Course Code: "; cin >> ccode;

			// Relational Check 2: Ensure the course actually exists in the database
			for (int i = 0; i < courses.size(); i++) {
				if (courses[i].getCourseCode() == ccode) { courseExists = true; break; }
			}

			if (!courseExists) {
				cout << "Error: Course code not found in system!" << endl;
				break;
			}

			// Relational Check 3: Prevent duplicate grades for the same student in the same course
			bool alreadyHasGrade = false;
			for (int i = 0; i < grades.size(); i++) {
				if (grades[i].getStudentID() == sid && grades[i].getCourseCode() == ccode) {
					alreadyHasGrade = true;
					break;
				}
			}

			// Final Gate: If all checks pass, prompt for marks and save
			if (alreadyHasGrade) {
				cout << "Error: Grade record for this student in this course already exists!" << endl;
			}
			else if (studentExists && courseExists) {
				g.setstudentid(sid);
				g.setCourseCode(ccode);
				cout << "Enter Midterm (0-40): "; cin >> mid; g.setMidterm(mid);
				cout << "Enter Final (0-60): "; cin >> fin; g.setFinalExam(fin);

				if (g.valid) { // Only save if the midterm and final marks passed validation
					grades.push_back(g);

					// Auto-save the new grade to the persistent text file
					ofstream outFile("grades.txt");
					for (int i = 0; i < grades.size(); i++) {
						outFile << grades[i].getStudentID() << "|" << grades[i].getCourseCode() << "|"
							<< grades[i].getMidterm() << "|" << grades[i].getFinalExam() << endl;
					}
					outFile.close();
					cout << "Grade saved successfully!" << endl;
				}
			}
			break;
		}
		case 2: { // VIEW GRADES
			if (grades.empty()) {
				cout << "No grades recorded yet." << endl;
				break;
			}
			int option2 = 0;
			cout << "1. View all grades\n2. View grades for a specific student\nOption: ";
			cin >> option2;

			// Sub-menu to either dump the whole database or filter by Student ID
			if (option2 == 1) {
				for (int i = 0; i < grades.size(); i++) {
					grades[i].getinfo();
					cout << "----------------" << endl;
				}
			}
			else if (option2 == 2) {
				string sid;
				cout << "Enter Student ID: "; cin >> sid;
				bool found = false;
				for (int i = 0; i < grades.size(); i++) {
					if (grades[i].getStudentID() == sid) {
						grades[i].getinfo();
						cout << "----------------" << endl;
						found = true;
					}
				}
				if (!found) cout << "No grades found for this student." << endl;
			}
			break;
		}
		case 3: { // UPDATE AN EXISTING GRADE
			string sid, ccode;
			cout << "Enter Student ID: "; cin >> sid;
			cout << "Enter Course Code: "; cin >> ccode;
			bool found = false;

			// Search for the specific Grade junction record
			for (int i = 0; i < grades.size(); i++) {
				if (grades[i].getStudentID() == sid && grades[i].getCourseCode() == ccode) {
					found = true;
					int m, f;
					cout << "New Midterm: "; cin >> m; grades[i].setMidterm(m);
					cout << "New Final: "; cin >> f; grades[i].setFinalExam(f);

					// Overwrite the file with the updated memory state
					ofstream outFile("grades.txt");
					for (int k = 0; k < grades.size(); k++) {
						outFile << grades[k].getStudentID() << "|" << grades[k].getCourseCode() << "|"
							<< grades[k].getMidterm() << "|" << grades[k].getFinalExam() << endl;
					}
					outFile.close();
					cout << "Grade updated successfully!" << endl;
					break;
				}
			}
			if (!found) cout << "Grade record not found." << endl;
			break;
		}
		case 4: { // DELETE A GRADE
			string sid, ccode;
			cout << "Enter Student ID: "; cin >> sid;
			cout << "Enter Course Code: "; cin >> ccode;
			bool found = false;

			// Locate and remove the specific grade record
			for (int i = 0; i < grades.size(); i++) {
				if (grades[i].getStudentID() == sid && grades[i].getCourseCode() == ccode) {
					grades.erase(grades.begin() + i); // Remove from dynamic array

					// Rewrite the file without the deleted record
					ofstream outFile("grades.txt");
					for (int k = 0; k < grades.size(); k++) {
						outFile << grades[k].getStudentID() << "|" << grades[k].getCourseCode() << "|"
							<< grades[k].getMidterm() << "|" << grades[k].getFinalExam() << endl;
					}
					outFile.close();
					cout << "Deleted." << endl;
					found = true;
					break;
				}
			}
			if (!found) cout << "Grade record not found." << endl;
			break;
		}
		case 5: { // CALCULATE WEIGHTED GPA
			string sid;
			cout << "Enter Student ID to calculate GPA: ";
			cin >> sid;

			double totalPoints = 0;
			int totalCredits = 0;
			bool foundAny = false;

			for (int i = 0; i < grades.size(); i++) {
				if (grades[i].getStudentID() == sid) {
					foundAny = true;
					int credits = 0;

					// Cross-reference the courses vector to dynamically fetch the Credit Hours
					for (int j = 0; j < courses.size(); j++) {
						if (courses[j].getCourseCode() == grades[i].getCourseCode()) {
							credits = courses[j].getCreditHours();
							break;
						}
					}

					// Calculate points for this specific course
					int totalMark = grades[i].getTotalGrade();
					double points = getGPAPoints(totalMark);

					// Accumulate weighted points and total credits for the GPA formula
					totalPoints += (points * credits);
					totalCredits += credits;
				}
			}

			if (!foundAny) {
				cout << "No grades found for this student." << endl;
			}
			else if (totalCredits > 0) {
				double finalGPA = totalPoints / totalCredits; // Standard GPA formula
				cout << "--------------------------------\n";
				cout << "Total Credit Hours: " << totalCredits << endl;
				cout << fixed << setprecision(2); // Locks GPA output to exactly 2 decimal places
				cout << "Semester GPA:       " << finalGPA << endl;
				cout << "--------------------------------\n";

				// Update the Student's personal record with their new GPA
				for (int k = 0; k < students.size(); k++) {
					if (students[k].getstudentid() == sid) {
						students[k].setgpa(finalGPA);
						break;
					}
				}

				// Save the updated student record to students.txt to ensure cross-module persistence
				ofstream outFile("students.txt");
				for (int k = 0; k < students.size(); k++) {
					outFile << students[k].getname() << "|"
						<< students[k].getstudentid() << "|"
						<< students[k].getNationalID() << "|"
						<< students[k].getphone() << "|"
						<< students[k].getprogram() << "|"
						<< students[k].getgender() << "|"
						<< students[k].getGPA() << "|"
						<< students[k].getlevel() << "|"
						<< students[k].getday() << "|"
						<< students[k].getmonth() << "|"
						<< students[k].getyear() << endl;
				}
				outFile.close();
				cout << "Student GPA automatically updated in database!" << endl;
			}
			break;
		}
		case 6: { // GENERATE FORMATTED TRANSCRIPT
			string sid;
			cout << "Enter Student ID for Transcript: ";
			cin >> sid;

			// Retrieve the target student's demographic info using a pointer
			Student* targetStudent = nullptr;
			for (int i = 0; i < students.size(); i++) {
				if (students[i].getstudentid() == sid) {
					targetStudent = &students[i];
					break;
				}
			}

			if (targetStudent == nullptr) {
				cout << "Student not found in system." << endl;
				break;
			}

			// Print the official transcript header using the retrieved student data
			cout << "\n=================================================================\n";
			cout << "                       OFFICIAL TRANSCRIPT                       \n";
			cout << "=================================================================\n";
			cout << "Student Name: " << targetStudent->getname() << "\n";
			cout << "Student ID:   " << targetStudent->getstudentid() << "\n";
			cout << "Program:      " << targetStudent->getprogram() << "\n";
			cout << "-----------------------------------------------------------------\n";

			// Setup tabular columns using <iomanip> for consistent spacing
			cout << left << setw(12) << "Course" << "| "
				<< setw(25) << "Course Name" << "| "
				<< setw(8) << "Credits" << "| "
				<< setw(6) << "Total" << "| "
				<< "Grade\n";
			cout << "-----------------------------------------------------------------\n";

			double totalPoints = 0;
			int totalCredits = 0;
			bool foundAny = false;

			// Iterate through all grades to build the transcript body
			for (int i = 0; i < grades.size(); i++) {
				if (grades[i].getStudentID() == sid) {
					foundAny = true;
					string cName = "Unknown";
					int credits = 0;

					// Fetch dynamic course data (Name and Credits) for the current grade
					for (int j = 0; j < courses.size(); j++) {
						if (courses[j].getCourseCode() == grades[i].getCourseCode()) {
							cName = courses[j].getCourseName();
							credits = courses[j].getCreditHours();
							break;
						}
					}

					int totalMark = grades[i].getTotalGrade();
					double points = getGPAPoints(totalMark);

					// Print the individual course row formatted to align with the headers
					cout << left << setw(12) << grades[i].getCourseCode() << "| "
						<< setw(25) << cName << "| "
						<< setw(8) << credits << "| "
						<< setw(6) << totalMark << "| "
						<< getLetter(totalMark) << "\n";

					// Accumulate values for the final Cumulative GPA
					totalPoints += (points * credits);
					totalCredits += credits;
				}
			}
			cout << "-----------------------------------------------------------------\n";

			// Print final transcript footer with calculated CGPA
			if (foundAny && totalCredits > 0) {
				double finalGPA = totalPoints / totalCredits;
				cout << "Total Credits Attempted: " << totalCredits << "\n";
				cout << fixed << setprecision(2);
				cout << "Cumulative GPA:          " << finalGPA << "\n";

				// Update Student Vector memory with the calculated CGPA
				targetStudent->setgpa(finalGPA);

				// Persist the updated CGPA to the database
				ofstream outFile("students.txt");
				for (int k = 0; k < students.size(); k++) {
					outFile << students[k].getname() << "|"
						<< students[k].getstudentid() << "|"
						<< students[k].getNationalID() << "|"
						<< students[k].getphone() << "|"
						<< students[k].getprogram() << "|"
						<< students[k].getgender() << "|"
						<< students[k].getGPA() << "|"
						<< students[k].getlevel() << "|"
						<< students[k].getday() << "|"
						<< students[k].getmonth() << "|"
						<< students[k].getyear() << endl;
				}
				outFile.close();

			}
			else {
				cout << "No grades registered for this student yet.\n";
			}
			cout << "=================================================================\n";
			break;
		}
		case 7: { // EXIT
			cout << "Exiting Grades Management." << endl;
			done = true;
			break;
		}
		default: {
			cout << "Invalid option. Please try again." << endl;
			break;
		}
		}
	}
}