#include "destructibles.h"

destructibles::destructibles()
{
    posx=0;
    posy=0;
    door=false;
    setPos(posx,posy);
}

destructibles::destructibles(int x, int y)
{
    posx=x;
    posy=y;
    door=false;
    setPos(posx,posy);
}

destructibles::destructibles(int x, int y, bool puerta)
{
    posx=x;
    posy=y;
    door=puerta;
    setPos(posx,posy);
}

bool destructibles::getDoor()
{
    return door;
}

QRectF destructibles::boundingRect() const
{
    return QRectF(0, 0, an, h);
}

void destructibles::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage bloq_esta(PATH_DESTRU);
    QBrush brush_im(bloq_esta);
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush_im);
    painter->drawRect(boundingRect());
}

destructibles::~destructibles()
{

}
