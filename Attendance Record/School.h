#ifndef SCHOOL_H
#define SCHOOL_H

#include <string>
#include <vector>
#include "Course.h"
#include "Student.h"

class School {
  std::vector<Course> courses;
  std::vector<Student> students;
  
public:
  void addCourses(std::string filename);
  void addStudents(std::string filename);
  void addAttendanceData(std::string filename);
  void listCourses();
  void listStudents();
  void outputCourseAttendance(std::string course_id);
  void outputStudentAttendance(std::string student_id, std::string course_id);
};

#endif