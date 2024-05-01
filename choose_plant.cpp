#include "choose_plant.h"
#include "ui_choose_plant.h"

Music music;

//choosebank
pair<int,int> choosebank_point[50] = {{},{23,130},{78,130},{133,130},
                            {188,130},{243,130},{298,130},
                            {353,130}};
//seedbank
pair<int,int> dpoint[50] = {{},{80,10}, {134,10}, {188,10},
                           {242,10},{296,10},{350,10},
                           {404,10}};

Choose_plant::Choose_plant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Choose_plant)
{
    ui->setupUi(this);

    music.setmusic("qrc:/new/prefix1/music/Laura Shigihara - Choose Your Seeds(1).mp3");
    music.play();

    //创建植物卡片button
    peashooter = new Choose_plantbutton(":/new/prefix1/imag/peashooter_1.jpg",1);
    sunflower = new Choose_plantbutton(":/new/prefix1/imag/sunflower_1.jpg",2);
    cherry_bomb = new Choose_plantbutton(":/new/prefix1/imag/cherryboom_1.jpg",3);
    wall_nut = new Choose_plantbutton(":/new/prefix1/imag/wallnut_1.jpg",4);
    potato_mine = new Choose_plantbutton(":/new/prefix1/imag/dilei_1.jpg",5);
    snowshooter = new Choose_plantbutton(":/new/prefix1/imag/snowshooter_1.jpg",6);

    //设父类， 移动到choose框内， 显示
    peashooter->setParent(this), peashooter->move(23,130), peashooter->show();
    sunflower->setParent(this), sunflower->move(78,130), sunflower->show();
    cherry_bomb->setParent(this), cherry_bomb->move(133,130), cherry_bomb->show();
    wall_nut->setParent(this), wall_nut->move(188,130), wall_nut->show();
    potato_mine->setParent(this), potato_mine->move(243,130), potato_mine->show();
    snowshooter->setParent(this), snowshooter->move(298,130), snowshooter->show();

    //按钮pressed事件

    connect(peashooter, &Choose_plantbutton::pressed,[=](){
        peashooter->sound();
        //当我点击植物按钮的时候，先判断is_choose的bool值
        //如果被选择了，那么该按钮原路返回至自己的老位置，并且改变is_choose的bool值
        //如果没有被选择，那么先从植物槽类中获取植物槽的最大个数，如果＜最大值，那么可以移动到植物槽中，反之不做回应
        //其中，关于移动到植物槽中的哪个位置，先判断植物槽中已经有几个植物，再获取下一个植物应该放到植物槽中的哪个位置的一个pair数组

        if (!peashooter->is_choose){
            int cnt = seedbank.getsize();
            //判断植物槽是不是满了
            if (cnt < 5){
                peashooter->is_choose = true;
                seedbank.choose_this_plant(peashooter->plant_number);

                //移动到植物槽的从左往右的第一个空槽中
                for(int i = 0; i < 5; i ++ ){
                    if (seedbank.is_occupied[i] == false){
                        seedbank.is_occupied[i] = true;//第i个槽设置被占用
                        seedbank.plant_id[peashooter->plant_number] = i;//这个植物序号在植物槽的第i个位置
                        peashooter->move(dpoint[i + 1].first,dpoint[i + 1].second);
                        break;
                    }
                }

                cnt = seedbank.getsize();
                qDebug() << "选择后植物槽个数：" << cnt;
                //如果添加了这个植物，使植物槽满了,则发送满槽信号给chooseplant,让它把start_gamebutton点亮
                if (cnt == 5) mancao();
            }else if(cnt == 5){
                qDebug() << "已满！不能再添加！";
            }
        }else{
            //被选择了,重新点击后要回到原来的位置
            //只要取消一个植物卡片，植物槽必然是不满槽的，所以lets_rockbutton不可能点亮
            peashooter->is_choose = false;
            seedbank.back_this_plant(peashooter->plant_number);
            dis_mancao();
            peashooter->move(choosebank_point[peashooter->plant_number].first,
                    choosebank_point[peashooter->plant_number].second);
            int x = seedbank.plant_id[peashooter->plant_number];
            seedbank.is_occupied[x] = false;
            seedbank.plant_id[peashooter->plant_number] = -1;

            int cnt = seedbank.getsize();
            qDebug() << "取消后植物槽个数：" << cnt;
        }
    });
    connect(sunflower, &Choose_plantbutton::pressed,[=](){
        sunflower->sound();
        if (!sunflower->is_choose){
            int cnt = seedbank.getsize();
            if (cnt < 5){
                sunflower->is_choose = true;
                seedbank.choose_this_plant(sunflower->plant_number);
                for(int i = 0; i < 5; i ++ ){
                    if (seedbank.is_occupied[i] == false){
                        seedbank.is_occupied[i] = true;
                        seedbank.plant_id[sunflower->plant_number] = i;
                        sunflower->move(dpoint[i + 1].first,dpoint[i + 1].second);
                        break;
                    }
                }
                cnt = seedbank.getsize();
                if (cnt == 5) mancao();
            }
        }else{
            sunflower->is_choose = false;
            seedbank.back_this_plant(sunflower->plant_number);
            dis_mancao();
            sunflower->move(choosebank_point[sunflower->plant_number].first,
                    choosebank_point[sunflower->plant_number].second);
            int x = seedbank.plant_id[sunflower->plant_number];
            seedbank.is_occupied[x] = false;
            seedbank.plant_id[sunflower->plant_number] = -1;
            int cnt = seedbank.getsize();
            qDebug() << "取消后植物槽个数：" << cnt;
        }
    });
    connect(cherry_bomb, &Choose_plantbutton::pressed,[=](){
        cherry_bomb->sound();
        if (!cherry_bomb->is_choose){
            int cnt = seedbank.getsize();
            if (cnt < 5){
                cherry_bomb->is_choose = true;
                seedbank.choose_this_plant(cherry_bomb->plant_number);
                for(int i = 0; i < 5; i ++ ){
                    if (seedbank.is_occupied[i] == false){
                        seedbank.is_occupied[i] = true;
                        seedbank.plant_id[cherry_bomb->plant_number] = i;
                        cherry_bomb->move(dpoint[i + 1].first,dpoint[i + 1].second);
                        break;
                    }
                }
                cnt = seedbank.getsize();
                qDebug() << "选择后植物槽个数：" << cnt;
                if (cnt == 5) mancao();
            }
        }else{
            cherry_bomb->is_choose = false;
            seedbank.back_this_plant(cherry_bomb->plant_number);
            dis_mancao();
            cherry_bomb->move(choosebank_point[cherry_bomb->plant_number].first,
                    choosebank_point[cherry_bomb->plant_number].second);
            int x = seedbank.plant_id[cherry_bomb->plant_number];
            seedbank.is_occupied[x] = false;
            seedbank.plant_id[cherry_bomb->plant_number] = -1;
            int cnt = seedbank.getsize();
            qDebug() << "取消后植物槽个数：" << cnt;
        }
    });
    connect(wall_nut, &Choose_plantbutton::pressed,[=](){
        wall_nut->sound();
        if (!wall_nut->is_choose){
            int cnt = seedbank.getsize();
            if (cnt < 5){
                wall_nut->is_choose = true;
                seedbank.choose_this_plant(wall_nut->plant_number);
                for(int i = 0; i < 5; i ++ ){
                    if (seedbank.is_occupied[i] == false){
                        seedbank.is_occupied[i] = true;
                        seedbank.plant_id[wall_nut->plant_number] = i;
                        wall_nut->move(dpoint[i + 1].first,dpoint[i + 1].second);
                        break;
                    }
                }
                cnt = seedbank.getsize();
                qDebug() << "选择后植物槽个数：" << cnt;
                if (cnt == 5) mancao();
            }
        }else{
            wall_nut->is_choose = false;
            seedbank.back_this_plant(wall_nut->plant_number);
            dis_mancao();
            wall_nut->move(choosebank_point[wall_nut->plant_number].first,
                    choosebank_point[wall_nut->plant_number].second);
            int x = seedbank.plant_id[wall_nut->plant_number];
            seedbank.is_occupied[x] = false;
            seedbank.plant_id[wall_nut->plant_number] = -1;
            int cnt = seedbank.getsize();
            qDebug() << "取消后植物槽个数：" << cnt;
        }
    });
    connect(potato_mine, &Choose_plantbutton::pressed,[=](){
        potato_mine->sound();
        if (!potato_mine->is_choose){
            int cnt = seedbank.getsize();
            if (cnt < 5){
                potato_mine->is_choose = true;
                seedbank.choose_this_plant(potato_mine->plant_number);
                for(int i = 0; i < 5; i ++ ){
                    if (seedbank.is_occupied[i] == false){
                        seedbank.is_occupied[i] = true;
                        seedbank.plant_id[potato_mine->plant_number] = i;
                        potato_mine->move(dpoint[i + 1].first,dpoint[i + 1].second);
                        break;
                    }
                }
                cnt = seedbank.getsize();
                qDebug() << "选择后植物槽个数：" << cnt;
                if (cnt == 5) mancao();
            }
        }else{
            potato_mine->is_choose = false;
            seedbank.back_this_plant(potato_mine->plant_number);
            dis_mancao();
            potato_mine->move(choosebank_point[potato_mine->plant_number].first,
                    choosebank_point[potato_mine->plant_number].second);
            int x = seedbank.plant_id[potato_mine->plant_number];
            seedbank.is_occupied[x] = false;
            seedbank.plant_id[potato_mine->plant_number] = -1;
            int cnt = seedbank.getsize();
            qDebug() << "取消后植物槽个数：" << cnt;
        }
    });
    connect(snowshooter, &Choose_plantbutton::pressed,[=](){
        snowshooter->sound();
        if (!snowshooter->is_choose){
            int cnt = seedbank.getsize();
            if (cnt < 5){
                snowshooter->is_choose = true;
                seedbank.choose_this_plant(snowshooter->plant_number);
                for(int i = 0; i < 5; i ++ ){
                    if (seedbank.is_occupied[i] == false){
                        seedbank.is_occupied[i] = true;
                        seedbank.plant_id[snowshooter->plant_number] = i;
                        snowshooter->move(dpoint[i + 1].first,dpoint[i + 1].second);
                        break;
                    }
                }
                cnt = seedbank.getsize();
                qDebug() << "选择后植物槽个数：" << cnt;
                if (cnt == 5) mancao();
            }
        }else{
            snowshooter->is_choose = false;
            seedbank.back_this_plant(snowshooter->plant_number);
            dis_mancao();
            snowshooter->move(choosebank_point[snowshooter->plant_number].first,
                    choosebank_point[snowshooter->plant_number].second);
            int x = seedbank.plant_id[snowshooter->plant_number];
            seedbank.is_occupied[x] = false;
            seedbank.plant_id[snowshooter->plant_number] = -1;
            int cnt = seedbank.getsize();
            qDebug() << "取消后植物槽个数：" << cnt;
        }
    });











    //创建lets_rockbutton
    lets_rockbutton = new Logonbutton(":/new/prefix1/imag/Lets_rockbutton_2.jpg", ":/new/prefix1/imag/Lets_rockbutton_3.jpg");
    lets_rockbutton->setParent(this);
    lets_rockbutton->move(145,540);
    lets_rockbutton->hide();
    //需要在植物槽满时才显示！！


    //当植物槽个数 == 预设植物槽个数时，发出的信号被this接收，同时显示这个按钮，准备开始游戏
    //当植物槽个数 < 预设植物槽个数时， 点击植物按钮可以将其放入植物槽中，再次点击可以返回
    //点击按钮时应该判断一个is_choose的bool值，如果为假，则移动到植物槽中，如果为真,则移动回选择植物框中

    connect(lets_rockbutton, &Logonbutton::pressed, [=](){
        lets_rockbutton->move1(1);
        lets_rockbutton->sound2();
    });
    connect(lets_rockbutton, &Logonbutton::released,[=](){
       lets_rockbutton->move2(1);
       this->hide();
       //在这里发送一个游戏开始的信号:game_start();
       emit game_start();
    });


//    Daygame *daygame = new Daygame();
//    daygame->show();
//    this->hide();
}

Choose_plant::~Choose_plant()
{
    delete ui;
    delete peashooter;
    delete sunflower;
    delete cherry_bomb;
    delete wall_nut;
    delete potato_mine;
    delete snowshooter;
    delete menubutton;
    delete lets_rockbutton;
}

void Choose_plant::continue_music()
{
    music.play();
}

void Choose_plant::to_mainwi()
{
    //返回主菜单
    MainWi *w = new MainWi(1);
    w->show();
    this->close();
}

void Choose_plant::mancao()
{
    lets_rockbutton->show();
}

void Choose_plant::dis_mancao()
{
    lets_rockbutton->hide();
}
