#ifndef HAMMER_H
#define HAMMER_H

#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>
#include <QEventLoop>
#include <QTime>
#include <QTimer>
#include <QCoreApplication>
#include <QMediaPlayer>
#include <music.h>

class Hammer : public QPushButton
{
    Q_OBJECT
public:
    Hammer(QTimer *timer, QTimer *timer2, QWidget *parent = nullptr);
    ~Hammer();
    bool event(QEvent *ev);
    void Sleep(int msec);
    void hammer_sound();

private:
    QMouseEvent * me;
    QMediaPlayer *startSound;
    QTimer *timer;
    QTimer *timer2;

signals:
    void hammer_clicked();
    void back_mainwi();
};

#endif // HAMMER_H
