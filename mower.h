#ifndef MOWER_H
#define MOWER_H

#include <QGraphicsItem>
#include "zombie.h"
#include <QMediaPlayer>

//割草机

class Mower : public QGraphicsItem
{
public:
    Mower();
    ~Mower();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
private:
    bool flag;
    qreal speed;
    QMediaPlayer *startSound;
};

#endif
