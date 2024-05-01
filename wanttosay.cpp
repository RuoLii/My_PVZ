#include "wanttosay.h"
#include "ui_wanttosay.h"

WantToSay::WantToSay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WantToSay)
{
    ui->setupUi(this);
    QPalette pa(this->palette());
    QImage img = QImage(":/new/prefix1/imag/Almanac_GroundDay.jpg");
    img = img.scaled(this->size());
    pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);

    //创建返回主页面按钮==================================
        back_main_menubutton = new Logonbutton(QString(":/new/prefix1/imag/tree_main_button_1.png"), QString(":/new/prefix1/imag/tree_main_button_2.png"));
        back_main_menubutton->setParent(this);
        back_main_menubutton->move(630,0);
        connect(back_main_menubutton, &Logonbutton::pressed,[=](){
            back_main_menubutton->move1(1);
            back_main_menubutton->sound1();
        });
        connect(back_main_menubutton, &Logonbutton::released,[=](){
           back_main_menubutton->move2(1);
           this->close();
           Music music("qrc:/new/prefix1/music/MainJM.mp3");
           music.play();
        });

        Music music("qrc:/new/prefix1/music/flowery.mp3");
        music.play();
}

WantToSay::~WantToSay()
{
    delete ui;
    delete pic;
}
