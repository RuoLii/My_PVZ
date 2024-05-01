#ifndef PLANT_CARDBUTTON_H
#define PLANT_CARDBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QMediaPlayer>

class Plant_cardbutton : QPushButton
{
    Q_OBJECT
public:
    Plant_cardbutton(QString normal, int number);
    void sound1();
    void sound2();

public:
    QString normal_img;
    bool is_choose;
    int plant_number;

};

#endif // PLANT_CARDBUTTON_H
