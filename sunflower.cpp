#include "sunflower.h"

SunFlower::SunFlower()
{
    hp = hp_NormalPlant;
    time = int(8.0 * 1000 / 33);
    setMovie(":/new/prefix1/imag/sunflower.gif");
}

//生产阳光
void SunFlower::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    else if (++counter >= time)
    {
        counter = 0;
        scene()->addItem(new Sun(pos()));
    }
}
