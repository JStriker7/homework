#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include<iostream>
#include <vector>
#include <conio.h> 
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

//�����С
const int width = 500;
const int canvasHeight = 700;

//�ɻ�����
int playerX, pos_y;
int missileY;
int FoeMissile_x;
int  foeX;
int enemy_y ;

//�÷ֺ�����ֵ
int score = 0;
int life = 10;

struct EnemyFoeMissile {
    int x, y;
};

const int interval = 1500;//�ӵ�������
DWORD lastFoeMissileTime = 0;


//�洢�з��ӵ��͵л�λ��
vector<EnemyFoeMissile> hostileBullets;
vector<POINT> enemies;

//�����ҷ��ӵ�
void drawMyFoeMissile( int x,    int y) {
    settextcolor(YELLOW);
    setbkmode(TRANSPARENT);
    settextstyle(16, 2, _T("Consolas"));
    outtextxy(x, y, _T("|"));
}


//�ҷ��ɻ�
void drawPlane(int    x,int y) {
    // ���û�����ɫΪ��ɫ
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, _T("Consolas")); // ʹ�õȿ�����

    // �ɻ�ͷ�� 
    int width1 = textwidth(_T("/=\\"));
    outtextxy(x - width1 / 2, y - 40, _T("/=\\"));

    // �ɻ�����ͻ��� <*> (3���ַ�)  
    int width2 = textwidth(_T("<<*>>"));
    outtextxy(x - width2 / 2, y - 20, _T("<<*>>"));

    // �ɻ�β���������� * * (3���ַ����м��пո�)
    int width3 = textwidth(_T("* *"));
    outtextxy(x - width3 / 2, y, _T("* *"));
}

//�з��ɻ�
void drawPlane2( int  x,int y) {
    // �����������ɫ
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, _T("Consolas")); // ʹ�õȿ�����

    // �ڶ���ս����ʽ
    // �Ϸ��� \+/
    int width1 = textwidth(_T("\\+/"));
    outtextxy(x - width1 / 2, y - 20, _T("\\+/"));

    // �·��� |
    int width2 = textwidth(_T("|"));
    outtextxy(x - width2 / 2, y, _T("|"));
}


void showStartScreen() {
    // ���������ñ���
    setbkcolor(RGB(0, 0, 0));
    cleardevice();

    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(40, 0, _T("Arial"));

    // ��ʾ����
    TCHAR title[] = _T("�ɻ���ս");
    int titleW = textwidth(title);
    outtextxy((width - titleW) / 2, canvasHeight / 3, title);

    // ��ʾ��ť�����֣�
    settextstyle(24, 0, _T("Arial"));
    TCHAR btnText[] = _T("�����ʼ��Ϸ");
    int btnW = textwidth(btnText);
    int btnH = textheight(btnText);
    int btnX = (width - btnW) / 2;
    int btnY = canvasHeight / 2;

    // ��ť����
    setfillcolor(RGB(80, 80, 80));
    fillrectangle(btnX - 10, btnY - 5, btnX + btnW + 10, btnY + btnH + 5);

    // ����
    settextcolor(WHITE);
    outtextxy(btnX, btnY, btnText);

    // �ȴ������س�
    while (true) {
        ExMessage msg;
        if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= btnX - 10 && msg.x <= btnX + btnW + 10 &&
                    msg.y >= btnY - 5 && msg.y <= btnY + btnH + 5) {
                    return; // �������ʼ��Ϸ����ť
                }
            }

            if (msg.message == WM_KEYDOWN&&msg.vkcode == VK_RETURN) {
                return; // ���»س���
            }
        }

        Sleep(20);
    }
}


//���Ƶз��ӵ�
void drawEnemyFoeMissile(int x,int y) {
    settextcolor(RGB(255, 50, 50));
    setbkmode(TRANSPARENT);
    settextstyle(22, 4, _T("Consolas"));
    outtextxy(x, y, _T("|"));
}

// ���²��������ел��ӵ�
void updatehostileBullets() {
    for (int i = 0; i < hostileBullets.size(); i++) {
        hostileBullets[i].y += 10; 
        drawEnemyFoeMissile(hostileBullets[i].x, hostileBullets[i].y); // �����ӵ�
    }

    // ���������淶Χ�ĵл��ӵ�
    for (int i = 0; i < hostileBullets.size(); i++) {
        if (hostileBullets[i].y > canvasHeight) {
            hostileBullets.erase(hostileBullets.begin() + i); // �Ƴ�������Ļ���ӵ�
            i--; // ��������
        }
    }
}

