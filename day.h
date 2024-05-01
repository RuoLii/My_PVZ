#ifndef DAY_H
#define DAY_H

#include <QWidget>
#include <QMouseEvent>
#include <music.h>
#include <choose_plant.h>
#include <logonbutton.h>
#include <seedbank.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QPropertyAnimation>
#include <plant_card.h>
#include <grass.h>
#include "shop.h"
#include "init.h"
#include "peashooter.h"
#include "sunflower.h"
#include "cherrybomb.h"
#include "wallnut.h"
#include "potatomine.h"
#include "snowpea.h"
#include "mower.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"

namespace Ui {
class Day;
}

class Day : public QWidget
{
    Q_OBJECT

public:
    explicit Day(QWidget *parent = nullptr);
    ~Day();
    Seedbank seedbank;
private:
    Ui::Day *ui;
    QBrush *pic;
    Logonbutton *menubutton;
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPropertyAnimation *m;//动画指针
    QMouseEvent * me;
    Plant_card *card1;
    Plant_card *card2;
    Plant_card *card3;
    Plant_card *card4;
    Plant_card *card5;
    Plant_card *shovel;
    QMediaPlayer *startSound;
    Plant_card *CardList[5];
    Grass grass;

    int xx;
    int yy;//鼠标最后坐标

protected:
    void mouseMoveEvent(QMouseEvent *ev);//重写 mouseMoveEvent 函数
signals:
    void now_sun_val(int);
    void cooltime();
    void map_plant_signal(int id, QPointF pos);
    void mouseMove(QMouseEvent *ev);//  鼠标移动信号

private slots:
    void plant_sound();
    void mouse_move(QMouseEvent *);
    void ready_to_plant_slot(int num);
    void addZombie();
    void check();
    void game_start_slot();

private:
    static int ZOMBIE_GEN_TIMES_NOW;

};

#endif // DAY_H
