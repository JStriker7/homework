#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include <QMap>
#include <QString>
#include <QWidget>
#include <QDateTime>
#include <QVector>
#include <QDate>

namespace Ui {
class HomePage;
}

struct Transaction {
    QString username;
    QString accountType;
    double amount;
    QString operation;  // "存款", "取款", "还款"
    QDateTime time;

};

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();
    void setCurrentUser(const QString &username);


private slots:


    void on_createAccountBtn_clicked();

    void on_depositBtn_clicked();

    void on_withdrawBtn_clicked();

    void on_repayBtn_clicked();
    void on_queryBtn_clicked();

    void on_pushButton_clicked();
    void on_queryStatsBtn_clicked();
private:
    Ui::HomePage *ui;
QString currentUser;
    QMap<QString, double> savingsBalances;
    QMap<QString, double> creditBalances;
     QVector<Transaction> transactions;
    void queryTransactionsByMonth(int year, int month, bool sortByAmount = false);
    QString getCurrentAccountType();

    double& getCurrentBalance();
    void updateBalanceUI();
};



#endif // HOMEPAGE_H
