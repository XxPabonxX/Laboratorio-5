#include "puerta.h"

puerta::puerta()
{
    posx=0;
    posy=0;
    setPos(posx,posy);
}

puerta::puerta(int x, int y)
{
    posx=x;
    posy=y;
    setPos(posx,posy);
}

QRectF puerta::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void puerta::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(PATH_DOOR);
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

puerta::~puerta()
{

}
