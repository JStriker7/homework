/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginBtn;
    QPushButton *gotoRegisterBtn;
    QPushButton *pushButton;

    void setupUi(QWidget *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(400, 300);
        usernameLineEdit = new QLineEdit(LoginDialog);
        usernameLineEdit->setObjectName(QString::fromUtf8("usernameLineEdit"));
        usernameLineEdit->setGeometry(QRect(180, 80, 113, 25));
        passwordLineEdit = new QLineEdit(LoginDialog);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setGeometry(QRect(180, 140, 113, 25));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        loginBtn = new QPushButton(LoginDialog);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));
        loginBtn->setGeometry(QRect(140, 210, 93, 28));
        gotoRegisterBtn = new QPushButton(LoginDialog);
        gotoRegisterBtn->setObjectName(QString::fromUtf8("gotoRegisterBtn"));
        gotoRegisterBtn->setGeometry(QRect(60, 140, 93, 28));
        pushButton = new QPushButton(LoginDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 80, 93, 28));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QWidget *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        loginBtn->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        gotoRegisterBtn->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
