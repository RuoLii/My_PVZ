#include "day.h"
#include "ui_day.h"

Music music1;

int plant_id[10];

//贴图用
QString plant_path1[10] = {"",
                           ":/new/prefix1/imag/peashooter_2.jpg",
                         ":/new/prefix1/imag/sunflower_2.jpg",
                         ":/new/prefix1/imag/cherryboom_2.jpg",
                         ":/new/prefix1/imag/wallnut_2.jpg",
                         ":/new/prefix1/imag/dilei_2.jpg",
                          ":/new/prefix1/imag/snowshooter_2.jpg"};

//button用
QString plant_path2[10] = {":/new/prefix1/imag/peashooter_1.jpg",
                          ":/new/prefix1/imag/sunflower_1.jpg",
                          ":/new/prefix1/imag/cherryboom_1.jpg",
                          ":/new/prefix1/imag/wallnut_1.jpg",
                          ":/new/prefix1/imag/dilei_1.jpg",
                          ":/new/prefix1/imag/snowshooter_1.jpg"};
//植物
QString gifs[10] = {
    0, ":/new/prefix1/imag/peashooter.gif",":/new/prefix1/imag/sunflower.gif",":/new/prefix1/imag/cherrybomb.gif",
    ":/new/prefix1/imag/wallnut.gif",":/new/prefix1/imag/potatodilei_noready.gif",":/new/prefix1/imag/snowshooter.gif"
};//存放每个植物序号所对应的gif图片，当可以种植时，将gif放置在对应的坐标内

//seedbank
pair<int,int> seedbank_point[50] = {{80,9}, {134,9}, {188,9},
                           {242,9},{296,9},{350,9},
                           {404,9}};

//草坪第几行第几列对应坐标
pair<int,int> gr_point[10][10] = {
    {{47,95},{124,95},{205,95},{284,95},{367,95},{449,95},{527,95},{605,95},{685,95}},
    {{47,195},{124,195},{205,195},{284,195},{367,195},{449,195},{527,195},{605,195},{685,195}},
    {{47,295},{124,295},{205,295},{284,295},{367,295},{449,295},{527,295},{605,295},{685,295}},
    {{47,395},{124,395},{205,395},{284,395},{367,395},{449,395},{527,395},{605,395},{685,395}},
    {{47,495},{124,495},{205,495},{284,495},{367,495},{449,495},{527,495},{605,495},{685,495}}
};

int Day::ZOMBIE_GEN_TIMES_NOW=0;

Day::Day(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Day)
{
    ui->setupUi(this);

    //清空植物槽等预先处理
    seedbank.clear();
    grass.clear();
    ui->ready->hide();
    ui->set->hide();
    ui->Plant->hide();

    //设置背景图片
    QPalette pa(this->palette());
    QImage img = QImage(":/new/prefix1/imag/background1.jpg");
    img = img.scaled(this->size());
    pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);

    //设置背景音乐
    Music music("qrc:/new/prefix1/music/Laura Shigihara - Choose Your Seeds(1).mp3");
    music.play();

    //加入选择植物界面
    Choose_plant *choose_plant = new Choose_plant(this);
    choose_plant->move(0,0);
    choose_plant->show();

    connect(choose_plant, SIGNAL(game_start()), this, SLOT(game_start_slot()));

    //加入菜单按钮以及菜单
    Menu *menu = new Menu(this);
    menu->move(190,45);
    menu->hide();//先隐藏

    connect(menu, &Menu::game, [=](){
        timer->start(33);
        music1.my_continue();
    });
    connect(menu, &Menu::mainwi, [=](){
        timer->stop();
        this->close();
        music1.setmusic("qrc:/new/prefix1/music/MainJM.mp3");
        music1.play();
    });

    //创建menubutton
    menubutton = new Logonbutton(QString(":/new/prefix1/imag/menubutton_1.png"), QString(":/new/prefix1/imag/menubutton_2.png"));
    menubutton->setParent(this);
    menubutton->move(686, -1);
    menubutton->show();
    connect(menubutton, &Logonbutton::pressed, [=](){
        menubutton->move1(1);
        menubutton->sound1();
    });
    connect(menubutton, &Logonbutton::released,[=](){
        menubutton->move2(1);
        menubutton->sound5();
        //跳出menu界面
        menu->raise();
        menu->show();
        //游戏强制暂停，线程和音乐都暂停
        music1.pause();
        timer->stop();
    });


    //设置随机数种子
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    timer = new QTimer;

    //创建场景
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    //背景图场景
    view = new QGraphicsView(scene, this);
    view->resize(802, 602);

    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/new/prefix1/imag/background1.jpg"));

    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    view->hide();

    //加入天空阳光
    Shop *shop = new Shop;
    shop->setPos(520, 45);
    scene->addItem(shop);

    //加入小推车
    for (int i = 0 ; i < 5; i ++ )
    {
        Mower *mower = new Mower;
        mower->setPos(13, 130 + 98 * i);
        scene->addItem(mower);
    }

    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(22);
    ui->sunbank_label->setFont(font);
    ui->sunbank_label->setAlignment(Qt::AlignCenter);//设置居中对齐

    //绑定信号和槽函数
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &Day::addZombie);
    connect(timer, &QTimer::timeout, this, &Day::check);
    connect(timer, &QTimer::timeout, [=](){
        emit cooltime();
        emit now_sun_val(shop->sun);
        ui->sunbank_label->setNum(shop->sun);
    });
}

