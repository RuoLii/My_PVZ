#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <init.h>

class Plant : public QGraphicsItem
{
public:
    int hp;
    int state;
    enum {Type = UserType + 1};//植物属于第一类
    Plant();
    ~Plant() override;

    //支持重写的函数
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *ohter, Qt::ItemSelectionMode mode) const override;//碰撞检测
    int type() const override;
    //设置动画
    void setMovie(QString path);

protected:
    QMovie *movie;
    int atk;
    int counter;//用于计时，比如豌豆射手发射豌豆的间隔时间
    int time;
};

#endif // PLANT_H
