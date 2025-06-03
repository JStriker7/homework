#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "date.h"  // 引入 Date 类



class Account
{
protected:
    std::string id;
    Date lastDate;
     static double total;
public:
   static  double getTotal();
   //纯虚函数接口
   virtual void deposit(Date date, double amount, std::string desc) = 0;
   virtual void withdraw(Date date, double amount, std::string desc) = 0;
   virtual void settle(Date date) = 0;
   virtual void show() const= 0;
};


class CreditAccount:public Account
{
private:
  
    double balance;
    double credit;//贷款额度
    double rate;//每日利率
    Date lastDate;
    double fee;//年费，每年都要扣
    
public:
    CreditAccount(Date date, std::string id, double credit, double rate, double fee);

    void deposit(Date date, double amount, std::string desc);

    void withdraw(Date date, double amount,std:: string desc);

    void settle(Date date);

    void show() const;
  
};



class SavingsAccount :public Account {
private:
    std::string id;           // 账户ID
    double balance;           // 账户余额
    double rate;              // 年利率
    Date lastDate;            // 上次操作日期
    double accumulation;      // 累积金额
      

public:
    // 构造函数
    SavingsAccount(Date startDate, std::string id, double rate);

    void deposit(Date date, double amount, std::string description);

    void withdraw(Date date, double amount, std::string description);

    void settle(Date date);

    static double getTotal();

    void show() const;

    // 累加计算
    double accumulate(Date date);
   


};

#endif
