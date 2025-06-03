#include "date.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

// Ĭ�Ϲ��캯��
Date::Date(int year, int month, int day) : day(day), month(month), year(year) {}

// ת������Ϊ�ַ�����ʽ "YYYY-MM-DD"
std::string Date::toString() const {
    stringstream ss;
    ss << year << "-" << month << "-" <<  day;
    return ss.str();
}

// ������������֮���������
int Date::daysBetween(const Date& other) const {
    // ���㵱ǰ���ڵ���Ԫ1��1��1�յ�������
    int days1 = totalDays();
    int days2 = other.totalDays();
    return days2 - days1;  // ֱ������õ�������
}
bool isLeapYear(int year) {
    
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return true;  // ����
    }
    else {
        return false; // ��������
    }
}
// �������������㵱ǰ���ڵ���Ԫ1��1��1�յ�������
int Date::totalDays() const {
    static const int daysInMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int days = day;
    for (int y = 1; y < year; y++)
        days += isLeapYear(y) ? 366 : 365;  // �ۼ����
    for (int m = 1; m < month; m++) {
        days += daysInMonth[m];
        if (m == 2 && isLeapYear(year)) days += 1;  // ����2�¼�1��
    }
    return days;
}

// ��ȡ��
int Date::getDay() const {
    return day;
}

// ��ȡ��
int Date::getMonth() const {
    return month;
}

// ��ȡ��
int Date::getYear() const {
    return year;
}
