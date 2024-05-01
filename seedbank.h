#ifndef SEEDBANK_H
#define SEEDBANK_H

#include <iostream>
#include <vector>
#include <cstring>
#include "init.h"

using namespace std;

class Seedbank
{
public:
    Seedbank();
    void set_sun();
    int get_sun();
    void add_sun(int val);
    void sub_sun(int val);
    int getsize();
    void choose_this_plant(int number);
    void back_this_plant(int number);
    void clear();
    int getd(int idx);
    bool is_occupied[10];//判断植物槽从0开始往下，是否被占用
    int plant_id[10];//plant_id[i]判断植物序号i若被选择，值为在第几个植物槽   若没有被选择，是-1
};

#endif // SEEDBANK_H
