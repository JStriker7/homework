#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "date.h"  // 引入 Date 类

class SavingsAccount {
private:
    std::string id;           // 账户ID
    double balance;           // 账户余额
    double rate;              // 年利率
    Date lastDate;            // 上次操作日期
    double accumulation;      // 累积金额
    static double total;      // 所有账户的总金额

public:
    // 构造函数
    SavingsAccount(Date startDate, std::string id, double rate);

    // 存款操作
    void deposit(Date date, double amount, std::string description);

    // 取款操作
    void withdraw(Date date, double amount, std::string description);

    // 结算利息
    void settle(Date date);

    // 获取总金额
    static double getTotal();

    // 显示账户信息
    void show() const;

    // 累加计算
    double accumulate(Date date);
    void record(const Date& date, double amount, const std::string& desc);
};

#endif
