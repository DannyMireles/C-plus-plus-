#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
  std::string id;
  std::string name;
  std::vector<std::string> course_ids;
  
public:
  Student(std::string student_id, std::string name);
  std::string get_id();
  std::string get_name();
  void addCourse(std::string course_id);
  void listCourses();
};

#endif