Day::~Day()
{
    delete ui;
    delete pic;
    delete menubutton;
    delete timer;
}

void Day::mouseMoveEvent(QMouseEvent *ev)
{
    emit mouseMove(ev);
}

void Day::plant_sound()
{
    startSound = new QMediaPlayer(this);
    startSound->setMedia(QUrl("qrc:/new/prefix1/music/plant.mp3"));
    startSound->play();
}

void Day::mouse_move(QMouseEvent *ev)
{
    me = static_cast<QMouseEvent*>(ev);
    //判断如果有植物卡片被选择了，那么它移动到鼠标位置
    for (int i = 0 ; i < 5; i ++ )
        if (CardList[i]->is_pick) CardList[i]->move(me->pos().x() - 25, me->pos().y() - 35), CardList[i]->raise();
    if (shovel->is_pick) shovel->move(me->pos().x() - 10, me->pos().y() - 55), shovel->raise();
    xx = me->pos().x();
    yy = me->pos().y();
}

void Day::ready_to_plant_slot(int num)
{
    //    bool a = grass.determine(x,y,num);//判断这个位置的草坪是否可以种植
//    //神奇的铲僵尸操作
//    QPointF pos = QPointF(gr_point[row][col].first,gr_point[row][col].second);
//    QList<QGraphicsItem *> items = scene->items(pos);
//    foreach (QGraphicsItem *item, items)
//        if (item->type() == Zombie::Type)
//        {
//            plant_sound();//声音
//            delete item;
//            return;
//        }

    int x = xx, y = yy;
    int row = grass.fun(x,y).first, col = grass.fun(x,y).second;
    QPointF pos = QPointF(gr_point[row][col].first + 32,gr_point[row][col].second + 30);


    if (num == 0){//铲子操作
        QList<QGraphicsItem *> items = scene->items(pos - QPointF(-32, -30));
        foreach (QGraphicsItem *item, items)
            if (item->type() == Plant::Type)
            {
                plant_sound();//声音
                delete item;
                return;
            }
    }
    else{//种植操作
        QList<QGraphicsItem *> items = scene->items(pos);

        foreach (QGraphicsItem *item, items)
            if (item->type() == Plant::Type)
                return;

        for (int i = 0 ; i < 5; i ++ ){
            if (CardList[i]->plant_id == num)
            {
                Shop *shop = qgraphicsitem_cast<Shop *>(scene->items(QPointF(300, 15))[0]);
                shop->sun -= CardList[i]->plant_spend;//花费阳光
                plant_sound();//声音
                CardList[i]->is_ok = false;//进入冷却
                CardList[i]->counter = 0;

                Plant *plant;

                switch(num){
                case 1:
                    plant = new Peashooter;
                    break;
                case 2:
                    plant = new SunFlower;
                    break;
                case 3:
                    plant = new CherryBomb;
                    break;
                case 4:
                    plant = new WallNut;
                    break;
                case 5:
                    plant = new PotatoMine;
                    break;
                case 6:
                    plant = new SnowPea;
                    break;
                }

                plant->setPos(pos);
                scene->addItem(plant);
            }
        }
    }
    update();
}

