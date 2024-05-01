#ifndef INIT_H
#define INIT_H

//初始化工作

//产生僵尸的数量
#define ZOMBIE_GEN_TIMES2 5

//产生一个僵尸从0累加到这个值
#define GEN_ONE_TIME2 100

//初始化阳光值
#define INIT_SUN_NUM 300 //50

//初始化卡片冷却时间
#define cooltime_SunFlower  100 //227
#define cooltime_Peashooter 100 //227
#define cooltime_CherryBomb 0 //606
#define cooltime_WallNut    280 //606
#define cooltime_PotatoMine 280 //606
#define cooltime_SnowPea    100 //227

//植物 生命值和攻击力
#define hp_WallNut 4000
#define hp_NormalPlant 300

#define atk_CherryBomb 1800
#define atk_PotatoMine 1800

#define atk_Peashooter 20
#define atk_Repeater 20
#define atk_SnowPea 20

#define hp_BasicZombie 181
#define hp_ConeZombie 640
#define hp_BucketZombie 1370
#define hp_ScreenZombie  1370
#define hp_FootballZombie  1670

#define atk_Zombie 100 * 33 / 1000

#define speed_zombie_1 (90.0 * 33 / 1000 / 4.7)
#define speed_zombie_2  (90.0 * 33 / 1000 / 2.5)


#endif // INIT_H
