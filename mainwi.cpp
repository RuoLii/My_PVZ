#include "mainwi.h"
#include "ui_mainwi.h"

MainWi::MainWi(bool state, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWi)
{
    ui->setupUi(this);

    //设置背景图片
    QPalette pa(this->palette());
    QImage img = QImage(":/new/prefix1/imag/denglu.png");
    img = img.scaled(this->size());
    pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);

    Music music("qrc:/new/prefix1/music/MainJM.mp3");
    music.play();


    //这里之后写：如果判断是第一次登录的话，创建登录子窗口对象↓↓↓↓↓

    //.创建登录子窗口对象
    logon = new Logon(this);
    //.显示登录界面
    logon->move(100,45);
    logon->hide();

    //创建huchulogonbutton
    huchulogonbutton = new Logonbutton(QString(":/new/prefix1/imag/huchulogon_1.png"), QString(":/new/prefix1/imag/huchulogon_2.png"), 1);
    huchulogonbutton->setParent(this);
    huchulogonbutton->move(25, 125);
    huchulogonbutton->hide();//先隐藏
    connect(huchulogonbutton, &Logonbutton::pressed, [=](){
        huchulogonbutton->move1(0);
        huchulogonbutton->sound2();
    });
    connect(huchulogonbutton, &Logonbutton::released,[=](){
        huchulogonbutton->move2(0);
    });

    //接受到 已选择用户的信号之后，显示huchulogonbutton
    connect(logon, SIGNAL(Complete_user_selection(int)),this,SLOT(showAllbutton_slot(int)));
    //给huchulogonbutton绑定一个信号槽，使release之后重新呼出logon界面
    connect(huchulogonbutton, &QPushButton::released, [=](){
        logon->raise();
        logon->show();
    });








    //墓碑上的按钮==============================

    //创建startbutton
    startbutton = new Logonbutton(QString(":/new/prefix1/imag/startbutton_1.png"), QString(":/new/prefix1/imag/startbutton_2.png"),1);
    startbutton->setParent(this);
    startbutton->move(405, 64);
    startbutton->hide();//先隐藏
    connect(startbutton, &Logonbutton::pressed, [=](){
        startbutton->move1(1);
        startbutton->sound1();
    });
    connect(startbutton, &Logonbutton::released,[=](){
       startbutton->move2(1);
       //进入经典游戏界面---
        Day *day = new Day(this);
        day->show();
    });

    //创建mini_gamesbutton
    mini_gamesbutton = new Logonbutton(QString(":/new/prefix1/imag/mini_gamesbutton_1.png"), QString(":/new/prefix1/imag/mini_gamesbutton_2.png"),1);
    mini_gamesbutton->setParent(this);
    mini_gamesbutton->move(406, 172);
    mini_gamesbutton->hide();//先隐藏
    connect(mini_gamesbutton, &Logonbutton::pressed, [=](){
        mini_gamesbutton->move1(1);
        mini_gamesbutton->sound1();
    });
    connect(mini_gamesbutton, &Logonbutton::released,[=](){
       mini_gamesbutton->move2(1);
       //打地鼠
        Whackgame *wak = new Whackgame(this);
        wak->show();

    });

    //创建puzzlebutton
    puzzlebutton = new Logonbutton(QString(":/new/prefix1/imag/puzzlebutton_1.png"), QString(":/new/prefix1/imag/puzzlebutton_2.png"),1);
    puzzlebutton->setParent(this);
    puzzlebutton->move(410, 256);
    puzzlebutton->hide();//先隐藏
    connect(puzzlebutton, &Logonbutton::pressed, [=](){
        puzzlebutton->move1(1);
        puzzlebutton->sound1();
    });
    connect(puzzlebutton, &Logonbutton::released,[=](){
       puzzlebutton->move2(1);
       //推箱子
       Sokoban *sok = new Sokoban(this);
       sok->show();
    });

    //创建survivalbutton
    survivalbutton = new Logonbutton(QString(":/new/prefix1/imag/survivalbutton_1.png"), QString(":/new/prefix1/imag/survivalbutton_2.png"),1);
    survivalbutton->setParent(this);
    survivalbutton->move(412, 327);
    survivalbutton->hide();//先隐藏
    connect(survivalbutton, &Logonbutton::pressed, [=](){
        survivalbutton->move1(1);
        survivalbutton->sound1();
    });
    connect(survivalbutton, &Logonbutton::released,[=](){
       survivalbutton->move2(1);
       //这里原游戏是白天 黑夜 泳池白天 泳池黑夜 无尽泳池白天---
       QMessageBox::information(this, "抱歉", "该游戏模式正火速开发中\n敬请期待！");
    });

    //右下角花瓶上的按钮============
        //创建optionsbutton
    optionsbutton = new Logonbutton(QString(":/new/prefix1/imag/SelectorScreen_Options1.png"), QString(":/new/prefix1/imag/SelectorScreen_Options2.png"),1);
    optionsbutton->setParent(this);
    optionsbutton->move(566, 490);
    optionsbutton->hide();//先隐藏
    connect(optionsbutton, &Logonbutton::pressed, [=](){
        optionsbutton->move1(0);
        optionsbutton->sound2();
    });
    connect(optionsbutton, &Logonbutton::released,[=](){
       optionsbutton->move2(0);
       //团队介绍
       WantToSay *wan = new WantToSay(this);
       wan->show();
    });
        //创建helpbutton
    helpbutton = new Logonbutton(QString(":/new/prefix1/imag/SelectorScreen_Help1.png"), QString(":/new/prefix1/imag/SelectorScreen_Help2.png"),1);
    helpbutton->setParent(this);
    helpbutton->move(647, 529);
    helpbutton->hide();//先隐藏
    connect(helpbutton, &Logonbutton::pressed, [=](){
        helpbutton->move1(0);
        helpbutton->sound2();
    });
    connect(helpbutton, &Logonbutton::released,[=](){
       helpbutton->move2(0);
       //智慧树
        Wisdom_tree *wis = new Wisdom_tree(this);
        wis->show();

    });
        //创建quitbutton
    quitbutton = new Logonbutton(QString(":/new/prefix1/imag/SelectorScreen_Quit1.png"), QString(":/new/prefix1/imag/SelectorScreen_Quit2.png"),1);
    quitbutton->setParent(this);
    quitbutton->move(720, 515);
    quitbutton->hide();//先隐藏
    connect(quitbutton, &Logonbutton::pressed, [=](){
        quitbutton->move1(0);
        quitbutton->sound2();
    });
    connect(quitbutton, &Logonbutton::released,[=](){
       quitbutton->move2(0);

       int op = QMessageBox::question(this,"退出","您确定要退出游戏吗？", QMessageBox::Ok, QMessageBox::Cancel);
       if (op == QMessageBox::Ok)
           this->close();
    });















    if (state == false){
        logon->show();
    }else{
        qDebug()<<"已显示";
        showAllbutton_slot(user_idx);
    }
    seedbank.clear();
}

MainWi::~MainWi()
{
    delete ui;
    delete pic;
    delete logon;
    delete huchulogonbutton;
    delete startbutton;
    delete mini_gamesbutton;
    delete puzzlebutton;
    delete survivalbutton;
    delete optionsbutton;
    delete helpbutton;
    delete quitbutton;
}

void MainWi::showAll()
{

}

void MainWi::showAllbutton_slot(int idx)
{
    user_idx = idx;
    huchulogonbutton->show();
    startbutton->show();
    mini_gamesbutton->show();
    puzzlebutton->show();
    survivalbutton->show();
    optionsbutton->show();
    helpbutton->show();
    quitbutton->show();
}

