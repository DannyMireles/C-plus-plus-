#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using namespace std;

Course::Course(string id, string title, Date startTime, Date endTime) : id(id), title(title), startTime(startTime), endTime(endTime) {}

string Course::getID() { return id; }
string Course::getTitle() { return title; }

Date Course::getStartTime() { return startTime; }
Date Course::getEndTime() { return endTime; }

void Course::addAttendanceRecord(AttendanceRecord ar) {
	attendanceRecords.push_back(ar); // push back attendanceRecords
}

void Course::outputAttendance() {
    int i = 0;
    while (i < attendanceRecords.size()) {
		AttendanceRecord flag = attendanceRecords.at(i);
		if (flag.getCourseID() == id) {
			Date date_flag = flag.getDate(); 
			string date_string = date_flag.getDateTime();
			cout << date_string << "," << flag.getCourseID() << ","; 
			cout << flag.getStudentID() << endl;
		}
	i++;
	}
}

void Course::outputAttendance(string student_id){
	int i = 0;
    bool test = false; // set flag to see if loop was enetered
    while( i < attendanceRecords.size()) {
		AttendanceRecord flag = attendanceRecords.at(i);
		if (flag.getStudentID() == student_id && flag.getCourseID() == id) {
			Date date_flag =flag.getDate();
			string date_string = date_flag.getDateTime();
			cout << date_string << "," << flag.getCourseID() << ",";
			cout << flag.getStudentID() << endl;
			test = true;
		}
		i++;
	}
	if(test == false){
		cout << "No Records" << endl;
		}
}



