#include "bomber.h"

bomber::bomber()//constructor
{
    posx=50;
    posy=50;
    setPos(posx,posy);
}

bomber::bomber(int x, int y)//bomber sobrecargado
{
    posx=x;
    posy=y;
    setPos(posx,posy);
}

QRectF bomber::boundingRect() const //valores del rectangulo de interaccion
{
    return QRectF(0,0,50,50);
}

void bomber::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//pintado del objeto
{
    QPixmap pixmap;
    pixmap.load(PATH_BOMBER);
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

void bomber::moveUp()//cambiar posicion hacia arriba
{
    posy-=velocidad;
    setPos(posx, posy);
}

void bomber::moveDown()//cambiar posicion hacia abajo
{
    posy+=velocidad;
    setPos(posx, posy);
}

void bomber::moveLeft()//cambiar movimiento hacia la izquierda
{
    posx-=velocidad;
    setPos(posx, posy);
}

void bomber::moveRight()//cambiar movimiento hacia la derecha
{
    posx+=velocidad;
    setPos(posx, posy);
}

int bomber::getPOSX()//devuelve la posicion en X del item
{
    return posx;
}

int bomber::getPOSY()//devuelve la posicion en Y del item
{
    return posy;
}

void bomber::cambiar()
{
    if(inmortal==false)
        inmortal=true;
    else
        inmortal=false;
}

bool bomber::getInmo()
{
    return inmortal;
}

bomber::~bomber()
{

}
