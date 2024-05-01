#ifndef LOGONBUTTON_H
#define LOGONBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QMediaPlayer>
#include <QEvent>

class Logonbutton : public QPushButton
{
    Q_OBJECT
public:
    Logonbutton(QString normal,QString press = "",bool is_sound4 = false);//构造函数
    ~Logonbutton();
    QString normal_img;//正常路径
    QString press_img;//按下路径
    bool event(QEvent *event);
    bool is_sound4;//判断 当鼠标进入时，是否需要播放sound4
    void move1(int val);
    void move2(int val);
    void sound1();
    void sound2();
    void sound3();
    void sound4();
    void sound5();
private:
    QMediaPlayer *startSound;
};

#endif // LOGONBUTTON_H
