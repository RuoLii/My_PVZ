#ifndef DIGGERZOMBIE_H
#define DIGGERZOMBIE_H

#include <QLabel>
#include <QTimer>

class DiggerZombie : public QLabel
{
    Q_OBJECT
public:
    DiggerZombie(int id);
    ~DiggerZombie();
    void zombie_disapear();
    int id;

private:
    QTimer *timer;

private slots:
    void is_knock(int id);
};

#endif // DIGGERZOMBIE_H
