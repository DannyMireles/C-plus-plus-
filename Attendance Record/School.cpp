#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "School.h"
#include "AttendanceRecord.h"

using namespace std;

void School::addCourses(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);    
    stringstream ss(line);
    string id;
    string startHour;
    string startMinute;
	
    int startHourInt;
    int startMinuteInt;
    int startSeconds = 0;
	
    string endHour;
    string endMinute;
	
    int endHourInt;
    int endMinuteInt;
    int endSeconds = 0;
	
    string title;
    getline(ss, id, ',');
    getline(ss, startHour, ':');
    getline(ss, startMinute, ',');
    getline(ss, endHour, ':');
    getline(ss, endMinute, ',');
    getline(ss, title); 

    stringstream tempStartHour(startHour);
    stringstream tempStartMinute(startMinute);
	
    tempStartHour >> startHourInt;
    tempStartMinute >> startMinuteInt;
	
    stringstream tempEndHour(endHour);
    stringstream tempEndMinute(endMinute);
	
    tempEndHour >> endHourInt;
    tempEndMinute >> endMinuteInt;

    Date startTime(startHourInt, startMinuteInt, startSeconds);
    Date endTime(endHourInt, endMinuteInt, endSeconds);

    if (!ss.fail()) {
      courses.push_back(Course(id, title, startTime, endTime));
    }
  }
}

void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
      students.push_back(Student(uin, name));
    }
  }
}  

void School::addAttendanceData(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
  }
  while (!ifs.eof()) {
	  
    string line;
    getline(ifs, line);
    stringstream ss(line);
    string year, month, day, hour, minute, second, course_id, student_id;
    int yearInt = 0, monthInt = 0, dayInt = 0, hourInt = 0, minuteInt = 0, secondInt = 0;

    getline(ss, year, '-');
    getline(ss, month, '-');
    getline(ss, day, ' ');
    getline(ss, hour, ':');
    getline(ss, minute, ':');
    getline(ss, second, ',');

    stringstream tempYear(year);
    stringstream tempMonth(month);
    stringstream tempDay(day);
    stringstream tempHour(hour);
    stringstream tempMinute(minute);
    stringstream tempSecond(second);
	
    tempYear >> yearInt;
    tempMonth >> monthInt;
    tempDay >> dayInt;
    tempHour >> hourInt;
    tempMinute >> minuteInt;
    tempSecond >> secondInt;

    Date courseDateTime(yearInt, monthInt, dayInt, hourInt, minuteInt, secondInt);

    getline(ss, course_id, ',');
    getline(ss, student_id);

    if (!ss.fail()) { 
      for (unsigned int i = 0; i < courses.size(); ++i) {
        if (courses.at(i).getID() == course_id) {
          courses.at(i).addAttendanceRecord(AttendanceRecord(course_id, student_id, courseDateTime));
        }
      }
    }

  }
}

void School::listCourses() {
    if(courses.size() == 0) {
    cout << "No Courses" << endl;
  }
  else {
    for (unsigned int i = 0; i < courses.size(); ++i) {    
      cout << courses.at(i).getID() << ",";

      if (courses.at(i).getStartTime().getHour() < 10) {
        cout << "0" << courses.at(i).getStartTime().getHour() << ":";
      }
      else {
        cout << courses.at(i).getStartTime().getHour() << ":";
      }

      if (courses.at(i).getStartTime().getMin() < 10) {
        cout << "0" << courses.at(i).getStartTime().getMin() << ",";
      }
      else {
        cout << courses.at(i).getStartTime().getMin() << ",";
      }

      if (courses.at(i).getEndTime().getHour() < 10) {
        cout << "0" << courses.at(i).getEndTime().getHour() << ":";
      }
      else {
        cout << courses.at(i).getEndTime().getHour() << ":";
      }

      if (courses.at(i).getEndTime().getMin() < 10) {
        cout << "0" << courses.at(i).getEndTime().getMin() << ",";
      }
      else {
        cout << courses.at(i).getEndTime().getMin() << ",";
      }

      cout << courses.at(i).getTitle() << endl;
    }
  }
}

void School::listStudents() {
  if(students.size() == 0) {
    cout << "No Students" << endl;
  }
  else {
    for (unsigned int i = 0; i < students.size(); ++i) {
      string student_id = students.at(i).get_id();
      string name = students.at(i).get_name();
      cout << student_id << "," << name << endl;
    }
  }
}

void School::outputCourseAttendance(string course_id) {
  for (unsigned int i = 0; i < courses.size(); ++i) {
    if (courses.at(i).getID() == course_id) {
      courses.at(i).outputAttendance();
    }
  }
}

void School::outputStudentAttendance(string student_id, string course_id) {
  for (unsigned int i = 0; i < courses.size(); ++i) {
    if (courses.at(i).getID() == course_id) {
      courses.at(i).outputAttendance(student_id);
    }
  }
}