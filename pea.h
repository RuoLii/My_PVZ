#ifndef PEA_H
#define PEA_H

#include <QRectF>
#include <QPainter>
#include <QGraphicsItem>
#include "zombie.h"

//豌豆子弹

class Pea : public QGraphicsItem
{
public:
    Pea(int attack = 0, bool flag = false);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
    void sound();
private:
    //是否冰冻，杀伤力，速度
    bool snow;
    int atk;
    qreal speed;
};

#endif // PEA_H
