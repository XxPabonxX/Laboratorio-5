#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsItem>
#include <QPainter>

#define PATH_EXP_CEN ":/imagenes/explo_centro.png"
#define PATH_EXP_ARR ":/imagenes/explo_arriba.png"
#define PATH_EXP_ABA ":/imagenes/explo_abajo.png"
#define PATH_EXP_IZQ ":/imagenes/explo_izquierda.png"
#define PATH_EXP_DER ":/imagenes/explo_derecha.png"

using namespace std;

class explosion : public QGraphicsItem
{
    int h=50;
    int a=50;
    int posx;
    int posy;
    bool cen=false;
    bool arr=false;
    bool aba=false;
    bool izq=false;
    bool der=false;


public:
    explosion();
    explosion(string,int,int);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    ~explosion();
};

#endif // EXPLOSION_H
