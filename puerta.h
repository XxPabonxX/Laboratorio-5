#ifndef PUERTA_H
#define PUERTA_H

#include <QGraphicsItem>
#include <QPainter>

#define PATH_DOOR ":/imagenes/puerta.png"

class puerta : public QGraphicsItem
{
    int h=50;
    int a=50;
    int posx;
    int posy;

public:
    puerta();
    puerta(int,int);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    ~puerta();
};

#endif // PUERTA_H
