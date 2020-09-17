#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Student.h"

using namespace std;

Student::Student(string student_id, string name) : id(student_id), name(name) {}

string Student::get_id() {return id; }

string Student::get_name() { return name; }

void Student::addCourse(string course_id) {
	course_ids.push_back(course_id);
}

void Student::listCourses() {
	cout << "Courses for " << get_id() << endl;
	for (unsigned int i = 0; i < course_ids.size(); i++) {
		cout << course_ids.at(i) << endl;
	}
}
