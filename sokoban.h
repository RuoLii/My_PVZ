#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <QWidget>
#include <music.h>
#include <menu.h>
#include <logonbutton.h>
#include <QMovie>
#include <doorzombie.h>
#include <wallnutpush.h>

namespace Ui {
class Sokoban;
}

class Sokoban : public QWidget
{
    Q_OBJECT

public:
    explicit Sokoban(QWidget *parent = nullptr);
    ~Sokoban();

private:
    Ui::Sokoban *ui;
    QBrush *pic;
    Logonbutton *menubutton;
    QLabel *chomper;
    QLabel *potato_mine;
    QMovie *movie;
    DoorZombie *door_zombie;
    WallnutPush *wallnut;
    WallnutPush *wal[5];
    int map_[5][9];

private slots:
    void move_to_here_slot(int row, int col);
    void game_over_slot();
    void push_wallnut_slot(int row, int col, int op);
    void check_slot();
};

#endif // SOKOBAN_H
