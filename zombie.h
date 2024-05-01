#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "init.h"

enum class ZombieType { WALK = 0, ATTACK, DIE, BURN};//僵尸拥有四种状态，行走状态，攻击状态，死亡状态，烧焦状态

class Zombie : public QGraphicsItem
{
public:
    int hp;//生命值
    int atk;//攻击力
    qreal speed;//移动速度

    //僵尸状态
    ZombieType state;

    enum { Type = UserType + 2};


    Zombie();
    ~Zombie() override;
    QRectF boundingRect() const override;//检测具体区域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;//碰撞检测
    int type() const override;
    void setMovie(QString path);//设置动图
    void setHead(QString path);//设置头
protected:
    QMovie *movie;
    QMovie *head;
};

#endif // ZOMBIE_H
