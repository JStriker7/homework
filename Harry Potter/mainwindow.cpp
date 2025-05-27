#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTextCursor>
#include <QRegularExpression>
#include <algorithm>
#include <QElapsedTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList h;
    h << "序号" << "人名/地名" << "页码" << "章节" << "书名";
    ui->resultsTable->setHorizontalHeaderLabels(h);

    books.clear();

    QList<QPair<QString, QString>> data = {
        {":/files/texts/Harry Potter Prequel.txt", "Harry Potter Prequel"},
        {":/files/texts/Harry_Potter_and_the_Chamber_of_Secrets_Book_2.txt", "Harry_Potter_and_the_Chamber_of_Secrets_Book_2"},
        {":/files/texts/Harry Potter and the Prisoner of Azkaban.txt", "Harry Potter and the Prisoner of Azkaban"},
        {":/files/texts/Harry Potter and the Goblet of Fire.txt", "Harry Potter and the Goblet of Fire"},
        {":/files/texts/Harry Potter and the Half-Blood Prince.txt", "Harry Potter and the Half-Blood Prince"},
        {":/files/texts/Harry_Potter_and_the_Chamber_of_Secrets_Book_2.txt", "Harry_Potter_and_the_Chamber_of_Secrets_Book_2"},
        {":/files/texts/Quidditch Through the Ages.txt", "Quidditch Through the Ages"},
        {":/files/texts/The Tales of Beedle the Bard.txt", "The Tales of Beedle the Bard"}
    };

for (const auto &d : data) {
        book b;
        b.path = d.first;
        b.name = d.second;
        b.ok = false;
        books.append(b);
    }

 test();
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::search);
            connect(ui->resultsTable, &QTableWidget::itemClicked, this, &MainWindow::click);
    loadall();
}

MainWindow::~MainWindow() {
    delete ui;
}

// 先随便读一个文件试试手气
void MainWindow::test()
{
    QString file = ":/files/texts/Harry Potter Prequel.txt";
    QFile f(file);

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "打不开文件：" + f.errorString());
        return;
    }

        QTextStream s(&f);
    txt = s.readAll();
    f.close();

QString info;
    info += "试了一下这个文件：\n";
    info += QString("文件名：%1\n字符数：%2\n行数：%3\n预览：\n%4...")
                .arg(file)
                .arg(txt.length())
                .arg(txt.split('\n').count())
                .arg(txt.left(100));

QMessageBox::information(this, "测试结果", info);
}

void MainWindow::load() {
    // 其实就是再调一遍 test()
    test();
}

// 全部都读一遍，不读白不读
void MainWindow::loadall()
{
    int ok = 0;
    for (int i = 0; i < books.size(); i++) {
QFile f(books[i].path);
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream s(&f);
            books[i].txt = s.readAll();
            books[i].ok = true;
            f.close();
            ok++;
 }
    }

        QString status = QString("读完啦，共 %1 本成功\n\n").arg(ok);
for (const book &b : books) {
        if (b.ok) {
            status += QString("《%1》开头：\n%2...\n").arg(b.name).arg(b.txt.left(300));
            break;
        }
    }
    ui->contextDisplay->setText(status);
    QMessageBox::information(this, "搞定啦", QString("一共搞定了 %1 本书！").arg(ok));
}

QList<chap> MainWindow::getchap(const QString &CONtent, int file)
{
    QList<chap> chaps;
            QRegularExpression regex("CHAPTER\\s+(\\w+)", QRegularExpression::CaseInsensitiveOption);
       //正则表达式寻找CHAPTER
  auto it = regex.globalMatch(CONtent);
    while (it.hasNext()) {
        auto m = it.next();
        chap c;
        c.pos = m.capturedStart();
        c.name = m.captured(0);
        c.show = conv(c.name);
        chaps.append(c);
    }
    return chaps;
}

QList<page> MainWindow::getpage(const QString &Content)
{
    QList<page> pages;
    QRegularExpression regex("(?:^|\\n)\\s*(\\d{1,3})\\s*(?=\\n|$)", QRegularExpression::MultilineOption);
     //正则表达式寻找页码
         auto it = regex.globalMatch(Content);
    while (it.hasNext()) {
        auto m = it.next();
        bool ok;
        int num = m.captured(1).toInt(&ok);
        if (ok && num > 0 && num < 1000) {
            page p;
            p.pos = m.capturedStart();
            p.num = num;
            pages.append(p);
        }
    }
std::sort(pages.begin(), pages.end(), [](const page &a, const page &b) {
        return a.pos < b.pos;
    });
    return pages;
}

QString MainWindow::findchap(int position, const QList<chap> &chapters)
{
    QString cur = "第1章";
    for (const auto &c : chapters) {
        if (c.pos <= position)
            cur = c.show;
        else
            break;
    }
    return cur;
}

int MainWindow::findpage(int Pos, const QList<page> &pages)
{
    int cur = 1;
    for (const auto &p : pages) {
        if (p.pos <= Pos)cur = p.num;
        else break;
    }
    return cur;
}

