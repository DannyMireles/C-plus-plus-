#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "School.h"
#include "Date.h"

using namespace std;

void printMenu() {
  cout << "--------------------------------------------------" << endl;
  cout << " '1': Load Courses" << endl;
  cout << " '2': Load Students" << endl;
  cout << " '3': Load Attendance File" << endl;
  cout << " '4': Output Attendance for Student in Course" << endl;
  cout << " '5': Output Course Attendance" << endl;
  cout << " '6': List Courses" << endl;
  cout << " '7': List Students" << endl;
  cout << " 'Q': Quit" << endl;
  cout << "--------------------------------------------------" << endl;
  cout << endl << "Please enter your choice: ";
}

void processLoadCourses(School& school) {
  string filename;
  cout << "Please enter filename: ";
  cin >> filename;
  school.addCourses(filename);
}

void processLoadStudents(School& school) {
  string filename;
  cout << "Please enter filename: ";
  cin >> filename;
  school.addStudents(filename);
}

void processLoadAttendance(School& school) {
  string filename;
  cout << "Please enter filename: ";
  cin >> filename;
  school.addAttendanceData(filename);
}

void processOutputAttendanceStudent(School& school) {
  string studentID, courseID;
  cout << "Please enter student UIN: ";
  cin >> studentID;
  cout << "Please enter course id: ";
  cin >> courseID;
  school.outputStudentAttendance(studentID, courseID);
}

void processOutputAttendanceCourse(School& school) {
  string courseID;
  cout << "Please enter course id: ";
  cin >> courseID;
  school.outputCourseAttendance(courseID);
}

int main() {   
  School school;
  char choice = 'a';
  
  do {
    printMenu();
    cin >> choice;
    switch (tolower(choice)) {
      case '1': processLoadCourses(school); break;
      case '2': processLoadStudents(school); break;
      case '3': processLoadAttendance(school); break;
      case '4': processOutputAttendanceStudent(school); break;
      case '5': processOutputAttendanceCourse(school); break;
      case '6': school.listCourses(); break;
      case '7': school.listStudents(); break;
      case 'q': break; // do nothing
      default:
        cout << choice << " is an invalid option. Please try again." << endl;
    }
  } while (tolower(choice) != 'q');
}

