#include "whackgame.h"
#include "ui_whackgame.h"

int Whackgame::ZOMBIE_GEN_TIMES_NOW = 0;
int Whackgame::zom_time = GEN_ONE_TIME;
int Whackgame::zom_cnt = 0;

pair<int,int> digzom_point[10] = {
    {380, 225},{340, 320},{556, 300},{238, 385},{464, 410},{102, 460},{301, 485},{486, 492}
};

Whackgame::Whackgame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Whackgame),
    socre(0)
{
    ui->setupUi(this);

//设置背景图片
    QPalette pa(this->palette());
    QImage img = QImage(":/new/prefix1/imag/whack_background.jpg");
    img = img.scaled(this->size());
    QBrush *pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);

//开始检测鼠标位置
    connect(this, SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(hammer_move(QMouseEvent *)));

//该类及其各父类都要设置
    this->setMouseTracking(true);
    QWidget::setMouseTracking(true);

//随机数种子 音乐 定时器
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));

    Music music("qrc:/new/prefix1/music/QukMc.mp3");

    timer = new QTimer(this);
    timer2 = new QTimer(this);
    startSound = new QMediaPlayer(this);
//绑定信号和槽函数
    connect(timer, &QTimer::timeout, this, &Whackgame::check);
    connect(timer2, &QTimer::timeout, this, &Whackgame::addZombie);

//加入锤子
    hammer = new Hammer(timer, timer2);
    hammer->setParent(this);
    hammer->move(-100, -100);
    hammer->setMouseTracking(true);
    hammer->show();

    connect(hammer, &Hammer::hammer_clicked, this, &Whackgame::hammer_clicked_slot);
    connect(hammer, &Hammer::back_mainwi, [=](){
        this->close();
    });
//播放音乐，启动定时器等等
    music.play();
    timer->start(1000);
    timer2->start(33);
    hammer->raise();

    ui->time_lcd->setDigitCount(3);
    ui->time_lcd->display(QString::number(time - cnt));
    ui->score_lcd->setDigitCount(4);

    ui->label->raise();
    ui->label_2->raise();
    QTimer::singleShot(3000, [=](){
        ui->label->hide();
        ui->label_2->hide();
    });
}

Whackgame::~Whackgame()
{
    delete ui;
    delete sound;
    delete timer;
    delete menubutton;
    delete hammer;
    delete pic;
    delete me;
}

void Whackgame::addZombie()
{
    if (ZOMBIE_GEN_TIMES_NOW < ZOMBIE_GEN_TIMES){
        if (++zom_cnt >= zom_time){
            ZOMBIE_GEN_TIMES_NOW++;
            zom_cnt = 0;
            int x = qrand() % 8;
            DiggerZombie *digger_zombie = new DiggerZombie(x);//参数表示 该僵尸生成在第几个洞
            digger_zombie->setParent(this);
            digger_zombie->setMouseTracking(true);
            digger_zombie->move(digzom_point[x].first,digzom_point[x].second);
            digger_zombie->lower();
            connect(this, SIGNAL(knock(int)),digger_zombie,SLOT(is_knock(int)));
            digger_zombie->show();
            hole[x] = true;
            QTimer::singleShot(800, [=](){
                hole[x] = false;
            });
        }
    }
}

void Whackgame::check()
{
    ui->time_lcd->display(QString::number(time - cnt - 1));
    if (++cnt >= time){
        //游戏结束
        timer->stop();
        timer2->stop();
        Music music;
        music.stop();

        QString a = "您的最终得分为：\n" + QString::number(socre);
        QMessageBox::information(this, "游戏结束", a);
        //返回主界面
        this->close();
        music.setmusic("qrc:/new/prefix1/music/MainJM.mp3");
        music.play();
    }
}

void Whackgame::juicy()
{
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/juicy.mp3"));  //将音乐文件添加到播放列表中
    startSound->play();
}

void Whackgame::hammer_move(QMouseEvent *ev)
{
    me = static_cast<QMouseEvent*>(ev);
    hammer->raise();
    hammer->move(me->pos().x() - 20, me->pos().y() - 40);
    xx = me->pos().x() - 20, yy = me->pos().y() - 40;
}

void Whackgame::hammer_clicked_slot()
{
    //{380, 225},{340, 320},{556, 300},{238, 385},{464, 410},{102, 460},{301, 485},{486, 492}
    for(int i = 0 ; i < 8; i ++ ){
        if (xx >= digzom_point[i].first - 30 && xx <= digzom_point[i].first + 100 &&
                yy >= digzom_point[i].second - 40 && yy <= digzom_point[i].second + 80 && hole[i]){
            hole[i] = false;
            emit knock(i);
            socre++;
            ui->score_lcd->display(socre);
            juicy();
        }
    }
}

void Whackgame::mouseMoveEvent(QMouseEvent *ev)
{
    emit mouseMove(ev);
}