QString MainWindow::conv(const QString &_name)
{
    QMap<QString, QString> map = {
        {"ONE", "第1章"}, {"TWO", "第2章"}, {"THREE", "第3章"},
        {"FOUR", "第4章"}, {"FIVE", "第5章"}, {"SIX", "第6章"},
        {"SEVEN", "第7章"}, {"EIGHT", "第8章"}, {"NINE", "第9章"},
        {"TEN", "第10章"}, {"ELEVEN", "第11章"}, {"TWELVE", "第12章"},
        {"THIRTEEN", "第13章"}, {"FOURTEEN", "第14章"}, {"FIFTEEN", "第15章"},
        {"SIXTEEN", "第16章"}, {"SEVENTEEN", "第17章"}, {"EIGHTEEN", "第18章"},
        {"NINETEEN", "第19章"}, {"TWENTY", "第20章"}, {"TWENTY-ONE", "第21章"},
        {"TWENTY-TWO", "第22章"}, {"TWENTY-THREE", "第23章"}, {"TWENTY-FOUR", "第24章"}
    };

    QRegularExpression regex("CHAPTER\\s+(\\S+)");
    auto m = regex.match(_name);
    if (m.hasMatch()) {QString num = m.captured(1).toUpper();
        if (map.contains(num)) return map[num];
    }
    return _name;
}

// 搜索按钮点击时调用
void MainWindow::search()
{

    QString word = ui->searchLineEdit->text().trimmed();




    dosearch(word);
}

// 真正执行搜索的函数
void MainWindow::dosearch(const QString &word)
{
    QElapsedTimer timer;
    timer.start(); // 开始计时


    // 清空表格和之前的搜索结果
    ui->resultsTable->setRowCount(0);
    results.clear();

    int total = 0;  // 总共找到多少个要搜索的词

    // 在每本书里搜索
    for (int i = 0; i < books.size(); i++) {
        const book &b = books[i];



        // 提取这本书的章节和页码信息
        QList<chap> chaps = getchap(b.txt, i);
        QList<page> pages = getpage(b.txt);

        int pos = 0;      // 从第一个字符开始搜
        int count = 0;    // 这本书找到多少个


        while (true) {




            int found = b.txt.indexOf(word, pos, Qt::CaseInsensitive);

            // 如果没找到，跳出循环
            if (found == -1) { break;
            }



            total++;
            count++;


    QString chap = findchap(found, chaps);
            int page = findpage(found, pages);
//搜索结果
            res r;
            r.pos = found;
            r.word = word;
            r.row = total - 1;
            r.file = i;
            results.append(r);




    // 在表格里插入一行
            int row = ui->resultsTable->rowCount();
                    ui->resultsTable->insertRow(row);


            ui->resultsTable->setItem(row, 0, new QTableWidgetItem(QString::number(total)));
            ui->resultsTable->setItem(row, 1, new QTableWidgetItem(word));
            ui->resultsTable->setItem(row, 2, new QTableWidgetItem(QString::number(page)));
            ui->resultsTable->setItem(row, 3, new QTableWidgetItem(chap));
            ui->resultsTable->setItem(row, 4, new QTableWidgetItem(b.name));
    // 填写表格内容

            pos = found + 1;
        }
    }

 qint64 timeCost = timer.elapsed();  // 单位是毫秒
    //jishijieshu
    QString msg = QString("搜索完成！\n找到 %1 个结果\n已经识别章节和页码了")
                   .arg(total)
                   .arg(timeCost);


    if (total == 0) {QMessageBox::information(this, "搜索结果", "没找到匹配的内容");
    } else {QMessageBox::information(this, "搜索结果", msg + "\n点击表格里的行可以查看上下文");
    }
}

// 点击表格某一行时调用
void MainWindow::click(QTableWidgetItem *item)
{


    // 获取点击的行号
    int row = item->row();




    res r = results[row];

    // 显示这个结果的上下文
    showctx(r.pos, r.word, r.file);
}

// 显示搜索结果的上下文 - 就是搜到的词前后的文字
void MainWindow::showctx(int position, const QString &word, int file)
{

    // 获取对应的书
    const book &b = books[file];



    QList<chap> chaps = getchap(b.txt, file);
    QList<page> pages = getpage(b.txt);


    QString chap = findchap(position, chaps);
            int page = findpage(position, pages);
 // 确定这个位置是第几章第几页

    const int len = 200;

  int start = qMax(0, position - len);
    int end = qMin(b.txt.length() - 1, position + word.length() + len);

    QString ctx = b.txt.mid(start, end - start + 1);    // 提取上下文文字


    // 计算搜索词在上下文中的相对位置
    int rel = position - start;


    QString before = ctx.left(rel);
    QString high = ctx.mid(rel, word.length());
    QString after = ctx.mid(rel + word.length());

// 就是前后各200字，中间那个词加个【】当高亮
QString text = QString("=== 《%1》 ===\n").arg(b.name);
    text += QString("章节：%1\n").arg(chap);
    text += QString("页码：第 %1 页\n").arg(page);
    text += QString("位置：第 %1 个字符\n\n").arg(position);
    text += before + "【" + high + "】" + after;


    // 在界面上显示
    ui->contextDisplay->setText(text);

    // 把光标移到开头
    ui->contextDisplay->moveCursor(QTextCursor::Start);
}
