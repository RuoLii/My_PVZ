#include "plant_cardbutton.h"

Plant_cardbutton::Plant_cardbutton(QString normal, int number)
{
    this->normal_img = normal;
    this->plant_number = number;
    QPixmap map;
    bool flag = map.load(normal);
    if(!flag){
        qDebug() << "图片加载失败！";
        return;
    }else{
        qDebug() << "图片加载成功！";

        //设置图片大小
        this->setFixedSize(map.width(), map.height());//设置按钮的固定大小为图片的大小;
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");//设置按钮为图片的形状
        //设置图片
        this->setIcon(map);
        //设置图标大小
        this->setIconSize(QSize(map.width(),map.height()));
    }
}

void Plant_cardbutton::sound1()
{
    QMediaPlayer *startSound = new QMediaPlayer(this);
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/seedlift.wav"));  //将音乐文件添加到播放列表中
    startSound->play();
}

void Plant_cardbutton::sound2()
{
    QMediaPlayer *startSound = new QMediaPlayer(this);
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/plant.wav"));  //将音乐文件添加到播放列表中
    startSound->play();
}
