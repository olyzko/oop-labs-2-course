#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include "datatime.h"

bool DataTime::parseInput (const std::string &input) {
    if (input[2] != '.' || input[5] != '.' || input[10] != ' ' || input[13] != ':' || input[16] != ':')
        return false;
    std::string dayStr = input.substr(0, 2);
    short dayInt = std::stoi(dayStr);
    setDay(dayInt);
    std::string monthStr = input.substr(3, 2);
    short monthInt = std::stoi(monthStr);
    setMonth(monthInt);
    std::string yearStr = input.substr(6, 4);
    int yearInt = std::stoi(yearStr);
    setYear(yearInt);
    std::string hourStr = input.substr(11, 2);
    short hourInt = std::stoi(hourStr);
    setHour(hourInt);
    std::string minuteStr = input.substr(14, 2);
    short minuteInt = std::stoi(minuteStr);
    setMinute(minuteInt);
    std::string secondStr = input.substr(16, 2);
    short secondInt = std::stoi(secondStr);
    setSecond(secondInt);

    return true;
}

bool isLeap (int y) {
    if (y % 4 != 0)
        return false;
    if (y % 100 == 0 && y % 400 != 0)
        return false;

    return true;
}

bool DataTime::isGregorian (DataTime data) {
    if (data.hour > 23 || data.minute > 59 || data.second > 59 || data.month > 12)
        return false;
    if (data.day > monthDays[month])
        if (data.month != 2 || data.day != 29 || !isLeap(data.year))
            return false;

    return true;
}

long DataTime::yeartoDays (DataTime data) {
    long res = data.year * 365 + data.year/4 - data.year/100 + data.year/400;
    for (int i=1; i<data.month; i++)
        res += data.monthDays[i];
    res += data.day;

    return res;
}

std::string DataTime::weekday(DataTime data) {
    long a = yeartoDays(data);
    int b = ((a - 2) % 7);
    switch (b) {
        case 0:
            return "Sunday";
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
            return "Saturday";
    }
}

int weekNumber(int y, int m, int d) {
    std::map<std::string, int> map2 = { { "Monday" ,1 }, { "Tuesday" , 2},{"Wednesday",3},{"Thursday",4},{"Friday",5},{"Saturday",6},{"Sunday",7} };
    long a = 0;
    if (m >= 2) a += 31;
    if (m >= 3 && (int)y / 4 == y / 4) a += 29;
    else if (m >= 3) a += 28;
    if (m >= 4) a += 31;
    if (m >= 5) a += 30;
    if (m >= 6) a += 31;
    if (m >= 7) a += 30;
    if (m >= 8) a += 31;
    if (m >= 9) a += 31;
    if (m >= 10) a += 30;
    if (m >= 11) a += 31;
    if (m == 12) a += 30;
    a += d;
    a -= map2[weekday(y, m, d)];
    return a / 7+1;
}

DataTime gaussEaster(int y)
{
    DataTime easterDay;
    easterDay.setYear(y);
    easterDay.setHour(0);
    easterDay.setMinute(0);
    easterDay.setSecond(0);
    double A, B, C, P, Q,
            M, N, D, E;

    A = y % 19;
    B = y % 4;
    C = y % 7;
    P = (double)floor(y / 100);
    Q = (double)floor((13 + 8 * P) / 25);
    M = (int)(15 - Q + P - P / 4) % 30;
    N = (int)(4 + P - P / 4) % 7;
    D = (int)(19 * A + M) % 30;
    E = (int)(2 * B + 4 * C + 6 * D + N) % 7;
    auto days = (short )(22 + D + E);

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

template<typename T>
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

template<typename T>
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

template<typename T>
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

template<typename T>
bool operator != (const DataTime &d1, const DataTime &d2) {
    if(d1 == d2)
        return false;
    return true;
}

template<typename T>
bool operator >= (const DataTime &d1, const DataTime &d2) {
    if(d1 < d2)
        return false;
    return true;
}

template<typename T>
bool operator <= (const DataTime &d1, const DataTime &d2) {
    if(d1 > d2)
        return false;
    return true;
}

template<typename T>
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

template<typename T>
DataTime operator + (const DataTime &d1, const DataTime &d2) {
    DataTime sum;
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
    sum.second = temp1.second + temp2.second;
    sum.minute = temp1.minute + temp2.minute;
    sum.hour = temp1.hour + temp2.hour;
    sum.day = temp1.day + temp2.day;
    sum.month = temp1.month + temp2.month;
    sum.year = temp1.year + temp2.year;

    return sum;
}