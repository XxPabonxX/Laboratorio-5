#include "baloons.h"

baloons::baloons()
{
    posx=50;
    posy=50;
    setPos(posx,posy);
}

baloons::baloons(int x, int y, bool _vertical)
{
    posx=x;
    posy=y;
    vertical=_vertical;
    setPos(posx,posy);
}

QRectF baloons::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void baloons::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(PATH_BALL);
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

void baloons::movOriginal()
{
    if(movi_original==true)
        movi_original=false;
    else if(movi_original==false)
        movi_original=true;
}

bool baloons::getMov()
{
    return movi_original;
}

bool baloons::getVerti()
{
    return vertical;
}

void baloons::moveUp()//cambiar posicion hacia arriba
{
    posy-=velocidad;
    setPos(posx, posy);
}

void baloons::moveDown()//cambiar posicion hacia abajo
{
    posy+=velocidad;
    setPos(posx, posy);
}

void baloons::moveLeft()//cambiar movimiento hacia la izquierda
{
    posx-=velocidad;
    setPos(posx, posy);
}

void baloons::moveRight()//cambiar movimiento hacia la derecha
{
    posx+=velocidad;
    setPos(posx, posy);
}

baloons::~baloons()
{

}