void Day::addZombie()
{
    /*
    // static int low = 4;
    // static int high = 8;
    // static int maxtime = 20 * 1000 / 33;//设置一个maxtime
    // static int time = maxtime / 2;//轮次为无穷，因为没有停止的控制
    */
    static int time = GEN_ONE_TIME2;
    static int counter = 0;//僵尸的数量

    if (ZOMBIE_GEN_TIMES_NOW < ZOMBIE_GEN_TIMES2)
    {
        if (++counter >= time)
        {
            ZOMBIE_GEN_TIMES_NOW++;
            counter = 0;//--------再次置为0

            //随机生成类型和出现位置
            int type = qrand() % 100;
            int i = qrand() % 5;

            Zombie *zombie;
            if (type < 40)
                zombie = new BasicZombie();
            else if (type < 70)
                zombie = new ConeZombie();
            else if (type < 80)
                zombie = new BucketZombie();
            else if (type < 90)
                zombie = new ScreenZombie();
            else
                zombie = new FootballZombie();

            zombie->setPos(828, 130 + 98 * i);

            scene->addItem(zombie);
        }
    }
}

void Day::check()
{
    static int time = GEN_ONE_TIME2/10;
    static int counter = 0;
    if (++counter >= time)
    {
        //判断是否输了
        counter = 0;
        const QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)
        {
            //僵尸到达了左边
            if (item->type() == Zombie::Type && item->x() < 10)
            {
                scene->addPixmap(QPixmap(":/new/prefix1/imag/ZombiesWon.png"))->setPos(0, 0);//输的图片
                scene->advance();
                timer->stop();
                music1.setmusic("qrc:/new/prefix1/music/losemusic.mp3");
                music1.play();
                QMessageBox::warning(this, "僵尸们", "僵尸们吃掉了你的脑子！\n游戏失败！\n\n“脑子...真好吃”");
                this->close();
                music1.setmusic("qrc:/new/prefix1/music/MainJM.mp3");
                music1.play();
                return;
            }
        }

        //没输，再判断是不是最后一次，如果是的话：并且没有僵尸了，就赢了
        if (ZOMBIE_GEN_TIMES_NOW == ZOMBIE_GEN_TIMES2)//最后一次生成僵尸
        {
            foreach (QGraphicsItem *item, items)
            {
                //还有僵尸就return
                if (item->type() == Zombie::Type)
                {
                    return;
                }
            }

            //到这里说明没有僵尸了，赢了！！！
            scene->addPixmap(QPixmap(":/new/prefix1/imag/AIIT.png"))->setPos(0, 0);//输的图片
            scene->advance();
            timer->stop();
            music1.setmusic("qrc:/new/prefix1/music/winmusic.mp3");
            music1.play();
            QMessageBox::warning(this, "恭喜", "你成功守护了你的房子和你的脑子！\n\t游戏胜利！\n\t\t“歪比歪比”");
            this->close();
            music1.setmusic("qrc:/new/prefix1/music/MainJM.mp3");
            music1.play();
            return;
        }


    }
}

