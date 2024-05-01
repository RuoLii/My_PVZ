#include "screenzombie.h"

ScreenZombie::ScreenZombie()
{
    hp = hp_ScreenZombie;
    atk = atk_Zombie;
    speed = speed_zombie_1;
    setMovie(":/new/prefix1/imag/ScreenZombieWalk.gif");
}

void ScreenZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    QList<QGraphicsItem *> items = collidingItems();
    if (hp <= 0)
    {
        if (state < ZombieType::DIE)
        {
            state = ZombieType::DIE;
            setMovie(":/new/prefix1/imag/zombie_die.gif");
            setHead(":/new/prefix1/imag/ZombieHead.gif");
        }else if (movie->currentFrameNumber() == movie->frameCount() - 1)
            delete this;
        return;
    }else if (!items.isEmpty())
    {
        Plant *plant = qgraphicsitem_cast<Plant *>(items[0]);
        plant->hp -= atk;
        if (state != ZombieType::ATTACK)
        {
            state = ZombieType::ATTACK;
            setMovie(":/new/prefix1/imag/ScreenZombieAttack.gif");
        }
        return;
    }else
    {
        state = ZombieType::WALK;
        setMovie(":/new/prefix1/imag/ScreenZombieWalk.gif");
    }
    setX(x() - speed);
}
