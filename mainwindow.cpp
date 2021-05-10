#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QTime>

int Distance(QPoint p1, QPoint p2)
{
    return pow(p1.x() - p2.x(),2) + pow(p1.y() - p2.y(),2);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),bIsRun(false),nSpeed(8),accFlag(false),ui(new Ui::MainWindow)
{
    this->setAutoFillBackground(true);//设置父窗口背景可被覆盖填充
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    timer1->stop();
    delete timer1;
    timer1 = nullptr;

    timer2->stop();
    delete timer2;
    timer2 = nullptr;

    delete ui;
}

void MainWindow::Init()
{
    sDisplay ="GAME START...";
    sScoreLabel = "得分：";
    sKillLabel = "击杀数：";
    bIsRun = true;
    bIsOver = false;

    for(int i=0; i<FOOD_NUM; i++) {
       CreateFood();
    }

    CreateSnake();
    for(int i=0; i<AISNAKE_NUM; i++) {
       CreateAISnake();
    }

    timer1 = new QTimer(this);
    timer1->start(150);
    connect(timer1,SIGNAL(timeout()),SLOT(Snake_update()));

    timer2 = new QTimer(this);
    timer2->start(150);
    connect(timer2,SIGNAL(timeout()),SLOT(AI_update()));

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(!bIsRun)
    {
        Init();
    }


    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //画背景
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawRect(0,0,GAME_AREA_WIDTH,GAME_AREA_HIGHT);

    painter.setPen("#F5F5F5F5");
    for(int ii = 0;ii <= GAME_AREA_HIGHT/TILE_SIZE; ii++)
    {
        painter.drawLine(0, ii*TILE_SIZE, GAME_AREA_WIDTH, ii*TILE_SIZE);
     }
    for(int jj = 0;jj <= GAME_AREA_WIDTH/TILE_SIZE; jj++)
    {
        painter.drawLine(jj*TILE_SIZE, 0, jj*TILE_SIZE, GAME_AREA_HIGHT);
     }


   //显示开始、结束
    QFont font1("Courier", 24);
    painter.setFont(font1);
    painter.setPen(Qt::black);
    painter.drawText(GAME_AREA_WIDTH/2,GAME_AREA_HIGHT/2,sDisplay);

    //排行榜
    drawRank(&painter);

    //得分
    QFont font2("Courier",15);
    painter.setFont(font2);
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::gray);
    painter.drawText(SCORE_AREA_X,SCORE_AREA_Y,sScoreLabel);
    painter.drawText(SCORE_AREA_X+50,SCORE_AREA_Y,QString::number(my_snake.getScore()));
    painter.drawText(KILL_AREA_X,KILL_AREA_Y,sKillLabel);
    painter.drawText(KILL_AREA_X+50,KILL_AREA_Y,QString::number(my_snake.getKill()));


    //画蛇
    painter.setBrush(my_snake.getColor());
    painter.setPen(Qt::black);
    for(int i=my_snake.getBodyLong()-1;i>=0;i--)
    {
        painter.drawEllipse((QPointF)my_snake.getBody()[i], my_snake.getRadius(), my_snake.getRadius());
    }
    painter.drawEllipse((QPointF)my_snake.getHead(), my_snake.getRadius()+1,my_snake.getRadius()+1);

    //画智能蛇
    for(int i=0; i<ai_snakes.size(); i++)
    {
        Snake ais = ai_snakes[i];
        painter.setBrush(ais.getColor());
        painter.setPen(Qt::black);
        for(int i=ais.getBodyLong()-1;i>=0;i--)
        {
            painter.drawEllipse((QPointF)ais.getBody()[i], ais.getRadius(), ais.getRadius());
        }
        painter.drawEllipse((QPointF)ais.getHead(), ais.getRadius()+1, ais.getRadius()+1);
    }


    //画食物
    for(int i=0;i<foods.size();i++)
    {
        painter.setBrush(foods[i].getColor());
        painter.setPen(foods[i].getColor());
        painter.drawEllipse(foods[i].getPos(), foods[i].getRadius(), foods[i].getRadius());
    }


    if(bIsOver)
    {
        timer1->stop();
        timer2->stop();
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QMouseEvent *mouse = (QMouseEvent*) event;
    mousex = mouse->windowPos().x();
    mousey = mouse->windowPos().y();
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A && accFlag == false)
    {
        timer1->stop();
        timer1->start(50);
        accFlag=true;
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A && accFlag == true)
    {
        timer1->stop();
        timer1->start(150);
        accFlag=false;
    }
}


