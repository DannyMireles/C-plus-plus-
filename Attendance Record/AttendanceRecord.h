#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <string>
#include "Date.h"

class AttendanceRecord {
  std::string course_id;
  std::string student_id;
  Date time;

public:
  AttendanceRecord(std::string course_id, std::string student_id, Date time);
  std::string getCourseID();
  std::string getStudentID();
  Date getDate();
};

#endif