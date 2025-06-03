#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

class Date {
private:
    int day;   // 天数
    int month; // 月份
    int year;  // 年份

public:
    Date(int year = 2000, int month = 1, int day = 1); // 默认构造函数

    // 返回日期的字符串形式，格式为 "YYYY-MM-DD"
    std::string toString() const;

    // 计算两个日期之间的天数差
    int daysBetween(const Date& otherDate) const;
    int totalDays() const;
    // 获取年月日
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    //新增之显示日期
    void show() const
    {
        std::cout << year << "-" << month << "-" << day;
    }

    //获取当月最大天数
    int getMaxDay() const {
        static const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int maxDay = daysInMonth[month];
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
            maxDay = 29;  // 闰年2月
        return maxDay;
    }
};

#endif