void pauseGame() {
    // ��ͣ��������
    mciSendString(_T("pause background"), NULL, 0, NULL);

    // ֻ����һ����ͣ����
    setfillcolor(RGB(0, 0, 0));
    bar(width / 2 - 150, canvasHeight / 2 - 80, width / 2 + 150, canvasHeight / 2 + 80);

    setlinecolor(WHITE);
    rectangle(width / 2 - 150, canvasHeight / 2 - 80, width / 2 + 150, canvasHeight / 2 + 80);

    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, _T("Arial"));

    int w1 = textwidth(_T("��Ϸ��ͣ"));
    outtextxy((width - w1) / 2, canvasHeight / 2 - 40, _T("��Ϸ��ͣ"));

    settextstyle(18, 0, _T("Arial"));
    setfillcolor(RGB(100, 100, 100));
    fillrectangle(width/ 2 - 50, canvasHeight   / 2+ 10, width / 2 +   50, canvasHeight / 2 + 40);
    rectangle(width / 2-50, canvasHeight / 2 +10, width / 2 +50, canvasHeight/ 2 + 40);

    int w2 = textwidth(_T("�������"));
    outtextxy((width - w2) / 2, canvasHeight / 2 + 22, _T("�������"));

    static bool escPressed = false;

    // ѭ����ֻ�������룬���ظ�����
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
// ����������� - ʹ�� EasyX �� peekmessage
void h() {
    const int moveSpeed = 16;  // �ƶ��ٶ�
    ExMessage msg;
 
    // �������д��������Ϣ
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

                // ���ŷ�����Ч
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

//��ըͼƬ
IMAGE boomImg;


int main()
{
    //��������
    PlaySound(_T("background.wav"), NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
    
    //���ر�ըͼƬ
    loadimage(&boomImg, _T("boom.png"),60,60);

	initgraph(width, canvasHeight);
   
    showStartScreen();

    //������̨������
    IMAGE buffer;
    buffer.Resize(width, canvasHeight);

    //����ͼƬ
	IMAGE img;
	loadimage(&img, _T("background.jpg"));
	
    playerX = width/ 2;
    pos_y =canvasHeight*0.7;
     missileY= pos_y - 55;
     FoeMissile_x = -100;

     //�ʼ�л�λ��
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
         //�ں�̨���������Ʊ���
         SetWorkingImage(&buffer);
         putimage(0, 0, &img);

         drawPlane(playerX, pos_y);//
         for (int i = 0; i < enemies.size(); i++) {
             drawPlane2(enemies[i].x, enemies[i].y);
         }
         drawMyFoeMissile(FoeMissile_x, missileY);

         updatehostileBullets();

         // ���з��ӵ��Ƿ�����ҷ��ɻ�
         for (int i = 0; i < hostileBullets.size(); i++) {
             if (abs(hostileBullets[i].x - playerX) + abs(hostileBullets[i].y - pos_y) < 20) {
                 life--;
                 hostileBullets.erase(hostileBullets.begin() + i);
                 i--;

                 if (life <= 0) {
                     TCHAR msg[100];
                     _stprintf(msg, _T("Game Over!\nScore: %d\n��������"), score);
                     MessageBox(NULL, msg, _T("GAME OVER"), MB_OK | MB_ICONINFORMATION);
                     PlaySound(NULL, 0, 0);
                     closegraph();
                     exit(0);
                 }
             }
         }

         // ��ʾ����������ֵ
         TCHAR scoreText[20];
         _stprintf(scoreText, _T("Score: %d"), score);
         outtextxy(10, canvasHeight - 30, scoreText);

         TCHAR lifeText[20];
         _stprintf(lifeText, _T("Life: %d"), life);
         outtextxy(10, canvasHeight - 60, lifeText);
        
         // // �л���ǰ̨��һ������ʾ����������
         SetWorkingImage();
         putimage(0, 0, &buffer);

         if (missileY> -50)
             missileY= missileY- 13;

         //���õл��ӵ�������
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
         
         //����֮��ˢ�µл�
         for (int i = 0; i < enemies.size(); i++) {
             if (abs(enemies[i].x - FoeMissile_x) + abs(enemies[i].y - missileY) < 20) {
        // ���ű�ը��Ч
        mciSendString(_T("close boom"), NULL, 0, NULL);
        mciSendString(_T("open boom.wav alias boom"), NULL, 0, NULL);
        mciSendString(_T("play boom"), NULL, 0, NULL);
        // ��ըЧ��ͼ
        putimage(enemies[i].x - 30,enemies[i].y - 30,   &boomImg);
        Sleep(200);

        missileY= -100;
        score++;

        // ��¼��ǰ�л�����
        int newCount = enemies.size() + 1;

        // ������ел�
        enemies.clear();

        // ����µĵл����� newCount ����λ������Ļ�� 1/4 ��Χ�����
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