#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "date.h"  // ���� Date ��

class SavingsAccount {
private:
    std::string id;           // �˻�ID
    double balance;           // �˻����
    double rate;              // ������
    Date lastDate;            // �ϴβ�������
    double accumulation;      // �ۻ����
    static double total;      // �����˻����ܽ��

public:
    // ���캯��
    SavingsAccount(Date startDate, std::string id, double rate);

    // ������
    void deposit(Date date, double amount, std::string description);

    // ȡ�����
    void withdraw(Date date, double amount, std::string description);

    // ������Ϣ
    void settle(Date date);

    // ��ȡ�ܽ��
    static double getTotal();

    // ��ʾ�˻���Ϣ
    void show() const;

    // �ۼӼ���
    double accumulate(Date date);
    void record(const Date& date, double amount, const std::string& desc);
};

#endif
