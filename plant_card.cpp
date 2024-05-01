#include "plant_card.h"

#include <iostream>

using namespace std;

//根据植物序号在数组中获取对应的属性
QString img[100] = {
    ":/new/prefix1/imag/Shovel.png",":/new/prefix1/imag/peashooter_1.jpg",":/new/prefix1/imag/sunflower_1.jpg",":/new/prefix1/imag/cherryboom_1.jpg",
    ":/new/prefix1/imag/wallnut_1.jpg",":/new/prefix1/imag/dilei_1.jpg",":/new/prefix1/imag/snowshooter_1.jpg"
};

QString img2[100] = {
    ":/new/prefix1/imag/Shovel.png",":/new/prefix1/imag/peashooter.gif",":/new/prefix1/imag/sunflower.gif",":/new/prefix1/imag/cherrybomb.gif",
    ":/new/prefix1/imag/wallnut.gif",":/new/prefix1/imag/potatodilei_ready.gif",":/new/prefix1/imag/snowshooter.gif"
};

int cd[100] = {
    0, cooltime_Peashooter, cooltime_SunFlower, cooltime_CherryBomb, cooltime_WallNut, cooltime_PotatoMine, cooltime_SnowPea
};

int initial_cd[100] = {
    0, cooltime_Peashooter, cooltime_SunFlower, 0, 0, 0,cooltime_SnowPea
};

int spend[100] = {
    0, 100, 50, 150, 50, 25, 175
};

int blood[100] = {
    0, 300, 300, 300, 4000, 300, 300
};


Plant_card::Plant_card(int plant_id, int x, int y)
{
    counter = 0;//冷却时间
    if (initial_cd[plant_id] == cd[plant_id])
        is_ok = true;
    else
        is_ok = false;
    this->plant_id = plant_id;
    this->plant_img = img[plant_id];
    this->plant_img2 = img2[plant_id];
    this->plant_cd = cd[plant_id];
    this->plant_initial_cd = initial_cd[plant_id];
    this->plant_spend = spend[plant_id];
    this->is_pick = false;
    this->x = x;
    this->y = y;

    //加载按钮图片
    QPixmap map;
    map.load(plant_img);
    this->setFixedSize(map.width(), map.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(map);
    this->setIconSize(QSize(map.width(),map.height()));

    startSound = new QMediaPlayer(this);
}

Plant_card::~Plant_card()
{
    delete me;
    delete startSound;
}

bool Plant_card::event(QEvent *ev)
{
    // 筛选鼠标按钮被按压事件
    if(ev->type() == QEvent::MouseButtonPress)
    {
        // 创建鼠标事件的对象
        me = static_cast<QMouseEvent*>(ev);
        // 鼠标按键事件   单个触发用 button
        if(me->button() & Qt::LeftButton)//左键
        {
            if (is_pick == false){
                //发出一个卡片选择的声音
                if (plant_id == 0) shovel_put_sound();
                else choose_sound();
                //按钮变形成植物的模样
                this->setIcon(QIcon(plant_img2));
                is_pick = true;
            }else {
                //按钮变回卡片的模样,并回去
                this->setIcon(QIcon(plant_img));
                this->move(x,y);
                emit ready_to_plant(plant_id);
                qDebug() << "发送植物序号：" << plant_id;
                is_pick = false;
            }

        }//右键
        if(me->button() & Qt::RightButton)
        {
            if (is_pick == false){
                //发出一个卡片选择的声音
                if (plant_id == 0) shovel_put_sound();
                else choose_sound();
                //按钮变形成植物的模样
                this->setIcon(QIcon(plant_img2));
                is_pick = true;
            }else{
                //右键是取消植物
                //发出一个取消植物的音效
                put_sound();
                //按钮变回卡片的模样
                this->setIcon(QIcon(plant_img));
                this->move(x,y);

                is_pick = false;
            }
        }
        if(me->button() & Qt::MidButton)
        {
            //效果和左键相同
            if (is_pick == false){
                //发出一个卡片选择的声音
                if (plant_id == 0) shovel_put_sound();
                else choose_sound();
                //按钮变形成植物的模样
                this->setIcon(QIcon(plant_img2));
                is_pick = true;
            }else {
                //按钮变回卡片的模样,并回去
                this->setIcon(QIcon(plant_img));
                this->move(x,y);
                emit ready_to_plant(plant_id);
                qDebug() << "发送植物序号：" << plant_id;
                is_pick = false;
            }
        }
    }

    return QWidget::event(ev);
}

void Plant_card::choose_sound()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/seedlift.mp3"));
    startSound->play();
}

void Plant_card::plant_sound()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/plant.mp3"));
    startSound->play();
}

void Plant_card::put_sound()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/tap2.mp3"));
    startSound->setVolume(150);
    startSound->play();
}

void Plant_card::shovel_put_sound()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/shovel.mp3"));
    startSound->play();
}

void Plant_card::cooltime_slot()
{
    if (is_ok)
        return;
    if (counter < cd[plant_id])
        counter++;
    else{
        is_ok = true;
        counter = 0;
    }
}

void Plant_card::compare_with_sun(int num)
{
    if (num >= plant_spend && is_ok)
        this->show();
    else this->hide();
}
