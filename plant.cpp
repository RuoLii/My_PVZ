#include "plant.h"
#include <zombie.h>

Plant::Plant()
{
    movie = nullptr;
    atk = counter = state = time = 0;
}

Plant::~Plant()
{
    delete movie;
}

QRectF Plant::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
}

bool Plant::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    // 左右30像素内是否存在僵尸
    return other->type() == Zombie::Type  && qAbs(other->x() - x()) < 25 && qAbs(other->y() - y()) < 15;
}

int Plant::type() const
{
    return Type;
}

void Plant::setMovie(QString path)
{
    movie = new QMovie(path);
    movie->start();
}
