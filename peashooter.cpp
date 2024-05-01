#include "peashooter.h"
#include <QDebug>

Peashooter::Peashooter()
{
    atk = atk_Peashooter;
    hp = hp_NormalPlant;
    time = int(1.4 * 1000 / 33);
    setMovie(":/new/prefix1/imag/peashooter.gif");
}

void Peashooter::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    else if (++counter >= time)
    {
        counter = 0;
        if (!collidingItems().isEmpty())
        {
            Pea *pea = new Pea(atk);
            pea->setX(x() + 32);
            pea->setY(y() - 2);
            scene()->addItem(pea);
            return;
        }
    }
}

bool Peashooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qAbs(other->y() - y()) < 15;
}
