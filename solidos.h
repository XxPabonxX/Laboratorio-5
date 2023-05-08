#ifndef SOLIDOS_H
#define SOLIDOS_H

#include <QGraphicsItem>
#include <QPainter>

#define PATH_BLOQ ":/imagenes/bloque.png"

class solidos : public QGraphicsItem
{
    int h;
    int an;
    int posx;
    int posy;

public:
    solidos();
    solidos(int,int,int,int);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    ~solidos();
};

#endif // SOLIDOS_H
