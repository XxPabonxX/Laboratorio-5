#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <QGraphicsScene>
#include <QMessageBox>
#include <QMainWindow>
#include <QKeyEvent>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <QTimer>
#include <time.h>


#include "solidos.h"
#include "destructibles.h"
#include "bomber.h"
#include "bomba.h"
#include "explosion.h"
#include "puerta.h"
#include "baloons.h"

using namespace std;

#define PATH_SOLID ":/posiciones/posxposy_soli.txt"
#define PATH_LADRI ":/posiciones/posxposy_destru.txt"
#define PATH_ENEM ":/posiciones/posenemies.txt"

QT_BEGIN_NAMESPACE
namespace Ui { class Interfaz; }
QT_END_NAMESPACE

class Interfaz : public QMainWindow
{
    Q_OBJECT

public:
    Interfaz(QWidget *parent = nullptr);
    ~Interfaz();

public slots:
    void eliminarBomba();
    void eliminarExplo();
    void moverEnemigos();
    void tiempoPasa();
    void mortal();

private:
    Ui::Interfaz *ui;
    QGraphicsScene *scene;
    baloons *enemigo_act;
    explosion *exp_actu;
    bomber *bombardero;
    bomba *bomb;

    QList<solidos*> bloq_solidos;
    QList<bomba*> bombs;
    QList<destructibles*> bloq_destru;
    QList<explosion*> rango_explo;
    QList<baloons*> enemigos;

    QTimer *timer;
    QTimer *timer_2;
    QTimer *timer_3;
    QTimer *timer_4;
    QTimer *timer_5;

    void keyPressEvent(QKeyEvent *evento);

    bool EvaluarColision();
    bool EvaluarColisionExp();
    bool EvaluarColisionEnemies();

    bool sobrepasa(int);

    void crearEnemigos(std::string=PATH_ENEM);
    void dibujarBordes(std::string=PATH_SOLID);
    void dibujarIntermedios();
    void dibujarLadrillos(std::string=PATH_LADRI);
};
#endif // INTERFAZ_H
