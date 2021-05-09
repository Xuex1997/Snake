#include "food.h"

Food::Food(QPoint pos, QColor color, int radius,int adds) :
    foodpos(pos),foodcolor(color),foodradius(radius), foodadds(adds)
{

}
QColor Food::getColor()
{
    return foodcolor;
}
QPoint Food::getPos()
{
    return foodpos;
}
int Food::getRadius()
{
    return foodradius;
}
int Food::getAdds()
{
    return foodadds;
}
void Food::setPos(QPoint p)
{
    foodpos = p;
}
