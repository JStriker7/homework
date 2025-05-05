#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

class Date {
private:
    int day;   // ����
    int month; // �·�
    int year;  // ���

public:
    Date(int year = 2000, int month = 1, int day = 1); // Ĭ�Ϲ��캯��

    // �������ڵ��ַ�����ʽ����ʽΪ "YYYY-MM-DD"
    std::string toString() const;

    // ������������֮���������
    int daysBetween(const Date& otherDate) const;
    int totalDays() const;
    // ��ȡ������
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    //����֮��ʾ����
    void show() const
    {
        std::cout << year << "-" << month << "-" << day;
    }

    //��ȡ�����������
    int getMaxDay() const {
        static const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int maxDay = daysInMonth[month];
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
            maxDay = 29;  // ����2��
        return maxDay;
    }
};

#endif
