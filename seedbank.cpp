#include "seedbank.h"

vector<int> d;

Seedbank::Seedbank()
{
    for(int i = 0; i < 10; i ++ ){
        plant_id[i] = -1;
        is_occupied[i] = false;
    }
}

int Seedbank::getsize()
{
    if(d.empty())return 0;
    return d.size();
}

void Seedbank::choose_this_plant(int number)
{
    d.push_back(number);
}

void Seedbank::back_this_plant(int number)
{
    swap(d[number], d[d.size() - 1]);
    d.pop_back();
    for(int i = number; i < int(d.size() - 1); i ++ )
        swap(d[i], d[i + 1]);
}

void Seedbank::clear()
{
    d.clear();
    for(int i = 0 ; i < 10; i ++ ){
        is_occupied[i] = false;
        plant_id[i] = -1;
    }
}

int Seedbank::getd(int idx)
{
    return d[idx];
}
