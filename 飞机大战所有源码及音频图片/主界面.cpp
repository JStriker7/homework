#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include<iostream>
#include <vector>
#include <conio.h> 
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

//画面大小
const int width = 500;
const int canvasHeight = 700;

//飞机坐标
int playerX, pos_y;
int missileY;
int FoeMissile_x;
int  foeX;
int enemy_y ;

//得分和生命值
int score = 0;
int life = 10;

struct EnemyFoeMissile {
    int x, y;
};

const int interval = 1500;//子弹发射间隔
DWORD lastFoeMissileTime = 0;


//存储敌方子弹和敌机位置
vector<EnemyFoeMissile> hostileBullets;
vector<POINT> enemies;

//绘制我方子弹
void drawMyFoeMissile( int x,    int y) {
    settextcolor(YELLOW);
    setbkmode(TRANSPARENT);
    settextstyle(16, 2, _T("Consolas"));
    outtextxy(x, y, _T("|"));
}


//我方飞机
void drawPlane(int    x,int y) {
    // 设置绘制颜色为白色
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, _T("Consolas")); // 使用等宽字体

    // 飞机头部 
    int width1 = textwidth(_T("/=\\"));
    outtextxy(x - width1 / 2, y - 40, _T("/=\\"));

    // 飞机机身和机翼 <*> (3个字符)  
    int width2 = textwidth(_T("<<*>>"));
    outtextxy(x - width2 / 2, y - 20, _T("<<*>>"));

    // 飞机尾部的两个点 * * (3个字符，中间有空格)
    int width3 = textwidth(_T("* *"));
    outtextxy(x - width3 / 2, y, _T("* *"));
}

//敌方飞机
void drawPlane2( int  x,int y) {
    // 设置字体和颜色
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, _T("Consolas")); // 使用等宽字体

    // 第二种战机样式
    // 上方的 \+/
    int width1 = textwidth(_T("\\+/"));
    outtextxy(x - width1 / 2, y - 20, _T("\\+/"));

    // 下方的 |
    int width2 = textwidth(_T("|"));
    outtextxy(x - width2 / 2, y, _T("|"));
}


void showStartScreen() {
    // 清屏并设置背景
    setbkcolor(RGB(0, 0, 0));
    cleardevice();

    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(40, 0, _T("Arial"));

    // 显示标题
    TCHAR title[] = _T("飞机大战");
    int titleW = textwidth(title);
    outtextxy((width - titleW) / 2, canvasHeight / 3, title);

    // 显示按钮（文字）
    settextstyle(24, 0, _T("Arial"));
    TCHAR btnText[] = _T("点击开始游戏");
    int btnW = textwidth(btnText);
    int btnH = textheight(btnText);
    int btnX = (width - btnW) / 2;
    int btnY = canvasHeight / 2;

    // 按钮背景
    setfillcolor(RGB(80, 80, 80));
    fillrectangle(btnX - 10, btnY - 5, btnX + btnW + 10, btnY + btnH + 5);

    // 文字
    settextcolor(WHITE);
    outtextxy(btnX, btnY, btnText);

    // 等待点击或回车
    while (true) {
        ExMessage msg;
        if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= btnX - 10 && msg.x <= btnX + btnW + 10 &&
                    msg.y >= btnY - 5 && msg.y <= btnY + btnH + 5) {
                    return; // 点击“开始游戏”按钮
                }
            }

            if (msg.message == WM_KEYDOWN&&msg.vkcode == VK_RETURN) {
                return; // 按下回车键
            }
        }

        Sleep(20);
    }
}


//绘制敌方子弹
void drawEnemyFoeMissile(int x,int y) {
    settextcolor(RGB(255, 50, 50));
    setbkmode(TRANSPARENT);
    settextstyle(22, 4, _T("Consolas"));
    outtextxy(x, y, _T("|"));
}

