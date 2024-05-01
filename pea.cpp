#include "pea.h"

//豌豆子弹

Pea::Pea(int attack, bool flag)
{
    snow = flag;
    atk = attack;
    speed = 360.0 * 33 / 1000;
}

QRectF Pea::boundingRect() const
{
    return QRectF(-12, -28, 56, 34);
}
//绘制豌豆子弹
void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-12, -28, 56, 34), QPixmap(snow ? ":/new/prefix1/imag/PeaSnow.gif" : ":/new/prefix1/imag/pea_bullet.gif"));
}

//碰撞检测
bool Pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qAbs(other->y() - y()) < 15 && qAbs(other->x() - x()) < 15;
}

//完成行动和状态转移
void Pea::advance(int phase)
{
    if (!phase)
        return;
    update();
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[qrand() % items.size()]);
        zombie->hp -= atk;
        //如果子弹是寒冰豌豆 并且 僵尸速度没有减半 ，只减速一次 ------防止一直给僵尸减速！！！
        if (snow && zombie->speed > 0.55)
            zombie->speed /= 2;
        delete this;
        return;
    }
    //飞离画面？
    setX(x() + speed);
    if (x() > 1069)
        delete this;
}
