#ifndef PLANT_CARD_H
#define PLANT_CARD_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QMediaPlayer>
#include <QEvent>
#include <QMouseEvent>
#include "init.h"

class Plant_card : public QPushButton
{
    Q_OBJECT
public:
    Plant_card(int plant_id, int x ,int y);
    ~Plant_card();
    bool event(QEvent *ev);
    int plant_id;//植物序号
    QString plant_img;//植物卡片的图片
    QString plant_img2;//植物的图片
    int plant_cd;//植物冷却时间
    int plant_initial_cd;//植物初始冷却时间
    int plant_spend;//植物价格
    bool is_pick;//植物被拿起
    bool is_ok;//cd已冷却
    //植物卡片在本次游戏中的，在植物槽中的坐标
    int x;
    int y;
    int counter;
public://按钮声音
    void choose_sound();
    void plant_sound();
    void put_sound();
    void shovel_put_sound();
signals:
    void ready_to_plant(int num);
private slots:
    void cooltime_slot();
    void compare_with_sun(int num);//接收到阳光数量，和阳光数量比较大小，如果 >= 阳光数量 并且冷却到了， 则显示
private:
    QMouseEvent * me;
    QMediaPlayer *startSound;

};

#endif // PLANT_CARD_H

//游戏开始时，会有一个定时器开始记时，此时植物的冷却时间 plant_initial_cd 开始减少，每秒减少 1
//当 plant_initial_cd 减少到 0 时，判断 seedbank 中的阳光类 sum_number 是否大于等于 这株植物的价格 plant_spend
//如果大于等于，那么就可以种植了：所以此时按钮就会显示 show() 当上述条件有其中一个未满足时，按钮都不会显示。
//按钮在显示状态下时，鼠标进行操作会有反应
//按钮有一个属性叫：is_pick 是否拿起，初始值为 false.
//当鼠标pressed按钮时，判断是否是 is_pick 如果 is_pick == false 那就拿起植物卡片
// if (is_pick == false  （左键或者右键都可以）){
        //发出一个卡片选择的声音
        //按钮开始跟随鼠标一起移动，
// }
//


//应该判断鼠标是左键 pressed 按钮了，还是右键 pressed 按钮了
//如果是左键 pressed 按钮=============================================================
/*
if (is_pick == false){
    发出一个卡片选择的声音
    按钮开始跟随鼠标一起移动，
    发出一个已选择物品的信号，并且参数为植物序号

    {(改变is_pick)}
}else {
        //判断是否在草坪上，并且满足草坪的种植规则
            //如果满足草坪的种植规则，那就直接种上去了
            //发出一个植物种植的声音

            //按钮不再跟随鼠标一起移动，move回seedbank中，隐藏hide()
            //开始冷却(开始冷却的意思就是让plant_initial_cd = plant_cd)


            //plant_initial_cd = plant_cd，并且每一秒 plant_initial_cd --;

            //如果不满足草坪的种植规则，或者不在草坪上，按钮返回

        //如果没有在草坪上，放回 seedbank 中：：：：：按钮不再跟随鼠标一起移动，move 回 seedbank 中  {(改变is_pick)}
}
*/

//如果是右键 pressed 按钮============================================================
/*
if (is_pick == false){
    发出一个卡片选择的声音
    按钮开始跟随鼠标一起移动，（效果和左键 pressed 一样）
    发出一个已选择物品的信号，并且参数为植物序号

    {(改变is_pick)}
}else{
    右键是放下植物
    //按钮不再跟随鼠标一起移动，move 回 seedbank 中

    {(改变is_pick)}
}
*/


//===================================================================
