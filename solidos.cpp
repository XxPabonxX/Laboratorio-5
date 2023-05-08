#include "solidos.h"

solidos::solidos()
{
    h=0;
    an=0;
    posx=0;
    posy=0;
    setPos(posx,posy);
}

solidos::solidos(int x, int y, int _an, int _h)
{
    h=_h;
    an=_an;
    posx=x;
    posy=y;
    setPos(posx,posy);
}

QRectF solidos::boundingRect() const
{
    return QRectF(0, 0, an, h);
}

void solidos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage bloq_esta(PATH_BLOQ);
    QBrush brush_im(bloq_esta);
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush_im);
    painter->drawRect(boundingRect());
}

solidos::~solidos()
{

}
