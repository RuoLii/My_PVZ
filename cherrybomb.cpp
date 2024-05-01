#include "cherrybomb.h"

CherryBomb::CherryBomb()
{
    atk = atk_CherryBomb;
    hp = hp_NormalPlant;
    setMovie(":/new/prefix1/imag/cherrybomb.gif");
}

QRectF CherryBomb::boundingRect() const
{
    return state ? QRectF(-150, -150, 300, 300) : Plant::boundingRect();
}

void CherryBomb::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;

    //正常状态到爆炸状态
    else if (state == 0 && movie->currentFrameNumber() == movie->frameCount() - 1)
    {
        state = 1;
        setMovie(":/new/prefix1/imag/Boom.gif");
        QList<QGraphicsItem *> items = collidingItems();
        foreach (QGraphicsItem *item, items)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
            zombie->hp -= atk;
            if (zombie->hp <= 0)
            {
                zombie->state = ZombieType::BURN;//僵尸变为烧焦状态
                zombie->setMovie(":/new/prefix1/imag/Burn.gif");
            }
        }
    }
    else if (state == 1 && movie->currentFrameNumber() == movie->frameCount() - 1)
        delete this;
}

//碰撞检测：遇到僵尸 && 距离接近
bool CherryBomb::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    //QLineF与QLine不同在于提供了浮点精度线段表示，
    //在成员函数方面增加了角度，单位向量等的表示，不过线段的表示法还是一样的，由两个点起点与终点标识。
    return other->type() == Zombie::Type && QLineF(pos(), other->pos()).length() < 190;//190可以炸到斜对角而且炸不到三格,刚刚好
}
