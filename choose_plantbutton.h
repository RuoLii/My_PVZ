#ifndef CHOOSE_PLANTBUTTON_H
#define CHOOSE_PLANTBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QMediaPlayer>
#include <QEvent>
#include <seedbank.h>


class Choose_plantbutton : public QPushButton
{
    Q_OBJECT
public:
    Choose_plantbutton(QString normal, int number, bool is_choose = false);
    ~Choose_plantbutton();
//    bool event(QEvent *event);
    void sound();

public:
    QString normal_img;//图片路径
    bool is_choose;
    int plant_number;

private:
    QMediaPlayer *startSound;
};

#endif // CHOOSE_PLANTBUTTON_H
