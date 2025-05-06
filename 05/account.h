#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "date.h"  // 引入 Date 类
#include<map>

class Account;

class AccountRecord//账目记录
{
private:
    Date date;
    const Account* account;
    double amount;
    double balance;
    std::string desc;
public:
    AccountRecord(const Date& date, const Account* account, double amount, double balance, const std::string& desc)
        : date(date), account(account), amount(amount), balance(balance), desc(desc) {}

    Date& getdate() { return date; }
    const Account* getAccount() { return account; }
    double getAmount() const { return amount; }
    double getBalance() const { return balance; }
    const std::string& getDesc() const { return desc; }
    void show() const;
};

class Account
{
protected:
    std::string id;
    Date lastDate;
     static double total;
     static std::multimap<Date, AccountRecord> recordMap;
public:
   static  double getTotal();
   //纯虚函数接口
   virtual void deposit(Date date, double amount, std::string desc) = 0;
   virtual void withdraw(Date date, double amount, std::string desc) = 0;
   virtual void settle(Date date) = 0;
   virtual void show() const= 0;
   const std::string getId()const
   {
       return id;
   }
   void record(const Date& date, double amount, double balance, const std::string& desc);

   static void query(const Date& day1, const Date& day2);
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
