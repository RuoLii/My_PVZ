#include "grass.h"

int have_plant[7][10];


Grass::Grass()
{
    memset(have_plant, 0, sizeof have_plant);

}

bool Grass::determine(int x, int y, int plant_number)
{

    int row = fun(x,y).first, col = fun(x,y).second;
    if (row < 0 || col < 0) return false;
    if (plant_number == 0){//它是铲子
        if (have_plant[row][col] != 0){//可以铲除，返回true
            have_plant[row][col] = 0;
            return true;
        }else
            return false;
    }else{//它是植物
        //判断这个位置是否可以种植
        if (have_plant[row][col] == 0){//可以种
            have_plant[row][col] = plant_number;
            return true;
        }else
            return false;
    }
    qDebug() << "第" << row << "行" << col << "列" ;
}

pair<int, int> Grass::fun(int x, int y)
{

    int row = -1, col = -1;
    // 40  122  197  284  362  449  529  606  683  765
    //判断列
    if (x >= 40 && x <= 122){
        col = 0;
    }else if (x >= 122 && x <= 197){
        col = 1;
    }else if (x >= 197 && x <= 284){
        col = 2;
    }else if (x >= 284 && x <= 362){
        col = 3;
    }else if (x >= 362 && x <= 449){
        col = 4;
    }else if (x >= 449 && x <= 529){
        col = 5;
    }else if (x >= 529 && x <= 606){
        col = 6;
    }else if (x >= 606 && x <= 683){
        col = 7;
    }else if (x >= 683 && x <= 765){
        col = 8;
    }
    // 90  183  281  388   480  575
    //判断行
    if (y >= 90 && y <= 183){
        row = 0;
    }else if (y >= 183 && y <= 281){
        row = 1;
    }else if (y >= 281 && y <= 388){
        row = 2;
    }else if (y >= 388 && y <= 480){
        row = 3;
    }else if (y >= 480 && y <= 575){
        row = 4;
    }

    return {row, col};
}

void Grass::clear()
{
    memset(have_plant, 0, sizeof have_plant);
}