// 更新并绘制所有敌机子弹
void updatehostileBullets() {
    for (int i = 0; i < hostileBullets.size(); i++) {
        hostileBullets[i].y += 10; 
        drawEnemyFoeMissile(hostileBullets[i].x, hostileBullets[i].y); // 绘制子弹
    }

    // 清理超出画面范围的敌机子弹
    for (int i = 0; i < hostileBullets.size(); i++) {
        if (hostileBullets[i].y > canvasHeight) {
            hostileBullets.erase(hostileBullets.begin() + i); // 移除超出屏幕的子弹
            i--; // 调整索引
        }
    }
}

void pauseGame() {
    // 暂停背景音乐
    mciSendString(_T("pause background"), NULL, 0, NULL);

    // 只绘制一次暂停界面
    setfillcolor(RGB(0, 0, 0));
    bar(width / 2 - 150, canvasHeight / 2 - 80, width / 2 + 150, canvasHeight / 2 + 80);

    setlinecolor(WHITE);
    rectangle(width / 2 - 150, canvasHeight / 2 - 80, width / 2 + 150, canvasHeight / 2 + 80);

    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, _T("Arial"));

    int w1 = textwidth(_T("游戏暂停"));
    outtextxy((width - w1) / 2, canvasHeight / 2 - 40, _T("游戏暂停"));

    settextstyle(18, 0, _T("Arial"));
    setfillcolor(RGB(100, 100, 100));
    fillrectangle(width/ 2 - 50, canvasHeight   / 2+ 10, width / 2 +   50, canvasHeight / 2 + 40);
    rectangle(width / 2-50, canvasHeight / 2 +10, width / 2 +50, canvasHeight/ 2 + 40);

    int w2 = textwidth(_T("点击继续"));
    outtextxy((width - w2) / 2, canvasHeight / 2 + 22, _T("点击继续"));

    static bool escPressed = false;

    // 循环中只处理输入，不重复绘制
    while (true) {
        ExMessage msg;
        if (peekmessage(&msg, EX_MOUSE)) {
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= width / 2 - 50 && msg.x <= width / 2 + 50 &&
                    msg.y >= canvasHeight / 2 + 10 && msg.y <= canvasHeight / 2 + 40) {
                    mciSendString(_T("resume background"), NULL, 0, NULL);
                    return;
                }
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            if (!escPressed) {
                mciSendString(_T("resume background"), NULL, 0, NULL);
                escPressed = true;
                return;
            }
        }
        else {
            escPressed = false;
        }

        Sleep(50);
    }
}
// 处理键盘输入 - 使用 EasyX 的 peekmessage
void h() {
    const int moveSpeed = 16;  // 移动速度
    ExMessage msg;
 
    // 处理所有待处理的消息
    while (peekmessage(&msg, EX_KEY)) {
        if (msg.message == WM_KEYDOWN) {
            switch (msg.vkcode) {
            case 'W':
                if (pos_y - moveSpeed >= 50)
                {
                    pos_y -= moveSpeed;
                }
                break;
            case 'S':
                if (pos_y + moveSpeed <= canvasHeight - 50) {
                    pos_y += moveSpeed;
                }
                break;
            case 'A':
                if (playerX - moveSpeed >= 50) 
                {
                    playerX -= moveSpeed;
                }
                break;
            case 'D':
                if (playerX + moveSpeed <= width - 50) {
                    playerX += moveSpeed;
                }
                break;
            case VK_SPACE:
                FoeMissile_x = playerX - 3;
                missileY= pos_y - 55;

                // 播放发射音效
                mciSendString(_T("close biubiu"), NULL, 0, NULL);
                mciSendString(_T("open biubiu.wav alias biubiu"), NULL, 0, NULL);
                mciSendString(_T("play biubiu"), NULL, 0, NULL);
                break;
            case 'Q':
                PlaySound(NULL, 0, 0);
                closegraph();
                exit(0);
                break;
            }
        }
    }
}

//爆炸图片
IMAGE boomImg;


