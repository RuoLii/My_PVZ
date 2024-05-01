#include "zombie.h"
#include <plant.h>

Zombie::Zombie()
{
    movie = head = nullptr;
    hp = atk = 0;
    speed = 0.0;
    state = ZombieType::WALK;//设置僵尸行走状态
}

Zombie::~Zombie()
{
    delete movie;
    delete head;
}

QRectF Zombie::boundingRect() const
{
    return QRectF(-80, -100, 200, 140);
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    //烧焦和吃植物使用动图，其他两个状态使用QPainter进行绘图
    QImage image = movie->currentImage();
    if (speed < 0.55 && state != ZombieType::BURN)//不是烧焦状态并且被减速过了，防止一直被减速，速度调整回来
    {
        if (state != ZombieType::DIE)
            movie->setSpeed(50);
        int w = image.width();
        int h = image.height();
        for (int i = 0 ; i < h; i ++ )
        {
            uchar *line = image.scanLine(i);
            for (int j = 5; j < w - 5; j ++ )
                line[j << 2] = 200;
        }
    }
    painter->drawImage(QRectF(-15, -80, 100, 120), image);
    if (head)
    {
        image = head->currentImage();
        if (speed < 0.55)//被寒冰射手减速或者其他减速效果，给自身画个蓝边
        {
            int w = image.width();
            int h = image.height();
            for (int i = 0 ; i < h; i ++ )
            {
                uchar *line = image.scanLine(i);
                for (int j = 5; j < w - 5; j ++ )
                    line[j << 2] = 200;
            }
        }
        painter->drawImage(QRectF(0, -100, 140, 140), image);
    }
}

bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plant::Type  && qAbs(other->x() - x()) < 25 && qAbs(other->y() - y()) < 15;
}

int Zombie::type() const
{
    return Type;
}

void Zombie::setMovie(QString path)
{
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}

void Zombie::setHead(QString path)
{
    if (head)
        delete head;
    head = new QMovie(path);
    head->start();
}