void Day::game_start_slot()
{
//=====================================================================
    //根据seedbank将植物卡片的阴影引入:
    //而植物卡片则以自定义按钮的形式 重新呈现在Seedbank上 盖住卡片阴影
    //获取一下植物序号
    for(int i = 0; i < seedbank.getsize(); i ++ )
        plant_id[i] = seedbank.getd(i);

    QImage image(plant_path1[plant_id[0]]);
    ui->plant1->setPixmap(QPixmap::fromImage(image));
    ui->plant1->resize(image.width(),image.height());
    image.load(plant_path1[plant_id[1]]);
    ui->plant2->setPixmap(QPixmap::fromImage(image));
    ui->plant2->resize(image.width(),image.height());
    image.load(plant_path1[plant_id[2]]);
    ui->plant3->setPixmap(QPixmap::fromImage(image));
    ui->plant3->resize(image.width(),image.height());
    image.load(plant_path1[plant_id[3]]);
    ui->plant4->setPixmap(QPixmap::fromImage(image));
    ui->plant4->resize(image.width(),image.height());
    image.load(plant_path1[plant_id[4]]);
    ui->plant5->setPixmap(QPixmap::fromImage(image));
    ui->plant5->resize(image.width(),image.height());

//=========================================================================

    ui->background->show();
    ui->background->lower();//将背景图片置于ui最低层
    //创建动画对象空间（初始化可以指定动画控件和动画需使用的动画属性名）
    m = new QPropertyAnimation();
    m->setTargetObject(ui->background);    //设置使用动画的控件
    m->setEasingCurve(QEasingCurve::Linear); //设置动画效果

    m->setPropertyName("pos");    //指定动画属性名
    m->setDuration(2500);    //设置动画时间（单位：毫秒）
    m->setStartValue(ui->background->pos());  //设置动画起始位置在label控件当前的pos
    m->setEndValue(ui->background->pos() + QPoint(296, 0)); //设置动画结束位置
    m->start();   //启动动画

    QEventLoop eventloop;
    QTimer::singleShot(2800, &eventloop, SLOT(quit()));
    eventloop.exec();

    ui->background->hide();

    music1.setmusic("qrc:/new/prefix1/music/readysetplant.mp3");
    music1.play();

    //ready!
        ui->ready->show();
        m->setPropertyName("pos");
        m->setDuration(500);
        m->setStartValue(ui->ready->pos());
        m->setEndValue(ui->ready->pos());
        m->start();
        QTimer::singleShot(500, &eventloop, SLOT(quit()));
        eventloop.exec();
        ui->ready->hide();
    //set!!
        ui->set->show();
        m->setPropertyName("pos");
        m->setDuration(800);
        m->setStartValue(ui->set->pos());
        m->setEndValue(ui->set->pos());
        m->start();
        QTimer::singleShot(700, &eventloop, SLOT(quit()));
        eventloop.exec();
        ui->set->hide();
    //plant!!!
        ui->Plant->show();
        m->setPropertyName("pos");
        m->setDuration(1000);
        m->setStartValue(ui->Plant->pos());
        m->setEndValue(ui->Plant->pos());
        m->start();
        QTimer::singleShot(900, &eventloop, SLOT(quit()));
        eventloop.exec();
        ui->Plant->hide();

    QTimer::singleShot(600, &eventloop, SLOT(quit()));
    eventloop.exec();
//=======================================================================================

    //检测鼠标位置
    connect(this, SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(mouse_move(QMouseEvent *)));
    this->setMouseTracking(true);
    QWidget::setMouseTracking(true);
    ui->label->setMouseTracking(true);
    ui->label_2->setMouseTracking(true);

    //加入植物卡片
    card1 = new Plant_card(plant_id[0],seedbank_point[0].first,seedbank_point[0].second);
    card2 = new Plant_card(plant_id[1],seedbank_point[1].first,seedbank_point[1].second);
    card3 = new Plant_card(plant_id[2],seedbank_point[2].first,seedbank_point[2].second);
    card4 = new Plant_card(plant_id[3],seedbank_point[3].first,seedbank_point[3].second);
    card5 = new Plant_card(plant_id[4],seedbank_point[4].first,seedbank_point[4].second);

    CardList[0] = card1;
    CardList[1] = card2;
    CardList[2] = card3;
    CardList[3] = card4;
    CardList[4] = card5;

    for(int i = 0 ; i < 5; i ++ ){
        CardList[i]->setParent(this);
        CardList[i]->setMouseTracking(true);
        CardList[i]->move(CardList[i]->x, CardList[i]->y);
        connect(CardList[i], SIGNAL(ready_to_plant(int)), this, SLOT(ready_to_plant_slot(int)));
        connect(this, SIGNAL(now_sun_val(int)), CardList[i], SLOT(compare_with_sun(int)));
        connect(this, SIGNAL(cooltime()), CardList[i], SLOT(cooltime_slot()));
    }

    //生成一个铲子shovel
    shovel = new Plant_card(0, 355, 0);
    shovel->setParent(this);
    shovel->setMouseTracking(true);
    shovel->move(shovel->x, shovel->y);
    shovel->show();
    connect(shovel, SIGNAL(ready_to_plant(int)), this, SLOT(ready_to_plant_slot(int)));

    //启动定时器，播放音乐等等游戏初始化
    timer->start(33);
    view->show();
    view->lower();
    music1.setmusic("qrc:/new/prefix1/music/Laura Shigihara - Grasswalk(In-Game).mp3");
    music1.play();
}
