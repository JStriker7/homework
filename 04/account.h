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
   //���麯���ӿ�
   virtual void deposit(Date date, double amount, std::string desc) = 0;
   virtual void withdraw(Date date, double amount, std::string desc) = 0;
   virtual void settle(Date date) = 0;
   virtual void show() const= 0;
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

    void show() const;
  
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

    void deposit(Date date, double amount, std::string description);

    void withdraw(Date date, double amount, std::string description);

    void settle(Date date);

    static double getTotal();

    void show() const;

    // �ۼӼ���
    double accumulate(Date date);
   


};

#endif
