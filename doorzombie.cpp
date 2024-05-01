#include "doorzombie.h"

DoorZombie::DoorZombie(int row, int col)
{
    this->row = row;
    this->col = col;
    movie = new QMovie(":/new/prefix1/imag/door_zombie.gif");
    this->setMovie(movie);
    movie->start();

    for (int i = 0; i < 5; i ++ )
        for (int j = 0; j < 9; j ++ )
            map_[i][j] = 0;
    for(int i = 1; i < 5; i ++ )
        for(int j = 0; j < 2; j ++ )
            map_[i][j] = -1;
    map_[0][4] = 1, map_[0][7] = -1, map_[0][8] = -1;
    map_[1][7] = -1,map_[1][8] = -1;
    map_[2][2] = 1,map_[2][3] = 1,map_[2][4] = 2,map_[2][5] = 2,map_[2][8] = -1;
    map_[3][4] = 1,map_[3][6] = 1,map_[3][7] = 2,map_[3][8] = -1;
    map_[4][2] = -1,map_[4][7] = 2,map_[4][8] = -1;
}

DoorZombie::~DoorZombie()
{
    delete movie;
}

void DoorZombie::keyPressEvent(QKeyEvent *ev)
{
    switch (ev->key())
    {
    case Qt::Key_Up://上
    case Qt::Key_W:
        if (map_[row - 1][col] == -1 || row == 0)//水池
            return;
        else if (map_[row - 1][col] == 2){//陷阱
            row--;
            emit move_to_here(row, col);
            emit game_over();
        }
        else if (map_[row - 1][col] == 1){//坚果
            auto s = map_[row - 2][col];
            if (row - 2 < 0 || s == -1 || s == 2 || s == 1)
                return;
            else{
                row--;
                emit push_wallnut(row, col, 1);
                map_[row][col] = 0;
                map_[row - 1][col] = 1;
            }
        }else
            row--;
        break;
    case Qt::Key_Down://下
    case Qt::Key_S:
        if (map_[row + 1][col] == -1 || row == 4)//水池
            return;
        else if (map_[row + 1][col] == 2){//陷阱
            row++;
            emit move_to_here(row, col);
            emit game_over();
        }
        else if (map_[row + 1][col] == 1){//坚果
            auto s = map_[row + 2][col];
            if (row + 2 > 4 || s == -1 || s == 2 || s == 1)
                return;
            else{
                row++;
                emit push_wallnut(row, col, 2);
                map_[row][col] = 0;
                map_[row + 1][col] = 1;
            }
        }
        else
            row++;
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if (map_[row][col - 1] == -1 || col == 0)//水池
            return;
        else if (map_[row][col - 1] == 2){//陷阱
            col--;
            emit move_to_here(row, col);
            emit game_over();
        }
        else if (map_[row][col - 1] == 1){//坚果
            auto s = map_[row][col - 2];
            if (col - 2 < 0 || s == -1 || s == 2 || s == 1)
                return;
            else{
                col--;
                emit push_wallnut(row, col, 3);
                map_[row][col] = 0;
                map_[row][col - 1] = 1;
            }
        }
        else
            col--;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        if (map_[row][col + 1] == -1 || col == 8)//水池
            return;
        else if (map_[row][col + 1] == 2){//陷阱
            col++;
            emit move_to_here(row, col);
            emit game_over();
        }
        else if (map_[row][col + 1] == 1){//坚果
            auto s = map_[row][col + 2];
            if (col + 2 > 8 || s == -1 || s == 2 || s == 1)
                return;
            else{
                col++;
                emit push_wallnut(row, col, 4);
                map_[row][col] = 0;
                map_[row][col + 1] = 1;
            }
        }
        else
            col++;
        break;
    }
    emit move_to_here(row, col);
    emit check();
}
