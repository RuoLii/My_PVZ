#include "sokoban.h"
#include "ui_sokoban.h"

Music music3;

//0代表空地，-1代表水池，1代表坚果，2代表陷阱


pair<int,int> map_coordinate[5][9]{
    {{47,95},{124,95},{205,95},{284,95},{367,95},{449,95},{527,95},{605,95},{685,95}},
    {{47,195},{124,195},{205,195},{284,195},{367,195},{449,195},{527,195},{605,195},{685,195}},
    {{47,295},{124,295},{205,295},{284,295},{367,295},{449,295},{527,295},{605,295},{685,295}},
    {{47,395},{124,395},{205,395},{284,395},{367,395},{449,395},{527,395},{605,395},{685,395}},
    {{47,495},{124,495},{205,495},{284,495},{367,495},{449,495},{527,495},{605,495},{685,495}}
};

Sokoban::Sokoban(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sokoban)
{
    ui->setupUi(this);
    //设置背景图片
    QPalette pa(this->palette());
    QImage img = QImage(":/new/prefix1/imag/sokoban_background.png");
    img = img.scaled(this->size());
    pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);

    //播放背景音乐
    music3.setmusic("qrc:/new/prefix1/music/Hpzvp.mp3");
    music3.play();

    //加入菜单按钮以及菜单
    Menu *menu = new Menu(this);
    menu->move(190,45);
    menu->hide();//先隐藏

    connect(menu, &Menu::game, [=](){

        music3.my_continue();
    });
    connect(menu, &Menu::mainwi, [=](){
        this->close();
        music3.setmusic("qrc:/new/prefix1/music/MainJM.mp3");
        music3.play();
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
        music3.pause();
    });

    for (int i = 0; i < 5; i ++ )
        for (int j = 0; j < 9; j ++ )
            map_[i][j] = 0;
    for(int i = 1; i < 5; i ++ )
        for(int j = 0; j < 2; j ++ )
            map_[i][j] = -1;
    map_[0][4] = 1, map_[0][7] = -1, map_[0][8] = -1;
    map_[1][7] = -1,map_[1][8] = -1;
    map_[2][2] = 1,map_[2][3] = 1,map_[2][4] = 2,map_[2][5] = 2,map_[2][8] = -1;
    map_[3][4] = 1,map_[3][6] = 1,map_[3][7] = 2,map_[3][8] = -1;
    map_[4][2] = -1,map_[4][7] = 2,map_[4][8] = -1;


    //加入食人花、土豆地雷等陷阱
    chomper = new QLabel(this);
    movie = new QMovie(":/new/prefix1/imag/chomper.gif");
    chomper->setMovie(movie);
    movie->start();
    chomper->move(map_coordinate[2][4].first, map_coordinate[2][4].second - 8);
    chomper->show();

    potato_mine = new QLabel(this);
    movie = new QMovie(":/new/prefix1/imag/potatodilei_ready.gif");
    potato_mine->setMovie(movie);
    movie->start();
    potato_mine->move(map_coordinate[3][7].first, map_coordinate[3][7].second + 13);
    potato_mine->show();

    potato_mine = new QLabel(this);
    movie = new QMovie(":/new/prefix1/imag/potatodilei_ready.gif");
    potato_mine->setMovie(movie);
    movie->start();
    potato_mine->move(map_coordinate[4][7].first, map_coordinate[4][7].second + 13);
    potato_mine->show();

    //加入坚果墙
    wallnut = new WallnutPush(0, 4);
    wallnut->setParent(this);
    wallnut->move(map_coordinate[0][4].first,map_coordinate[0][4].second);
    wallnut->show();
    wal[0] = wallnut;

    wallnut = new WallnutPush(2, 2);
    wallnut->setParent(this);
    wallnut->move(map_coordinate[2][2].first,map_coordinate[2][2].second);
    wallnut->show();
    wal[1] = wallnut;

    wallnut = new WallnutPush(2, 3);
    wallnut->setParent(this);
    wallnut->move(map_coordinate[2][3].first,map_coordinate[2][3].second);
    wallnut->show();
    wal[2] = wallnut;

    wallnut = new WallnutPush(3, 4);
    wallnut->setParent(this);
    wallnut->move(map_coordinate[3][4].first,map_coordinate[3][4].second);
    wallnut->show();
    wal[3] = wallnut;

    wallnut = new WallnutPush(3, 6);
    wallnut->setParent(this);
    wallnut->move(map_coordinate[3][6].first,map_coordinate[3][6].second);
    wallnut->show();
    wal[4] = wallnut;

    //加入铁门僵尸  初始出生在4行5列
    door_zombie = new DoorZombie(4, 5);
    door_zombie->setParent(this);
    door_zombie->setFocusPolicy(Qt::StrongFocus);
    door_zombie->setGeometry(0, 0, 166, 144);
    door_zombie->move(map_coordinate[4][5].first - 65, map_coordinate[4][5].second - 65);
    door_zombie->show();

    //绑定僵尸的信号
    connect(door_zombie,SIGNAL(move_to_here(int,int)),this, SLOT(move_to_here_slot(int,int)));
    connect(door_zombie,SIGNAL(game_over()), this, SLOT(game_over_slot()));
    connect(door_zombie,SIGNAL(push_wallnut(int,int,int)),this, SLOT(push_wallnut_slot(int,int,int)));
    connect(door_zombie,SIGNAL(check()),this, SLOT(check_slot()));

    ui->label->raise();
    ui->label_2->raise();
    QTimer::singleShot(3000, [=](){
        ui->label->hide();
        ui->label_2->hide();
    });
}

