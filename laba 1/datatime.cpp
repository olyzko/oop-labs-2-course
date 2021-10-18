#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include "datatime.h"

bool DataTime::parseInput (const std::string &input) {
    if (input[2] != '.' || input[5] != '.' || input[10] != ' ' || input[13] != ':' || input[16] != ':')
        return false;
    std::string dayStr = input.substr(0, 2);
    int dayInt = std::stoi(dayStr);
    setDay(dayInt);
    std::string monthStr = input.substr(3, 2);
    int monthInt = std::stoi(monthStr);
    setMonth(monthInt);
    std::string yearStr = input.substr(6, 4);
    int yearInt = std::stoi(yearStr);
    setYear(yearInt);
    std::string hourStr = input.substr(11, 2);
    int hourInt = std::stoi(hourStr);
    setHour(hourInt);
    std::string minuteStr = input.substr(14, 2);
    int minuteInt = std::stoi(minuteStr);
    setMinute(minuteInt);
    std::string secondStr = input.substr(16, 2);
    int secondInt = std::stoi(secondStr);
    setSecond(secondInt);

    return true;
}

std::string monthName (int month) {
    switch (month) {
        case 1: return "January";
        case 2: return "February";
        case 3: return "March";
        case 4: return "April";
        case 5: return "May";
        case 6: return "June";
        case 7: return "July";
        case 8: return "August";
        case 9: return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";

        default: return "";
    }
}

bool isLeap (int y) {
    if (y % 4 != 0)
        return false;
    if (y % 100 == 0 && y % 400 != 0)
        return false;

    return true;
}

bool DataTime::isGregorian () {
    if (hour > 23 || minute > 59 || second > 59 || month > 12)
        return false;
    if (day > monthDays[month])
        if (month != 2 || day != 29 || !isLeap(year))
            return false;

    return true;
}

long DataTime::yeartoDays () {
    long res = year * 365 + year/4 - year/100 + year/400;
    for (int i=1; i<month; i++)
        res += monthDays[i];
    res += day;

    return res;
}

std::string DataTime::weekday() {
    int tempMonth, tempYear;
    if (month == 1) {
        tempMonth = 13;
        tempYear--;
    }
    if (month == 2) {
        tempMonth = 14;
        tempYear--;
    }
    int q = day;
    int m = tempMonth;
    int k = tempYear % 100;
    int j = tempYear / 100;
    int h
            = q + 13 * (m + 1) / 5 + k + k / 4 +
              j / 4 + 5 * j;
    h = h % 7;
    switch (h) {
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";

        default: return "";
    }
}

int DataTime::weekNumber() {
    std::map<std::string, int> map2 = { { "Monday" ,1 }, { "Tuesday" , 2},{"Wednesday",3},{"Thursday",4},{"Friday",5},{"Saturday",6},{"Sunday",7} };
    long a = 0;
    for (int i=1; i<month; i++)
        a += monthDays[i];
    if (isLeap(year))
        a++;
    a += day;
    a -= map2[weekday()];
    return a / 7+1;
}

std::string DataTime::altDay () {
    std::string res;
    res += day%7;
    if (res == "1")
        res += "st ";
    else if (res == "2")
        res += "nd ";
    else if (res == "3")
        res += "rd ";
    else res += "th ";

    res += weekday();
    res += " of ";
    res += monthName(month);

    return res;
}