int main()
{
    //背景音乐
    PlaySound(_T("background.wav"), NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
    
    //加载爆炸图片
    loadimage(&boomImg, _T("boom.png"),60,60);

	initgraph(width, canvasHeight);
   
    showStartScreen();

    //创建后台缓冲区
    IMAGE buffer;
    buffer.Resize(width, canvasHeight);

    //加载图片
	IMAGE img;
	loadimage(&img, _T("background.jpg"));
	
    playerX = width/ 2;
    pos_y =canvasHeight*0.7;
     missileY= pos_y - 55;
     FoeMissile_x = -100;

     //最开始敌机位置
     POINT firstEnemy = { rand() % (width - 100) + 50, 75 };
     enemies.push_back(firstEnemy);


     while (1)
     {
         static bool escPressed = false;
         if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
             if (!escPressed) {
                 pauseGame();
                 escPressed = true;
             }
         }
         else {
             escPressed = false;
         }
         h();
         //在后台缓冲区绘制背景
         SetWorkingImage(&buffer);
         putimage(0, 0, &img);

         drawPlane(playerX, pos_y);//
         for (int i = 0; i < enemies.size(); i++) {
             drawPlane2(enemies[i].x, enemies[i].y);
         }
         drawMyFoeMissile(FoeMissile_x, missileY);

         updatehostileBullets();

         // 检查敌方子弹是否击中我方飞机
         for (int i = 0; i < hostileBullets.size(); i++) {
             if (abs(hostileBullets[i].x - playerX) + abs(hostileBullets[i].y - pos_y) < 20) {
                 life--;
                 hostileBullets.erase(hostileBullets.begin() + i);
                 i--;

                 if (life <= 0) {
                     TCHAR msg[100];
                     _stprintf(msg, _T("Game Over!\nScore: %d\n哇塞！！"), score);
                     MessageBox(NULL, msg, _T("GAME OVER"), MB_OK | MB_ICONINFORMATION);
                     PlaySound(NULL, 0, 0);
                     closegraph();
                     exit(0);
                 }
             }
         }

         // 显示分数和生命值
         TCHAR scoreText[20];
         _stprintf(scoreText, _T("Score: %d"), score);
         outtextxy(10, canvasHeight - 30, scoreText);

         TCHAR lifeText[20];
         _stprintf(lifeText, _T("Life: %d"), life);
         outtextxy(10, canvasHeight - 60, lifeText);
        
         // // 切换回前台，一次性显示整个缓冲区
         SetWorkingImage();
         putimage(0, 0, &buffer);

         if (missileY> -50)
             missileY= missileY- 13;

         //设置敌机子弹发射间隔
         DWORD currentTime = GetTickCount();
         if (currentTime - lastFoeMissileTime >= interval) {
             for (int i = 0; i < enemies.size(); i++) {
                 EnemyFoeMissile newFoeMissile;
                 newFoeMissile.x = enemies[i].x;
                 newFoeMissile.y = enemies[i].y + 45;
                 hostileBullets.push_back(newFoeMissile);
             }
         lastFoeMissileTime = currentTime;
     }
         
         //击中之后刷新敌机
         for (int i = 0; i < enemies.size(); i++) {
             if (abs(enemies[i].x - FoeMissile_x) + abs(enemies[i].y - missileY) < 20) {
        // 播放爆炸音效
        mciSendString(_T("close boom"), NULL, 0, NULL);
        mciSendString(_T("open boom.wav alias boom"), NULL, 0, NULL);
        mciSendString(_T("play boom"), NULL, 0, NULL);
        // 爆炸效果图
        putimage(enemies[i].x - 30,enemies[i].y - 30,   &boomImg);
        Sleep(200);

        missileY= -100;
        score++;

        // 记录当前敌机数量
        int newCount = enemies.size() + 1;

        // 清空所有敌机
        enemies.clear();

        // 添加新的敌机，共 newCount 个，位置在屏幕上 1/4 范围内随机
        for (int j = 0; j < newCount; j++) {
            POINT newEnemy = {
                rand() % (width - 100) + 50,
                rand() % (canvasHeight / 4) + 30
            };
            enemies.push_back(newEnemy);
        }

        break;
    }
}

     

        Sleep(1);
	}
    _getch();
    PlaySound(NULL, 0, 0);
	closegraph();
	return 0;
}