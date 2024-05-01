#include "basiczombie.h"
#include <QDebug>

//普通僵尸类
//有4种状态，行走，攻击，死亡，被烧焦

BasicZombie::BasicZombie()
{
    hp = hp_BasicZombie;
    atk = atk_Zombie;
    speed = speed_zombie_1;

    //if (qrand() % 2)
        //setMovie(":/images/ZombieWalk1.gif");
    //else
        setMovie(":/new/prefix1/imag/ZombieWalk1.gif");
        movie->start();
}

//僵尸的状态变化
void BasicZombie::advance(int phase)
{
    if (!phase)
        return;
    update();


    QList<QGraphicsItem *> items = collidingItems(Qt::IntersectsItemShape);

    //如果死亡
    if (hp <= 0)
    {
        if (state < ZombieType::DIE)
        {
            state = ZombieType::DIE;
            setMovie(":/new/prefix1/imag/zombie_die.gif");//死亡的图片
            setHead(":/new/prefix1/imag/ZombieHead.gif");//画头
        }
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)//头的动画播放完删除该僵尸
            delete this;
        return;
    }

    //如果发生碰撞，变为攻击状态攻击植物
    else if (!items.isEmpty())
    {
        Plant *plant = qgraphicsitem_cast<Plant *>(items[0]);
        plant->hp -= atk;
        if (state != ZombieType::ATTACK)
        {
            state = ZombieType::ATTACK;
            setMovie(":/new/prefix1/imag/ZombieAttack.gif");
        }
        return;
    }

    //没死，没碰撞，就继续行走
    else//if ( state==ZombieType::ATTACK || state==ZombieType::DIE )
    {
        state = ZombieType::WALK;
        setMovie(":/new/prefix1/imag/ZombieWalk1.gif");
    }

    // 向前移动
    setX(x() - speed);
}
