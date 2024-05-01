#ifndef WHACKGAME_H
#define WHACKGAME_H

#include <QWidget>
#include "init2.h"
#include <logonbutton.h>
#include <QMessageBox>
#include <music.h>
#include <hammer.h>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <diggerzombie.h>
#include <QMediaPlayer>

using namespace std;

namespace Ui {
class Whackgame;
}

class Whackgame : public QWidget
{
    Q_OBJECT

public:
    explicit Whackgame(QWidget *parent = nullptr);
    ~Whackgame();
    void addZombie();
    void check();
    void juicy();
private:
    int time = GAME_TIME;
    int cnt = 0;
    bool hole[10];//0 ~ 7号洞是否存在僵尸

private:
    Ui::Whackgame *ui;
    QSound *sound;
    QTimer *timer;
    QTimer *timer2;
    Logonbutton *menubutton;
    Hammer *hammer;
    QBrush *pic;
    QMouseEvent * me;
    QLabel *aiit;
    QMediaPlayer *startSound;

    static int ZOMBIE_GEN_TIMES_NOW;
    static int zom_time;
    static int zom_cnt;//僵尸的数量

    int xx,yy;
    int socre;

signals:
    void mouseMove(QMouseEvent *ev);
    void knock(int id);//参数代表被敲击的是哪一个洞

private slots:
    void hammer_move(QMouseEvent *ev);
    void hammer_clicked_slot();

protected:
    void mouseMoveEvent(QMouseEvent *ev);
};

#endif // WHACKGAME_H
