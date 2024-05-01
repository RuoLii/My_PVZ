#ifndef DOORZOMBIE_H
#define DOORZOMBIE_H

#include <QLabel>
#include <QMovie>
#include <QKeyEvent>

using namespace std;

class DoorZombie : public QLabel
{
    Q_OBJECT
public:
    DoorZombie(int row, int col);
    ~DoorZombie();
    void keyPressEvent(QKeyEvent *ev);
    int row;
    int col;
    int map_[5][9];
private:
    QMovie *movie;
signals:
    void move_to_here(int row, int col);
    void game_over();
    void push_wallnut(int row, int col, int op);//op代表操作，1上2下3左4右
    void check();//每次移动之后判断是否游戏胜利
};

#endif // DOORZOMBIE_H
