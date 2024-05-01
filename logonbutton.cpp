#include "logonbutton.h"

Logonbutton::Logonbutton(QString normal, QString press,bool is_sound4)
{
    this->normal_img = normal;//自定义按钮的图片路径
    this->press_img = press;
    this->is_sound4 = is_sound4;
    QPixmap map;
    map.load(normal);
    this->setFixedSize(map.width(), map.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(map);
    this->setIconSize(QSize(map.width(),map.height()));
    startSound = new QMediaPlayer(this);
}

Logonbutton::~Logonbutton()
{
    delete startSound;
}

bool Logonbutton::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Enter:
        this->setIcon(QIcon(press_img));
        if (is_sound4) sound4();
        break;
    case QEvent::Leave:
        this->setIcon(QIcon(normal_img));
        break;
    case QEvent::MouseButtonPress:
        this->setIcon(QIcon(press_img));
        break;
    case QEvent::MouseButtonRelease:
        this->setIcon(QIcon(press_img));
        break;
    default:
        break;
    }
    return QPushButton::event(event);
}

void Logonbutton::move1(int val)
{
    QPixmap map;
    map.load(press_img);
    this->setFixedSize(map.width(), map.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(map);
    this->setIconSize(QSize(map.width(),map.height()));
    QPoint w = this->pos();
    w.setX(w.x() + val);
    w.setY(w.y() + val);
    this->move(w);
    //    qDebug() << "已移动！";
}

void Logonbutton::move2(int val)
{
    QPixmap map;
    map.load(normal_img);

    //设置图片大小
    this->setFixedSize(map.width(), map.height());//设置按钮的固定大小为图片的大小;
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");//设置按钮为图片的形状
    //设置图片
    this->setIcon(map);
    //设置图标大小
    this->setIconSize(QSize(map.width(),map.height()));

    QPoint w = this->pos();
    w.setX(w.x() - val);
    w.setY(w.y() - val);
    this->move(w);
}

void Logonbutton::sound1()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/gravebutton.mp3"));  //将音乐文件添加到播放列表中
    startSound->play();
}

void Logonbutton::sound2()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/tap.mp3"));
    startSound->play();
}

void Logonbutton::sound3()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/buttonclick.mp3"));
    startSound->play();
}

void Logonbutton::sound4()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/bleep.mp3"));
    startSound->play();
}

void Logonbutton::sound5()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/pause.mp3"));
    startSound->play();
}


