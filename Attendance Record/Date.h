#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
  long timestamp;

  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
  
public:
  Date(int year, int month, int day, int hour, int min, int sec);
  Date(int hour, int min, int sec=0); 
  int getYear() const { return year; }
  int getMonth() const { return month; }
  int getDay() const { return day; }
  int getHour() const { return hour; }
  int getMin() const { return min; }
  int getSec() const { return sec; }
  std::string getDateTime() const;
  std::string getDate() const;
  std::string getTime(bool withSeconds=true) const;
  bool operator<(const Date& d) const;
  bool operator>(const Date& d) const;
  bool operator<=(const Date& d) const;
  bool operator>=(const Date& d) const;
};

#endif