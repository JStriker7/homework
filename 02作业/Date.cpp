#include "date.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

// 默认构造函数
Date::Date(int year, int month, int day) : day(day), month(month), year(year) {}

// 转换日期为字符串格式 "YYYY-MM-DD"
std::string Date::toString() const {
    stringstream ss;
    ss << year << "-" << month << "-" <<  day;
    return ss.str();
}

// 计算两个日期之间的天数差
int Date::daysBetween(const Date& other) const {
    // 计算当前日期到公元1年1月1日的总天数
    int days1 = totalDays();
    int days2 = other.totalDays();
    return days2 - days1;  // 直接相减得到天数差
}
bool isLeapYear(int year) {
    
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return true;  // 闰年
    }
    else {
        return false; // 不是闰年
    }
}
// 辅助函数：计算当前日期到公元1年1月1日的总天数
int Date::totalDays() const {
    static const int daysInMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int days = day;
    for (int y = 1; y < year; y++)
        days += isLeapYear(y) ? 366 : 365;  // 累加年份
    for (int m = 1; m < month; m++) {
        days += daysInMonth[m];
        if (m == 2 && isLeapYear(year)) days += 1;  // 闰年2月加1天
    }
    return days;
}

// 获取天
int Date::getDay() const {
    return day;
}

// 获取月
int Date::getMonth() const {
    return month;
}

// 获取年
int Date::getYear() const {
    return year;
}
