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
};

#endif
