#include <string>
#include "AttendanceRecord.h"
#include "Date.h"

using namespace std;

AttendanceRecord::AttendanceRecord(string course_id, string student_id, Date time) : course_id(course_id), student_id(student_id), time(time) {}

string AttendanceRecord::getCourseID() { return course_id; }
string AttendanceRecord::getStudentID() { return student_id; }

Date AttendanceRecord::getDate() { return time; }