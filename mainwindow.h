#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include <QFont>
#include <QRect>
#include <QTimer>

#include "food.h"
#include "snake.h"

#define GAME_AREA_WIDTH 1000
#define GAME_AREA_HIGHT 600
#define TILE_SIZE 5
#define SCORE_AREA_X 30
#define SCORE_AREA_Y 30
#define FOOD_NUM 50
#define AISNAKE_NUM 5
#define WANRANGE 10

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void Init(); //初始化
    void CreateFood();//产生随机的食物
    void CreateSnake();//创建初试的蛇
    void CreateAISnake();
    void Eat(Snake* s);
    bool AIIsDied(Snake* s);
    bool MSIsDied(Snake* s);
    void AIMove(Snake* s);
    void Snake2Food(int index, Snake* s);

private slots:
    void Snake_update();
    void AI_update();

private:
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    int mousex; //鼠标坐标
    int mousey;
    bool bIsRun; //是否启动
    bool bIsOver; //是否结束
    Snake my_snake; //玩家控制的蛇

    QList<Snake> ai_snakes; //智能蛇

    QList<Food> foods;//随机食物
    bool foods_map[GAME_AREA_WIDTH][GAME_AREA_HIGHT];//食物矩阵，加快查找速度
    QTimer *timer1; //自己的蛇定时器
    QTimer *timer2;//AI定时器
    QString sDisplay;//开始、结束提示
    QString sScoreLabel;//得分标签
    int nSpeed;//移动速度
    bool accFlag;
};

#endif
// MAINWINDOW_H
