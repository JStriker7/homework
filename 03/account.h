#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "date.h"  // ���� Date ��



class Account
{
protected:
    std::string id;

    
    Date lastDate;
     static double total;
public:
   static  double getTotal();
};

class CreditAccount:public Account
{
private:
  
    double balance;
    double credit;//������
    double rate;//ÿ������
    Date lastDate;
    double fee;//��ѣ�ÿ�궼Ҫ��
    
public:
    CreditAccount(Date date, std::string id, double credit, double rate, double fee);

    void deposit(Date date, double amount, std::string desc);

    void withdraw(Date date, double amount,std:: string desc);

    void settle(Date date);

    void show();
  
};



class SavingsAccount :public Account {
private:
    std::string id;           // �˻�ID
    double balance;           // �˻����
    double rate;              // ������
    Date lastDate;            // �ϴβ�������
    double accumulation;      // �ۻ����
      

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