bool operator > (const DataTime &d1, const DataTime &d2) {
    if(d1.year >= d2.year){
        if(d1.month >= d2.month){
            if(d1.day >= d2.day){
                if(d1.hour >= d2.hour) {
                    if (d1.minute >= d2.minute) {
                        if (d1.second > d2.second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

bool operator < (const DataTime &d1, const DataTime &d2) {
    if(d1.year <= d2.year){
        if(d1.month <= d2.month){
            if(d1.day <= d2.day){
                if(d1.hour <= d2.hour) {
                    if (d1.minute <= d2.minute) {
                        if (d1.second < d2.second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

bool operator == (const DataTime &d1, const DataTime &d2) {
    if(d1.year == d2.year){
        if(d1.month == d2.month){
            if(d1.day == d2.day){
                if(d1.hour == d2.hour) {
                    if (d1.minute == d2.minute) {
                        if (d1.second == d2.second) {
                            return true;
                        } else return false;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

bool operator != (const DataTime &d1, const DataTime &d2) {
    return !(d1 == d2);
}

bool operator >= (const DataTime &d1, const DataTime &d2) {
    return !(d1 < d2);
}

bool operator <= (const DataTime &d1, const DataTime &d2) {
    return !(d1 > d2);
}

DataTime operator - (const DataTime &d1, const DataTime &d2) {
    DataTime diff;
    DataTime temp1 = d1, temp2 = d2;
    if (temp1.second < temp2.second) {
        temp1.second += 60;
        temp1.minute--;
    }
    if (temp1.minute < temp2.minute) {
        temp1.minute += 60;
        temp1.hour--;
    }
    if (temp1.hour < temp2.hour) {
        temp1.hour += 24;
        temp1.day--;
    }

    if (temp1.day < temp2.day) {
        temp1.day += temp1.monthDays[temp1.month];
        if (isLeap(temp1.year))
            temp1.day++;
        temp1.month--;
    }
    if (temp1.month < temp2.month) {
        temp1.month += 12;
        temp1.year--;
    }
    diff.second = temp1.second - temp2.second;
    diff.minute = temp1.minute - temp2.minute;
    diff.hour = temp1.hour - temp2.hour;
    diff.day = temp1.day - temp2.day;
    diff.month = temp1.month - temp2.month;
    diff.year = temp1.year - temp2.year;

    return diff;
}

DataTime operator + (const DataTime &d1, const DataTime &d2) {
    DataTime temp1 = d1, temp2 = d2;
    if (temp1.second + temp2.second >= 60) {
        temp1.second -= 60;
        temp1.minute++;
    }
    if (temp1.minute + temp2.minute >= 60) {
        temp1.minute -= 60;
        temp1.hour++;
    }
    if (temp1.hour + temp2.hour >= 60) {
        temp1.hour -= 60;
        temp1.day++;
    }
    if (temp1.month + temp2.month > 12) {
        temp1.month -= 12;
        temp1.year++;
    }

    if (temp1.day + temp2.day >= temp1.monthDays[temp1.month + temp2.month - 1]) {
        temp1.day -= temp2.monthDays[temp2.month - 1];
        if (isLeap(temp1.year) && temp1.monthDays[temp1.month] == 28)
            temp1.day++;
        temp1.month++;
    }
    DataTime sum {temp1.year + temp2.year, temp1.month + temp2.month, temp1.day + temp2.day, temp1.hour + temp2.hour, temp1.minute + temp2.minute, temp1.second + temp2.second};

    return sum;
}

std::ostream& operator << (std::ostream &os, const DataTime &d1) {
    if (d1.year != 0)
        os << d1.year <<" years ";
    if (d1.month != 0)
        os << d1.month << " months ";
    if (d1.day != 0)
        os << d1.day << " days ";
    if (d1.hour != 0)
        os << d1.hour << " hours ";
    if (d1.minute != 0)
        os << d1.minute << " minutes ";
    if (d1.second != 0)
        os << d1.second << " seconds";

    return os;
}

DataTime DataTime::catholicEaster() const {
    DataTime easterDay;
    easterDay.setYear(year);
    easterDay.setHour(0);
    easterDay.setMinute(0);
    easterDay.setSecond(0);
    double A, B, C, P, Q,
            M, N, D, E;

    A = year % 19;
    B = year % 4;
    C = year % 7;
    P = (double)floor(year / 100);
    Q = (double)floor((13 + 8 * P) / 25);
    M = (int)(15 - Q + P - P / 4) % 30;
    N = (int)(4 + P - P / 4) % 7;
    D = (int)(19 * A + M) % 30;
    E = (int)(2 * B + 4 * C + 6 * D + N) % 7;
    auto days = (int )(22 + D + E);

    if ((D == 29) && (E == 6)) {
        easterDay.setMonth(4);
        easterDay.setDay(19);
        return easterDay;
    }
    else if ((D == 28) && (E == 6)) {
        easterDay.setMonth(4);
        easterDay.setDay(19);
        return easterDay;
    }
    else {
        if (days > 31) {
            easterDay.setMonth(4);
            easterDay.setDay(days - 31);
            return easterDay;
        }
        else {
            easterDay.setMonth(3);
            easterDay.setDay(days);
            return easterDay;
        }
    }
}

DataTime DataTime::orthodoxEaster() const {
    DataTime easterDay;
    easterDay.setYear(year);
    easterDay.setHour(0);
    easterDay.setMinute(0);
    easterDay.setSecond(0);
    double A, B, C, D, E;
    int M = 15, N = 6, P;

    A = year % 19;
    B = year % 4;
    C = year % 7;
    D = (int)(19 * A + M) % 30;
    E = (int)(2 * B + 4 * C + 6 * D + N) % 7;
    P = 10 + (year/100 - 16 + year/400);
    auto days = (int )(22 + D + E + P);

    if (days > 61) {
        easterDay.setMonth(5);
        easterDay.setDay(days - 61);
    }
    if (days > 31) {
        easterDay.setMonth(4);
        easterDay.setDay(days - 31);
    }
    else {
        easterDay.setMonth(3);
        easterDay.setDay(days);
    }
    return easterDay;
}


