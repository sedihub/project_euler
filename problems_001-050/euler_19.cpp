/*
PROBLEM:
  You are given the following information, but you may prefer to do some research for yourself.

  - 1 Jan 1900 was a Monday.
  - Thirty days has September, April, June and November.
  - All the rest have thirty-one,
  - Saving February alone, which has twenty-eight, rain or shine, and on leap years, twenty-nine.

  A leap year occurs on any year evenly divisible by 4, but not on a century unless it is 
  divisible by 400. How many Sundays fell on the first of the month during the twentieth century
  (1 Jan 1901 to 31 Dec 2000)?


SOLUTION:
  construct multiple counters and increment days.

  ANSWER: 171 
**/

#include <iostream>
#include <map>
#include <string>
#include <iomanip>  // needed for std::setw(...)


typedef unsigned int uint;


class DateFrom1900
{
public:  
  DateFrom1900() 
  {
    day = 1;
    weekday_number = 1;
    monthday_number = 1;
    month_number = 1;
    year_number = 1900;
    //
    day_names[1] = "Monday";
    day_names[2] = "Tuesday";
    day_names[3] = "Wednesday";
    day_names[4] = "Thursday";
    day_names[5] = "Friday";
    day_names[6] = "Saturday";
    day_names[7] = "Sunday";
    //
    month_names[ 1] = "January";
    month_names[ 2] = "February";
    month_names[ 3] = "March";
    month_names[ 4] = "April";
    month_names[ 5] = "May";
    month_names[ 6] = "June";
    month_names[ 7] = "July";
    month_names[ 8] = "August";
    month_names[ 9] = "September";
    month_names[10] = "October";
    month_names[11] = "November";
    month_names[12] = "December";
    //
    month_length[ 1] = 31;
    month_length[ 2] = 28;
    month_length[ 3] = 31;
    month_length[ 4] = 30;
    month_length[ 5] = 31;
    month_length[ 6] = 30;
    month_length[ 7] = 31;
    month_length[ 8] = 31;
    month_length[ 9] = 30;
    month_length[10] = 31;
    month_length[11] = 30;
    month_length[12] = 31; 
  }

  bool leap_year()
  {
    if ((year_number % 400) == 0)
      return true;
    else if ((year_number % 100) == 0)
      return false; 
    else if ((year_number % 4) == 0)
      return true;
    else
      return false;
  }

  void next_day()
  {
    day++;
    //
    weekday_number++;
    if (weekday_number > 7)
      weekday_number = 1;
    //
    monthday_number++;
    if(!leap_year() || month_number != 2) {
      if (monthday_number > month_length[month_number]) {
        monthday_number = 1;
        month_number++;
        if (month_number > 12) {
          month_number = 1;
          year_number++;
        }
      }
    }
    else {
      if (monthday_number > 29) {
        monthday_number = 1;
        month_number++;
        if (month_number > 12) {
          month_number = 1;
          year_number++;
        }
      }
    }

  }

  void get_date(uint &year, uint &month, uint &day_number, uint &week_day)
  {
    year = year_number;
    month = monthday_number;
    day_number = monthday_number;
    week_day = weekday_number;
  }


  void print_date()
  {
    std::cout << std::setw(10) << day_names[weekday_number] 
          << "," << std::setw(10) << month_names[month_number]
          << std::setw(3) << monthday_number 
          << ", " << year_number << std::endl;
  }

private:
  std::map<uint, std::string> day_names;
  std::map<uint, std::string> month_names;
  std::map<uint, uint> month_length;
  uint day;
  uint weekday_number;
  uint monthday_number;
  uint month_number;
  uint year_number;
};


int main()
{
  DateFrom1900 date;
  uint count_sunday_firsts = 0;
  uint weekday, mothday, month, year;

  date.get_date(year, month, mothday, weekday);
  while (year < 2001) {
    date.get_date(year, month, mothday, weekday);
    if (weekday == 7 && mothday == 1 && year > 1900){
      count_sunday_firsts++;
      date.print_date();
    }
    date.next_day();
  }

  std::cout << std::endl << count_sunday_firsts 
        << " Sundays fall on the first day of the month in the 21st century." 
        << std::endl;

  return 0;
}
