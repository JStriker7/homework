#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QWidget>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_registerBtn_clicked();

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
