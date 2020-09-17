#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include "Date.h"

using namespace std;

Date::Date(int year, int month, int day, int hour, int min, int sec) :
    year(year), month(month), day(day), hour(hour), min(min), sec(sec) {}
    
Date::Date(int hour, int min, int sec) 
  : timestamp(0), year(0), month(0), day(0), 
    hour(hour), min(min), sec(sec) {}

string Date::getDateTime() const {
  stringstream ss;
  ss << month << "/" << day << "/" << year << " ";
  ss << setw(2) << setfill('0') << hour << ":"; 
  ss << setw(2) << setfill('0') << min << ":";
  ss << setw(2) << setfill('0') << sec;
  return ss.str();
}

string Date::getDate() const {
  stringstream ss;
  ss << month << "/" << day << "/" << year;
  return ss.str();
}

string Date::getTime(bool withSeconds) const {
  stringstream ss;
  ss << setw(2) << setfill('0') << hour << ":"; 
  ss << setw(2) << setfill('0') << min;
  if (withSeconds)
    ss << ":" << setw(2) << setfill('0') << sec;
  return ss.str();
}

bool Date::operator<(const Date& rhs) const {
    if (this->hour < rhs.hour)
        return true;
    if (this->hour > rhs.hour)
        return false;
    if (this->min < rhs.min)
        return true;
    if (this->min > rhs.min)
        return false;
    return this->sec < rhs.sec;
}

bool Date::operator>(const Date& rhs) const {
    return rhs < *this;
}

bool Date::operator<=(const Date& rhs) const {
    return !(*this > rhs);
}

bool Date::operator>=(const Date& rhs) const {
    return !(*this < rhs);
}