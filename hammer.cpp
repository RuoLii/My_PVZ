#include "hammer.h"

Hammer::Hammer(QTimer *timer, QTimer *timer2, QWidget *parent)
    : QPushButton(parent)
{
    this->timer = timer;
    this->timer2 = timer2;
    //加载按钮图片
    QPixmap map1;
    map1.load(":/new/prefix1/imag/hammer.png");
    this->setFixedSize(map1.width(), map1.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(map1);
    this->setIconSize(QSize(map1.width(),map1.height()));

    startSound = new QMediaPlayer(this);
}

Hammer::~Hammer()
{
    delete me;
    delete startSound;
}

bool Hammer::event(QEvent *ev)
{
    if(ev->type() == QEvent::MouseButtonPress)
    {
        me = static_cast<QMouseEvent*>(ev);
        if(me->button() & Qt::LeftButton){//左键锤子的敲击
            QPixmap map2;
            map2.load(":/new/prefix1/imag/hammer_2.png");
            this->setFixedSize(map2.width(), map2.height());
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(map2);
            this->setIconSize(QSize(map2.width(),map2.height()));

            emit hammer_clicked();

            hammer_sound();

            Sleep(100);

            QPixmap map1;
            map1.load(":/new/prefix1/imag/hammer.png");
            this->setFixedSize(map1.width(), map1.height());
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(map1);
            this->setIconSize(QSize(map1.width(),map1.height()));
            this->show();
        }else if (me->button() & Qt::RightButton){//右键跳出菜单，暂停游戏
            if (timer->isActive() && timer2->isActive()){
                timer->stop();
                timer2->stop();
                Music music("qrc:/new/prefix1/music/MainJM.mp3");
                music.play();
                emit back_mainwi();
            }
        }

    }
    return QWidget::event(ev);
}

void Hammer::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Hammer::hammer_sound()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/swing.mp3"));  //将音乐文件添加到播放列表中
    startSound->play();
}
