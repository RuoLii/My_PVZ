#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    //设置背景图片
    QPalette pa(this->palette());
    QImage img = QImage(":/new/prefix1/imag/menu.png");
    img = img.scaled(this->size());
    pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);

    //创建back_to_gamebutton
    back_to_gamebutton = new Logonbutton(QString(":/new/prefix1/imag/back_to_gamebutton_1.png"), QString(":/new/prefix1/imag/back_to_gamebutton_2.png"));
    back_to_gamebutton->setParent(this);
    back_to_gamebutton->move(36,392);
    connect(back_to_gamebutton, &Logonbutton::pressed,[=](){
        back_to_gamebutton->move1(1);
        back_to_gamebutton->sound1();
    });
    connect(back_to_gamebutton, &Logonbutton::released,[=](){
       back_to_gamebutton->move2(1);
       //游戏继续
       emit game();
       this->close();
    });

    //创建back_main_menubutton
    back_main_menubutton = new Logonbutton(QString(":/new/prefix1/imag/back_main_menubutton_1.png"), QString(":/new/prefix1/imag/back_main_menubutton_2.png"));
    back_main_menubutton->setParent(this);
    back_main_menubutton->move(100,320);
    connect(back_main_menubutton, &Logonbutton::pressed,[=](){
        back_main_menubutton->move1(1);
        back_main_menubutton->sound1();
    });
    connect(back_main_menubutton, &Logonbutton::released,[=](){
       back_main_menubutton->move2(1);
       //返回主页面
       emit mainwi();
       this->close();
    });
}

Menu::~Menu()
{
    delete ui;
    delete pic;
    delete back_to_gamebutton;
    delete back_main_menubutton;
}
