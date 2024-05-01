#ifndef SHOP_H
#define SHOP_H

#include "sun.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include "init.h"

class Shop : public QGraphicsItem
{
public:
    int sun;
    Shop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
private:
    int counter;
    int time;
};

#endif // SHOP_H
