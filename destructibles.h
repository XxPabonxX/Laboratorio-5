#ifndef DESTRUCTIBLES_H
#define DESTRUCTIBLES_H

#include <QGraphicsItem>
#include <QPainter>

#define PATH_DESTRU ":/imagenes/bloque_destructible.png"

class destructibles : public QGraphicsItem
{
    int h=50;
    int an=50;
    int posx;
    int posy;
    bool door;

public:
    destructibles();
    destructibles(int,int);
    destructibles(int,int,bool);
    bool getDoor();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    ~destructibles();
};

#endif // DESTRUCTIBLES_H
