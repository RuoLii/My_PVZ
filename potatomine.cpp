#include "potatomine.h"

PotatoMine::PotatoMine()
{
    atk = atk_PotatoMine;
    hp = hp_NormalPlant;
    time = int(15.0 * 1000 / 33);
    setMovie(":/new/prefix1/imag/potatodilei_noready.gif");
}

QRectF PotatoMine::boundingRect() const
{
    return state == 2 ? QRectF(-75, -75, 150, 150) : Plant::boundingRect();
}

//根据计数器和状态，进行碰撞检测，完成行动和状态转移
void PotatoMine::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    //时间到了就可以起爆，变为起爆状态
    else if (state == 0 && ++counter >= time)
    {
        state = 1;
        counter = 0;
        time = int(1.0 * 1000 / 33);
        setMovie(":/new/prefix1/imag/potatodilei_ready.gif");
    }
    //遇到僵尸就爆炸，变为爆炸状态
    else if (state == 1 && ++counter >= time)
    {
        counter = 0;
        QList<QGraphicsItem *> items = collidingItems();
        if (!items.isEmpty())
        {
            state = 2;
            setMovie(":/new/prefix1/imag/PotatoMineBomb.gif");
            foreach (QGraphicsItem *item, items)
            {
                //由于 QGraphicsScene 和 QGraphicsItem 的大多数便利函数
                //例如items()selectedItems()、collidingItems()、childItems()返回一个 QList<QGraphicsItem *> 列表
                //在遍历列表的时候通常需要对其中的 QGraphicsItem 进行类型检测与转换以确定实际的 item。
                //https://blog.csdn.net/weixin_33769207/article/details/90530644
                Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
                zombie->hp -= atk;
                if (zombie->hp <= 0)
                    delete zombie;
            }
        }
    }
    //爆炸后，删除对象
    else if (state == 2 && movie->currentFrameNumber() == movie->frameCount() - 1)
        delete this;
}

bool PotatoMine::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qAbs(other->y() - y()) < 15 && qAbs(other->x() - x()) < 50;
}