void MainWindow::AI_update()
{
    for(int i = 0; i<ai_snakes.size(); i++)
    {
        if(AIIsDied(&ai_snakes[i]))
        {
            Snake2Food(i,&ai_snakes[i]);
        }else{
            Eat(&ai_snakes[i]);
            AIMove(&ai_snakes[i]);
        }
    }
}

void MainWindow::Snake_update()
{
    sDisplay = "";

    my_snake.snakeMove(my_snake.move(mousex,mousey));
    Eat(&my_snake);

    if(MSIsDied(&my_snake))
    {
        sDisplay = "GAME OVER !";
        bIsOver = true;
    }

    update();//paintEvent 更新
}

void MainWindow::CreateFood()//产生随机的食物
{
    QPoint pos(qrand()%(GAME_AREA_WIDTH-10)+10,qrand()%(GAME_AREA_HIGHT-10)+10);
    QColor color = QColor::fromHsl(qrand()%360,qrand()%256,qrand()%200);
    int radius = qrand()%FOOD_MAX_AWARD;
    if(radius <= 1) {
        radius+=2;
    }
    int adds = radius;

    Food food(pos,color,radius,adds);
    foods.push_back(food);
    foods_map[pos.x()][pos.y()]=true;
}

void MainWindow::CreateSnake()
{
    QPoint hhead(500,500);
    my_snake = Snake(hhead, Qt::red);
}

void MainWindow::CreateAISnake()
{
    QPoint h(qrand()%(GAME_AREA_WIDTH-10)+10,qrand()%(GAME_AREA_HIGHT-10)+10);
    QColor c = QColor::fromHsl(qrand()%360,qrand()%256,qrand()%200);
    Snake ais = Snake(h, c);
    ai_snakes.push_back(ais);
}

void MainWindow::Eat(Snake* s)
{
    for(int i=0; i<foods.size(); i++)
    {
        if(Distance(s->getHead(), foods[i].getPos()) < 81)
        {
            s->addbody(foods[i].getAdds());
            foods_map[foods[i].getPos().x()][foods[i].getPos().y()]=false;
            foods[i].setPos(QPoint(rand()%(GAME_AREA_WIDTH-10)+10,rand()%(GAME_AREA_HIGHT-10)+10));
            foods_map[foods[i].getPos().x()][foods[i].getPos().y()]=true;
            return;
        }
    }

}

bool MainWindow::AIIsDied(Snake* s)
{
    if(s->getHead().x()<0||s->getHead().x()>GAME_AREA_WIDTH
            ||s->getHead().y()>GAME_AREA_HIGHT||s->getHead().y()<0)
    {
        return true;
    }

    for(int i=0; i<my_snake.getBody().size(); i++)
    {
        if(Distance(s->getHead(),my_snake.getBody()[i]) < 81)
        {
            my_snake.setKill(my_snake.getKill()+1);
            return true;
        }
    }

    if(Distance(s->getHead(),my_snake.getHead()) < 81)
    {
        my_snake.setKill(my_snake.getKill()+1);
        return true;
    }
    return false;
}

bool MainWindow::MSIsDied(Snake* s)
{
    if(s->getHead().x()<0||s->getHead().x()>GAME_AREA_WIDTH
            ||s->getHead().y()>GAME_AREA_HIGHT||s->getHead().y()<0)
    {
        return true;
    }

    for(int i=0; i<ai_snakes.size(); i++)
    {
        for(int j=0; j<ai_snakes[i].getBody().size(); j++)
        {
            if(Distance(s->getHead(),ai_snakes[i].getBody()[j]) < 81)
            {
                return true;
            }
        }

    }
    return false;
}

void MainWindow::Snake2Food(int index,Snake* ais)
{
    for(int i=0; i<ais->getBodyLong(); i=i+2)
    {
        Food food(ais->getBody()[i],ais->getColor(),3, 3);
        foods.push_back(food);
    }
    ai_snakes.removeAt(index);

    CreateAISnake();
}

void MainWindow::AIMove(Snake *s)
{
    // find food
    float minLength = 0;
    QPoint minDir(0,0);
    for( auto itr = foods.begin(); itr != foods.end(); itr++ )
    {
        QPoint dir = itr->getPos() - s->getHead();
        if(dir.manhattanLength() < 1000 )
        {
            if(minDir == QPoint(0,0) || minLength > dir.manhattanLength())
            {
                minDir = itr->getPos();
                minLength = dir.manhattanLength();
            }
        }
    }

    if(minDir != QPoint(0,0))
    {
        s->snakeMove(s->move(minDir.x(), minDir.y()));
        return;
    }

}

void MainWindow::drawRank(QPainter* painter)
{

}
