#include "diggerzombie.h"

DiggerZombie::DiggerZombie(int id)
{
    this->id = id;
    QImage img(":/new/prefix1/imag/digger_zombie.png");
    this->setPixmap(QPixmap::fromImage(img));
    this->resize(img.width(), img.height());

    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &DiggerZombie::zombie_disapear);
    timer->start(800);
}

DiggerZombie::~DiggerZombie()
{
    delete timer;
}

void DiggerZombie::zombie_disapear()
{
    this->close();
}

void DiggerZombie::is_knock(int id)
{
    if (id == this->id)
        delete this;
}
