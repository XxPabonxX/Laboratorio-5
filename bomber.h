#ifndef BOMBER_H
#define BOMBER_H

#include <QGraphicsItem>
#include <QPainter>

#define PATH_BOMBER ":/imagenes/bomberman.png"

class bomber : public QGraphicsItem
{
    int h=50;
    int a=50;
    int posx;
    int posy;
    int velocidad=50;
    bool inmortal=false;

public:
    bomber();
    bomber(int,int);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    int getPOSX();
    int getPOSY();
    void cambiar();
    bool getInmo();
    ~bomber();
};

#endif // BOMBER_H
