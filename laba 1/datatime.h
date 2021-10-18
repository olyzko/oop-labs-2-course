#ifndef LABA_1_DATATIME_H
#define LABA_1_DATATIME_H


class DataTime {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    const int monthDays[12]
            = { 31, 28, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31 };

public:
    DataTime() = default;
    DataTime (int Year, int Month, int Day, int Hour, int Minute, int Second) {
        this->year = Year;
        this->month = Month;
        this->day = Day;
        this->hour = Hour;
        this->minute = Minute;
        this->second = Second;
    }

    void setYear (int Year) {year = Year;}
    void setMonth (int Month) {month = Month;}
    void setDay (int Day) {day = Day;}
    void setHour (int Hour) {hour = Hour;}
    void setMinute (int Minute) {minute = Minute;}
    void setSecond (int Second) {second = Second;}

    const int* getMonthDays () {return monthDays;}

    bool parseInput (const std::string &input);

    bool isGregorian ();

    long yeartoDays ();

    std::string weekday();

    int weekNumber();

    std::string altDay ();

    DataTime catholicEaster();

    DataTime orthodoxEaster();

    friend bool operator > (const DataTime &d1, const DataTime &d2);
    friend bool operator < (const DataTime &d1, const DataTime &d2);
    friend bool operator >= (const DataTime &d1, const DataTime &d2);
    friend bool operator <= (const DataTime &d1, const DataTime &d2);
    friend bool operator == (const DataTime &d1, const DataTime &d2);
    friend bool operator != (const DataTime &d1, const DataTime &d2);
    friend DataTime operator - (const DataTime &d1, const DataTime &d2);
    friend DataTime operator + (const DataTime &d1, const DataTime &d2);
    friend std::ostream operator << (std::ostream &os, const DataTime &d1);


};

#endif //LABA_1_DATATIME_H