Sokoban::~Sokoban()
{
    delete ui;
    delete pic;
    delete menubutton;
    delete chomper;
    delete potato_mine;
    delete movie;
    delete door_zombie;
    delete wallnut;
    delete *wal;
}

void Sokoban::move_to_here_slot(int row, int col)
{
//    qDebug() << "已移动！";
    door_zombie->move(map_coordinate[row][col].first - 65, map_coordinate[row][col].second - 65);
}

void Sokoban::game_over_slot()
{
    QMessageBox::warning(this,"抱歉","碰到了陷阱植物\n游戏失败！");
    this->close();
    music3.setmusic("qrc:/new/prefix1/music/MainJM.mp3");
    music3.play();
}

void Sokoban::push_wallnut_slot(int row, int col, int op)
{
    for(int i = 0; i < 5; i ++ ){
        if (wal[i]->row == row && wal[i]->col == col){
            switch(op){
            case 1://上
                wal[i]->row -= 1;
                wal[i]->move(map_coordinate[wal[i]->row][wal[i]->col].first,map_coordinate[wal[i]->row][wal[i]->col].second);
                map_[row][col] = 0;
                map_[row - 1][col] = 1;
                break;
            case 2://下
                wal[i]->row += 1;
                wal[i]->move(map_coordinate[wal[i]->row][wal[i]->col].first,map_coordinate[wal[i]->row][wal[i]->col].second);
                map_[row][col] = 0;
                map_[row + 1][col] = 1;
                break;
            case 3://左
                wal[i]->col -= 1;
                wal[i]->move(map_coordinate[wal[i]->row][wal[i]->col].first,map_coordinate[wal[i]->row][wal[i]->col].second);
                map_[row][col] = 0;
                map_[row][col - 1] = 1;
                break;
            case 4://右
                wal[i]->col += 1;
                wal[i]->move(map_coordinate[wal[i]->row][wal[i]->col].first,map_coordinate[wal[i]->row][wal[i]->col].second);
                map_[row][col] = 0;
                map_[row][col + 1] = 1;
                break;
            }
        }
    }
}

void Sokoban::check_slot()
{
    if (map_[0][0] == 1 && map_[0][1] == 1 && map_[0][2] == 1 &&
            map_[0][6] == 1 && map_[1][4] == 1)
    {
        QMessageBox::information(this, "恭喜","通关成功！\n");
        this->close();
        music3.setmusic("qrc:/new/prefix1/music/MainJM.mp3");
        music3.play();

    }
}
