#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTextCursor>
#include <QRegularExpression>
#include <algorithm>





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct res
{// 这个词在第几个字符的位置
    int pos;
    // 搜的是什么词
    QString word;
    int row;        // 在表格第几行
    int file;       // 在第几个文件里找到的
};


struct book
{
    QString path;
    // 文件在哪里
    QString name;
    // 书叫什么名字
    QString txt;
    // 书的全部内容
    bool ok;
    // 有没有成功读到
};

// 章节信息
struct chap
{    int pos;
    QString name;
    QString show;   // 显示的时候叫什么（比如第1章）
};

// 页码信息 - 记录页码位置
struct page
{ // 这个页码在第几个字符
    int pos;
    // 页码数字
    int num;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void search();     // 点搜索按钮时调用
    void click(QTableWidgetItem *item);      // 点击表格某一行时调用

private:  // 私有成员变量和函数
    Ui::MainWindow *ui;
    QString txt;
    QList<res> results;
    QList<book> books;






    void test();                                           // 试试读一个文件
    void load();

    // 读文件（备用）
    void loadall();                                       // 把所有书都读进来
    void dosearch(const QString &word);                   // 执行搜索
    void showctx(int pos, const QString &word, int file); // 显示上下文



    QList<chap> getchap(const QString &txt, int file);   // 从文本里提取章节
    QList<page> getpage(const QString &txt);
    // 从文本里提取页码
    QString findchap(int pos, const QList<chap> &chaps); // 根据位置找章节



    int findpage(int pos, const QList<page> &pages);     // 根据位置找页码
    QString conv(const QString &name);                    // 把英文章节名转成中文
};

#endif // MAINWINDOW_H
