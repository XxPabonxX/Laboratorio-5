#ifndef BALOONS_H
#define BALOONS_H

#include <QGraphicsItem>
#include <QPainter>

#define PATH_BALL ":/imagenes/enemigo.png"

class baloons : public QGraphicsItem
{
    int h=25;
    int a=25;
    bool movi_original=true;
    bool vertical;
    int posx;
    int posy;
    int velocidad=1;

public:
    baloons();
    baloons(int,int,bool);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void movOriginal();
    bool getMov();
    bool getVerti();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    ~baloons();
};

#endif // BALOONS_H
