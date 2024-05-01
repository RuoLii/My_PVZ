#include "footballzombie.h"

FootballZombie::FootballZombie()
{
    hp = hp_FootballZombie;
    atk = atk_Zombie;
    speed = speed_zombie_2;
    setMovie(":/new/prefix1/imag/FootballZombieWalk.gif");
}

void FootballZombie::advance(int phase)
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
            setMovie(":/new/prefix1/imag/FootballZombieDie.gif");
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
            setMovie(":/new/prefix1/imag/FootballZombieAttack.gif");
        }
        return;
    }else
    {
        state = ZombieType::WALK;
        setMovie(":/new/prefix1/imag/FootballZombieWalk.gif");
    }
    setX(x() - speed);
}
