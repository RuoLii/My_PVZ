#ifndef SUN_H
#define SUN_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QTimer>
#include <QMovie>
#include <QTime>
#include <QThread>
#include <QEvent>
#include <QPainter>
#include "shop.h"

using namespace std;


class Sun : public QGraphicsItem
{
//    Q_OBJECT
public:
    Sun();
    Sun(QPointF pos);
    ~Sun();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;

private:
    QMovie *movie;
    QPointF dest;
    int counter;
    int time;
    double speed;
};

#endif // SUN_H
