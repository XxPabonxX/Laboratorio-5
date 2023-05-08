#ifndef BOMBA_H
#define BOMBA_H

#include <QGraphicsItem>
#include <QPainter>

#define PATH_BOMB ":/imagenes/bomba.png"

class bomba : public QGraphicsItem
{
    int h=50;
    int a=50;
    int posx;
    int posy;

public:
    bomba();
    bomba(int,int);
    int getPOSX();
    int getPOSY();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    ~bomba();
};

#endif // BOMBA_H
