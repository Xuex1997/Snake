#ifndef FOOD_H
#define FOOD_H
#include <QPoint>
#include <QColor>


#define FOOD_MAX_AWARD 5
#define FOOD__MAX_RADIUS 5

class Food
{
public:
    Food() { };
    Food(QPoint foodpos, QColor foodcolor, int foodradius,int foodadds);
    QColor getColor();
    QPoint getPos();
    void setPos(QPoint p);
    int getRadius();
    int getAdds();
private:
    QPoint foodpos;
    QColor foodcolor;
    int foodradius;
    int foodadds;
};

#endif // FOOD_H
