//
// Created by mihan on 03.10.2021.
//

#ifndef LABA_1_DATATIME_H
#define LABA_1_DATATIME_H


class DataTime {
private:
    int year;
    short month;
    short day;
    short hour;
    short minute;
    short second;

    const int monthDays[12]
            = { 31, 28, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31 };

public:
    void setYear (int Year) {year = Year;}
    void setMonth (short int Month) {month = Month;}
    void setDay (short int Day) {day = Day;}
    void setHour (short int Hour) {hour = Hour;}
    void setMinute (short int Minute) {minute = Minute;}
    void setSecond (short int Second) {second = Second;}

    const int* getMonthDays () {return monthDays;}

    bool parseInput (const std::string &input);

    bool isGregorian (DataTime data);

    friend bool operator > (const DataTime &d1, const DataTime &d2);
    friend bool operator < (const DataTime &d1, const DataTime &d2);
    friend bool operator >= (const DataTime &d1, const DataTime &d2);
    friend bool operator <= (const DataTime &d1, const DataTime &d2);
    friend bool operator == (const DataTime &d1, const DataTime &d2);
    friend bool operator != (const DataTime &d1, const DataTime &d2);
    friend DataTime operator - (const DataTime &d1, const DataTime &d2);
    friend DataTime operator + (const DataTime &d1, const DataTime &d2);


};

#endif //LABA_1_DATATIME_H
