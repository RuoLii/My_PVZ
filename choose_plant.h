#ifndef CHOOSE_PLANT_H
#define CHOOSE_PLANT_H

#include <QWidget>
#include <menu.h>
#include <music.h>
#include <logonbutton.h>
#include <choose_plantbutton.h>
#include <seedbank.h>


namespace Ui {
class Choose_plant;
}

class Choose_plant : public QWidget
{
    Q_OBJECT

public:
    explicit Choose_plant(QWidget *parent = nullptr);
    ~Choose_plant();

private:
    Ui::Choose_plant *ui;
    Choose_plantbutton *peashooter;
    Choose_plantbutton *sunflower;
    Choose_plantbutton *cherry_bomb;
    Choose_plantbutton *wall_nut;
    Choose_plantbutton *potato_mine;
    Choose_plantbutton *snowshooter;
    Logonbutton *menubutton;
    Logonbutton *lets_rockbutton;
    Seedbank seedbank;


private slots:
    void continue_music();
    void to_mainwi();
    void mancao();
    void dis_mancao();

signals:
    void game_start();

};

#endif // CHOOSE_PLANT_H
