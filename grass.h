#ifndef GRASS_H
#define GRASS_H

#include <iostream>
#include <cstring>
#include <QObject>
#include <QDebug>

using namespace std;

class Grass
{
public:
    Grass();
    QString yinyin = ":/new/prefix1/imag/plantshadow.png";//每个植物下面都需要一个阴影，因为在坚果保龄球模式中发现碰撞是根据阴影判断的
    bool determine(int x, int y, int plant_number);//根据给定的坐标判断是否可以在这个区域的草坪上种植
    pair<int,int> fun(int x, int y);
    void clear();

};

#endif // GRASS_H
/*
草坪类，用来判断草地上某一块草地是否已种植了植物，通过调用草坪类中的 int is_plant[5][9]

    先判断鼠标位置，如果处于某一块草坪，并且手中拿了一株植物，那么该块草坪的正中央会显示一个该植物的虚影

                                   如果手中没有拿植物，那么没有反应

                                   如果拿了一把铲子，并且该块草坪上有植物
                                        点击左键会删除该植物




















*/

