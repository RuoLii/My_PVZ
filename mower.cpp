#include "mower.h"

//割草机

Mower::Mower()
{
    flag = false;
    speed = 300.0 * 33 / 1000;
    startSound = new QMediaPlayer();
}

Mower::~Mower()
{
    delete startSound;
}

QRectF Mower::boundingRect() const
{
    return QRectF(-30, -30, 60, 60);
}
//绘制割草机
void Mower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-30, -30, 60, 60), QPixmap(":/new/prefix1/imag/LawnMower.png"));
}


//检测碰撞：碰到僵尸 && 纵坐标一样 && 横坐标接近
bool Mower::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    //比较两个浮点数，相等返回true：qFuzzyCompare(other->y(), y())
    if (other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15){
        startSound->setMedia(QUrl("qrc:/new/prefix1/music/lawnmower.mp3"));  //将音乐文件添加到播放列表中
        startSound->play();
    }
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15;
}

//割草机与僵尸碰撞，僵尸死亡。割草机消失
void Mower::advance(int phase)
{
    if (!phase)
        return;
    update();
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.empty())
    {
        flag = true;
        foreach (QGraphicsItem *item, items)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
            zombie->hp = 0;
        }
    }
    if (flag)
        setX(x() + speed);
    if (x() > 1069)
        delete this;
}
