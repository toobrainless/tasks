#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Date {
    static inline const std::vector<int> day_in_month =
            {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    static inline const std::vector<int> day_in_month_leap =
            {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


private:
    int day;
    int month;
    int year;

public:
    Date(int day, int month, int year) : day(day), month(month), year(year) {
        if (year < 0) {
            throw std::invalid_argument("invalid argument");
        }

        if (month > 12 || month < 0) {
            throw std::invalid_argument("invalid argument");
        }

        if (((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
            && (day > day_in_month_leap[month - 1] || day < 0)) {
            throw std::invalid_argument("invalid argument");
        }

        if (day > day_in_month[month - 1] || day < 0) {
            throw std::invalid_argument("invalid argument");
        }
    }

    int DateToDays() const {
        int days = ((year - 1600) / 400) * 146097 + ((year - 1600) % 400) / 100 * 36524 +
                   (((year - 1600) % 100) / 4) * 1461 + ((year - 1600) % 4) * 365 + 1;

        if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
            --days;
        }

        for (int i = 1; i < month; ++i) {
            days += day_in_month[i - 1];
        }

        days += day - 1;

        if (month > 2 && ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))) {
            ++days;
        }

        return days;
    }

    Date& operator++ () {
        if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
            ++day;
            if (day > day_in_month_leap[month - 1]) {
                day = 1;
                ++month;
            }
            if (month > 12) {
                month = 1;
                ++year;
            }
        } else {
            ++day;
            if (day > day_in_month[month - 1]) {
                day = 1;
                ++month;
            }
            if (month > 12) {
                month = 1;
                ++year;
            }
        }
        return *this;
    }

    Date& operator-- () {
        --day;
        if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
            if (day == 0) {
                --month;
                if (month == 0) {
                    --year;
                    month = 12;
                    day = 31;
                } else {
                    day = day_in_month_leap[month - 1];
                }
            }
        } else {
            if (day == 0) {
                --month;
                if (month == 0) {
                    --year;
                    month = 12;
                    day = 31;
                } else {
                    day = day_in_month[month - 1];
                }
            }
        }
        return *this;
    }

    friend Date operator+ (const Date& lhs, int rhs) {
        auto temp = lhs;
        while (rhs > 0) {
            ++temp;
            --rhs;
        }

        return temp;
    }

    friend Date operator+ (int rhs, const Date& lhs) {
        auto temp = lhs;
        while (rhs > 0) {
            ++temp;
            --rhs;
        }

        return temp;
    }

    friend Date operator- (const Date& lhs, int rhs) {
        auto temp = lhs;
        while (rhs > 0) {
            --temp;
            --rhs;
        }

        return temp;
    }

    friend Date operator- (int rhs, const Date& lhs) {
        auto temp = lhs;
        while (rhs > 0) {
            --temp;
            --rhs;
        }

        return temp;
    }

    friend int operator- (const Date& lhs, const Date& rhs) {
        return (lhs.DateToDays() - rhs.DateToDays());
    }

    int GetDay() const {
        return day;
    }

    int GetMonth() const {
        return month;
    }

    int GetYear() const {
        return year;
    }
};
