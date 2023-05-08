#include "explosion.h"

explosion::explosion()
{
    cen=true;
    posx=0;
    posy=0;
    setPos(posx,posy);
}

explosion::explosion(string lugar, int x, int y)
{
    if(lugar=="centro")
    {
        cen=true;
    }
    else if(lugar=="arriba")
    {
        arr=true;
    }
    else if(lugar=="abajo")
    {
        aba=true;
    }
    else if(lugar=="izquierda")
    {
        izq=true;
    }
    else if(lugar=="derecha")
    {
        der=true;
    }
    posx=x;
    posy=y;
    setPos(posx,posy);
}

QRectF explosion::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void explosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    if(cen==true)
    {
        pixmap.load(PATH_EXP_CEN);
    }
    else if(arr==true)
    {
        pixmap.load(PATH_EXP_ARR);
    }
    else if(aba==true)
    {
        pixmap.load(PATH_EXP_ABA);
    }
    else if(izq==true)
    {
        pixmap.load(PATH_EXP_IZQ);
    }
    else if(der==true)
    {
        pixmap.load(PATH_EXP_DER);
    }
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

explosion::~explosion()
{

}
