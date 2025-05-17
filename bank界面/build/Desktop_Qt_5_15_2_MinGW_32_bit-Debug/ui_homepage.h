/********************************************************************************
** Form generated from reading UI file 'homepage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomePage
{
public:
    QPushButton *createAccountBtn;
    QComboBox *accountTypeComboBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *amountSortCheckBox;
    QDateEdit *queryDateEdit;
    QPushButton *queryBtn;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *queryStatsBtn;
    QDateEdit *statsDateEdit;
    QLabel *balanceLabel;
    QLineEdit *amountEdit;
    QDateEdit *dateEdit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *repayBtn;
    QPushButton *depositBtn;
    QPushButton *withdrawBtn;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *annualFeeEdit;
    QLineEdit *interestEdit;

    void setupUi(QWidget *HomePage)
    {
        if (HomePage->objectName().isEmpty())
            HomePage->setObjectName(QString::fromUtf8("HomePage"));
        HomePage->resize(616, 526);
        createAccountBtn = new QPushButton(HomePage);
        createAccountBtn->setObjectName(QString::fromUtf8("createAccountBtn"));
        createAccountBtn->setGeometry(QRect(240, 110, 93, 28));
        accountTypeComboBox = new QComboBox(HomePage);
        accountTypeComboBox->setObjectName(QString::fromUtf8("accountTypeComboBox"));
        accountTypeComboBox->setGeometry(QRect(10, 110, 158, 25));
        accountTypeComboBox->setEditable(false);
        gridLayoutWidget = new QWidget(HomePage);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(420, 110, 171, 161));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        amountSortCheckBox = new QCheckBox(gridLayoutWidget);
        amountSortCheckBox->setObjectName(QString::fromUtf8("amountSortCheckBox"));

        gridLayout->addWidget(amountSortCheckBox, 3, 0, 1, 1);

        queryDateEdit = new QDateEdit(gridLayoutWidget);
        queryDateEdit->setObjectName(QString::fromUtf8("queryDateEdit"));
        queryDateEdit->setCalendarPopup(true);

        gridLayout->addWidget(queryDateEdit, 1, 0, 1, 1);

        queryBtn = new QPushButton(gridLayoutWidget);
        queryBtn->setObjectName(QString::fromUtf8("queryBtn"));

        gridLayout->addWidget(queryBtn, 0, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(HomePage);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(409, 310, 171, 80));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        queryStatsBtn = new QPushButton(gridLayoutWidget_2);
        queryStatsBtn->setObjectName(QString::fromUtf8("queryStatsBtn"));

        gridLayout_2->addWidget(queryStatsBtn, 1, 0, 1, 1);

        statsDateEdit = new QDateEdit(gridLayoutWidget_2);
        statsDateEdit->setObjectName(QString::fromUtf8("statsDateEdit"));

        gridLayout_2->addWidget(statsDateEdit, 2, 0, 1, 1);

        balanceLabel = new QLabel(HomePage);
        balanceLabel->setObjectName(QString::fromUtf8("balanceLabel"));
        balanceLabel->setGeometry(QRect(440, 440, 99, 33));
        amountEdit = new QLineEdit(HomePage);
        amountEdit->setObjectName(QString::fromUtf8("amountEdit"));
        amountEdit->setGeometry(QRect(50, 270, 131, 31));
        dateEdit = new QDateEdit(HomePage);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(220, 270, 91, 31));
        dateEdit->setCalendarPopup(true);
        horizontalLayoutWidget = new QWidget(HomePage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(80, 310, 231, 121));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        repayBtn = new QPushButton(horizontalLayoutWidget);
        repayBtn->setObjectName(QString::fromUtf8("repayBtn"));

        horizontalLayout->addWidget(repayBtn);

        depositBtn = new QPushButton(horizontalLayoutWidget);
        depositBtn->setObjectName(QString::fromUtf8("depositBtn"));

        horizontalLayout->addWidget(depositBtn);

        withdrawBtn = new QPushButton(horizontalLayoutWidget);
        withdrawBtn->setObjectName(QString::fromUtf8("withdrawBtn"));

        horizontalLayout->addWidget(withdrawBtn);

        horizontalLayoutWidget_2 = new QWidget(HomePage);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 150, 331, 121));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        annualFeeEdit = new QLineEdit(horizontalLayoutWidget_2);
        annualFeeEdit->setObjectName(QString::fromUtf8("annualFeeEdit"));

        horizontalLayout_2->addWidget(annualFeeEdit);

        interestEdit = new QLineEdit(horizontalLayoutWidget_2);
        interestEdit->setObjectName(QString::fromUtf8("interestEdit"));

        horizontalLayout_2->addWidget(interestEdit);


        retranslateUi(HomePage);

        QMetaObject::connectSlotsByName(HomePage);
    } // setupUi

    void retranslateUi(QWidget *HomePage)
    {
        HomePage->setWindowTitle(QCoreApplication::translate("HomePage", "Form", nullptr));
        createAccountBtn->setText(QCoreApplication::translate("HomePage", "\345\210\233\345\273\272\350\264\246\346\210\267", nullptr));
        amountSortCheckBox->setText(QCoreApplication::translate("HomePage", "\346\214\211\351\207\221\351\242\235\346\216\222\345\272\217", nullptr));
        queryBtn->setText(QCoreApplication::translate("HomePage", "\346\237\245\350\257\242\344\272\244\346\230\223\350\256\260\345\275\225", nullptr));
        queryStatsBtn->setText(QCoreApplication::translate("HomePage", "\347\273\237\350\256\241\346\224\266\346\224\257", nullptr));
        balanceLabel->setText(QCoreApplication::translate("HomePage", "\345\275\223\345\211\215\344\275\231\351\242\235\357\274\2320\345\205\203", nullptr));
        repayBtn->setText(QCoreApplication::translate("HomePage", "\350\277\230\346\254\276", nullptr));
        depositBtn->setText(QCoreApplication::translate("HomePage", "\345\255\230\351\222\261", nullptr));
        withdrawBtn->setText(QCoreApplication::translate("HomePage", "\345\217\226\351\222\261", nullptr));
        annualFeeEdit->setPlaceholderText(QCoreApplication::translate("HomePage", "\350\276\223\345\205\245\345\271\264\350\264\271\357\274\210\344\273\205\344\277\241\347\224\250\350\264\246\346\210\267\357\274\211", nullptr));
        interestEdit->setPlaceholderText(QCoreApplication::translate("HomePage", "\350\276\223\345\205\245\345\210\251\347\216\207\357\274\210%\357\274\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_HomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
