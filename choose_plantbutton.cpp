#include "choose_plantbutton.h"

Choose_plantbutton::Choose_plantbutton(QString normal, int number, bool is_choose)
{
    this->normal_img = normal;
    this->plant_number = number;
    this->is_choose = is_choose;
    QPixmap map;
    map.load(normal);
    this->setFixedSize(map.width(), map.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(map);
    this->setIconSize(QSize(map.width(),map.height()));
    startSound = new QMediaPlayer(this);
}

Choose_plantbutton::~Choose_plantbutton()
{
    delete startSound;
}

void Choose_plantbutton::sound()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/tap.mp3"));  //将音乐文件添加到播放列表中
    startSound->play();
}

