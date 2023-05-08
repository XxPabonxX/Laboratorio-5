#include "interfaz.h"
#include "ui_interfaz.h"

int inicio=0;
int vidas=3;
int puntaje=0;

Interfaz::Interfaz(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interfaz)
{
    QMessageBox::information(
        this,
        tr("NOTA"),
        tr("Las rutas a cada textura de los objetos se encuentra en la cabecera de su clase correspondiente.") );
    ui->setupUi(this);
    //Se crea la escena
    scene = new QGraphicsScene;

    //Fondo verde
    QPen pen;
    QBrush brush2(Qt::darkGreen,Qt::SolidPattern);
    scene->addRect(0,0,1550,650, pen, brush2);
    scene->setSceneRect(inicio,-15,700,671);

    //personaje
    bombardero =new bomber();
    scene->addItem(bombardero);

    //Se grafica el mapa estatico
    dibujarLadrillos();
    dibujarBordes();
    dibujarIntermedios();
    crearEnemigos();

    //timer de las bombas
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(eliminarBomba()));

    //timer de la explosion
    timer_2=new QTimer(this);
    connect(timer_2,SIGNAL(timeout()),this,SLOT(eliminarExplo()));

    //timer del movimiento de los enemigos
    timer_3=new QTimer(this);
    connect(timer_3,SIGNAL(timeout()),this,SLOT(moverEnemigos()));
    timer_3->start(18);

    //timer del countdown del juego
    ui->lcd_time->display(200);
    timer_4=new QTimer(this);
    connect(timer_4,SIGNAL(timeout()),this,SLOT(tiempoPasa()));
    timer_4->start(1000);

    //Vidas y timer de la inmortalidad
    ui->lcd_lifes->display(vidas);
    timer_5=new QTimer(this);
    connect(timer_5,SIGNAL(timeout()),this,SLOT(mortal()));

    //mostrar escena
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

Interfaz::~Interfaz()
{
    delete ui;
}

void Interfaz::keyPressEvent(QKeyEvent *evento)//evento de presionar tecla
{
    if(evento->key()==Qt::Key_S)
    {
        bombardero->moveDown();
        if(EvaluarColision())
            bombardero->moveUp();
    }
    else if (evento->key()==Qt::Key_D)
    {
        int xd=bombardero->getPOSX();//valor en x antes de moverse
        bombardero->moveRight();
        if(EvaluarColision())
            bombardero->moveLeft();
        else if(sobrepasa(xd))
        {
            inicio+=50;
            scene->setSceneRect(inicio,-15,700,671);
        }
    }
    else if(evento->key()==Qt::Key_W)
    {
        bombardero->moveUp();
        if(EvaluarColision())
            bombardero->moveDown();
    }
    else if(evento->key()==Qt::Key_A)
    {
        int xd=bombardero->getPOSX();//valor en x antes de moverse
        bombardero->moveLeft();
        if(EvaluarColision())
            bombardero->moveRight();
        else if(sobrepasa(xd))
        {
            inicio-=50;
            scene->setSceneRect(inicio,-15,700,671);
        }
    }
    else if(evento->key()==Qt::Key_E)
    {
        if(bombs.count()==0)
        {
            int x=bombardero->getPOSX(),y=bombardero->getPOSY();
            bombs.append(new bomba(x,y));
            scene->addItem(bombs.back());
            timer->start(3000);
        }
    }
}

bool Interfaz::EvaluarColision()//se evalua si el personaje colisiona con otro(s) objeto(s)
{
    QList<solidos*>::iterator it;
    QList<destructibles*>::iterator ite;
    QList<bomba*>::iterator iter;

    for(it=bloq_solidos.begin(); it!=bloq_solidos.end(); it++)
    {
        if(bombardero->collidesWithItem(*it))
        {
            return true;
        }
    }
    for(ite=bloq_destru.begin(); ite!=bloq_destru.end(); ite++)
    {
        if(bombardero->collidesWithItem(*ite))
        {
            return true;
        }
    }
    for(iter=bombs.begin(); iter!=bombs.end(); iter++)
    {
        if(bombardero->collidesWithItem(*iter))
        {
            return true;
        }
    }
    return false;
}

bool Interfaz::EvaluarColisionExp()//se evalua si la explosion colisiona con algun objeto y que accion tomar al respecto
{
    QList<solidos*>::iterator it;
    QList<destructibles*>::iterator ite;
    QList<baloons*>::iterator iter;

    for(it=bloq_solidos.begin(); it!=bloq_solidos.end(); it++)
    {
        if(exp_actu->collidesWithItem(*it))
        {
            return false;
        }
    }
    int contador=0;
    for(ite=bloq_destru.begin(); ite!=bloq_destru.end(); ite++)
    {
        bool puerta=bloq_destru[contador]->getDoor();
        if(exp_actu->collidesWithItem(*ite))
        {
            scene->removeItem(*ite);
            bloq_destru.removeAt(contador);
            puntaje+=100;
            ui->lcd_score->display(puntaje);
            if(puerta==true)
            {
                QMessageBox::information(
                    this,
                    tr("Felicitaciones!"),
                    tr("Ha encontrado la puerta.") );
                exit(1);
            }
            return true;
        }
        contador++;
    }
    int con=0;
    for(iter=enemigos.begin(); iter!=enemigos.end(); iter++)
    {
        if(exp_actu->collidesWithItem(*iter))
        {
            scene->removeItem(*iter);
            enemigos.removeAt(con);
            puntaje+=500;
            ui->lcd_score->display(puntaje);
            return true;
        }
        con++;
    }
    bool inmo=bombardero->getInmo();
    if(exp_actu->collidesWithItem(bombardero))
    {
        if(inmo==true)
        {

        }
        else
        {
            vidas-=1;
            ui->lcd_lifes->display(vidas);
            if(vidas==0)
            {
                QMessageBox::information(
                    this,
                    tr("GAME OVER"),
                    tr("Ultima vida perdida por una explosion propia."));
                timer_4->stop();
                bombardero->cambiar();
                exit(1);
            }
            bombardero->cambiar();
            timer_5->start(2000);
        }
    }
    return true;
}

bool Interfaz::EvaluarColisionEnemies()
{
    QList<solidos*>::iterator it;
    QList<destructibles*>::iterator ite;
    QList<bomba*>::iterator iter;

    for(it=bloq_solidos.begin(); it!=bloq_solidos.end(); it++)
    {
        if(enemigo_act->collidesWithItem(*it))
        {
            return true;
        }
    }
    for(ite=bloq_destru.begin(); ite!=bloq_destru.end(); ite++)
    {
        if(enemigo_act->collidesWithItem(*ite))
        {
            return true;
        }
    }
    for(iter=bombs.begin(); iter!=bombs.end(); iter++)
    {
        if(enemigo_act->collidesWithItem(*iter))
        {
            return true;
        }
    }
    bool inmo=bombardero->getInmo();
    if(enemigo_act->collidesWithItem(bombardero))
    {
        if(inmo==true)
        {

        }
        else
        {
            vidas-=1;
            ui->lcd_lifes->display(vidas);
            if(vidas==0)
            {
                QMessageBox::information(
                    this,
                    tr("GAME OVER"),
                    tr("Ultima vida perdida por un enemigo."));
                timer_4->stop();
                bombardero->cambiar();
                exit(1);
            }
            bombardero->cambiar();
            timer_5->start(2000);
        }
    }
    return false;
}

bool Interfaz::sobrepasa(int xd)//Dice si el personaje ya paso alguno de los puntos limite
{
    bool sobrepasa=false;
    int x=bombardero->getPOSX();
    int limit_izq=300,limit_dere=1050;
    if(x>=limit_izq and x<=limit_dere)
    {
        sobrepasa=true;
    }
    if(xd==300 or xd==1050)
    {
        sobrepasa=true;
    }
    return sobrepasa;
}

void Interfaz::crearEnemigos(std::string ruta)
{
    ifstream archivo;
    string coorde,numero,int1,int2,digi;
    int ente1,ente2,len,conta,contador=0;
    archivo.open(ruta, ios::in);
    while(!archivo.eof())
    {
        if (archivo.eof())
            break;
        getline(archivo,coorde);
        len=coorde.length();
        conta=0;
        for (int i=0; i<=len;i++)
        {
            digi=coorde[i];
            if (digi!="," and digi[0]!='\000' )
            {
                numero+=digi;
            }
            else
            {
                conta+=1;
                if(conta==1)
                    int1+=numero;
                else if(conta==2)
                    int2+=numero;
                numero.erase();
            }
        }
        ente1=atoi(int1.c_str());
        ente2=atoi(int2.c_str());
        int1.erase();
        int2.erase();
        if(contador>=0 and contador<=5)
        {
            enemigos.append(new baloons(ente1,ente2,true));
            scene->addItem(enemigos.back());
        }
        else
        {
            enemigos.append(new baloons(ente1,ente2,false));
            scene->addItem(enemigos.back());
        }
        contador++;
    }
    archivo.close();
}

void Interfaz::eliminarBomba()//Se encarga de eliminar la bomba de la escena
{
    int x=bombs.back()->getPOSX(), y=bombs.back()->getPOSY(), copy_x, copy_y;
    scene->removeItem(bombs.back());
    timer->stop();
    bombs.clear();
    //se grafica el centro de la explosion
    rango_explo.append(new explosion("centro",x,y));
    scene->addItem(rango_explo.back());
    exp_actu=new explosion("centro",x,y);
    EvaluarColisionExp();
    //lado derecho graficable?
    copy_x=x+50;
    exp_actu=new explosion("derecha",copy_x,y);
    if(EvaluarColisionExp())
    {
        rango_explo.append(exp_actu);
        scene->addItem(rango_explo.back());
    }
    //lado izquierdo graficable?
    copy_x=x-50;
    exp_actu=new explosion("izquierda",copy_x,y);
    if(EvaluarColisionExp())
    {
        rango_explo.append(exp_actu);
        scene->addItem(rango_explo.back());
    }
    //lado de arriba graficable?
    copy_y=y-50;
    exp_actu=new explosion("arriba",x,copy_y);
    if(EvaluarColisionExp())
    {
        rango_explo.append(exp_actu);
        scene->addItem(rango_explo.back());
    }
    //lado de abajo graficable?
    copy_y=y+50;
    exp_actu=new explosion("abajo",x,copy_y);
    if(EvaluarColisionExp())
    {
        rango_explo.append(exp_actu);
        scene->addItem(rango_explo.back());
    }
    timer_2->start(1000);
}

void Interfaz::eliminarExplo()//elimina la explosion de la escena
{
    for(int i=0;i<rango_explo.count();i++)
    {
        scene->removeItem(rango_explo[i]);
    }
    timer_2->stop();
    rango_explo.clear();
}

void Interfaz::moverEnemigos()//se encarga de hacer que los enemigos se muevan
{
    QList<baloons*>::iterator ite;

    int contador=0;
    bool verticalidad;
    for(ite=enemigos.begin();ite!=enemigos.end();ite++)
    {
        verticalidad=enemigos[contador]->getVerti();
        if(verticalidad==true)
        {
            enemigo_act=enemigos[contador];
            bool moverse=enemigo_act->getMov();
            if(moverse==true)
            {
                enemigo_act->moveUp();
                enemigos[contador]->moveUp();
                if(EvaluarColisionEnemies())
                {
                    enemigos[contador]->movOriginal();
                    enemigos[contador]->moveDown();
                }
            }
            else
            {
                enemigo_act->moveDown();
                enemigos[contador]->moveDown();
                if(EvaluarColisionEnemies())
                {
                    enemigos[contador]->movOriginal();
                    enemigos[contador]->moveUp();
                }
            }
        }
        else
        {
            enemigo_act=enemigos[contador];
            bool moverse=enemigo_act->getMov();
            if(moverse==true)
            {
                enemigo_act->moveLeft();
                enemigos[contador]->moveLeft();
                if(EvaluarColisionEnemies())
                {
                    enemigos[contador]->movOriginal();
                    enemigos[contador]->moveRight();
                }
            }
            else
            {
                enemigo_act->moveRight();
                enemigos[contador]->moveRight();
                if(EvaluarColisionEnemies())
                {
                    enemigos[contador]->movOriginal();
                    enemigos[contador]->moveLeft();
                }
            }
        }
        contador++;
    }
}

void Interfaz::tiempoPasa()//cuenta el tiempo transcurrido para el countdown
{
    static int conta=1;
    ui->lcd_time->display(200-conta);
    if(200-conta==0)
    {
        timer_4->stop();
        vidas-=1;
        ui->lcd_lifes->display(vidas);
        if(vidas==0)
        {
            QMessageBox::information(
                this,
                tr("GAME OVER"),
                tr("Ultima vida perdida por el tiempo acabado."));
            bombardero->cambiar();
            timer_4->stop();
            exit(1);
        }
    }
    conta++;
}

void Interfaz::mortal()//vuelve a bomberman mortal otra vez
{
    bombardero->cambiar();
    timer_5->stop();
}

void Interfaz::dibujarBordes(std::string ruta)//dibuja los bordes del mapa
{
    ifstream archivo;
    string coorde,numero,int1,int2,int3,int4,digi;
    int ente1,ente2,ente3,ente4,len,conta;
    archivo.open(ruta, ios::in);
    while(!archivo.eof())
    {
        if (archivo.eof())
            break;
        getline(archivo,coorde);
        len=coorde.length();
        conta=0;
        for (int i=0; i<=len;i++)
        {
            digi=coorde[i];
            if (digi!="," and digi[0]!='\000' )
            {
                numero+=digi;
            }
            else
            {
                conta+=1;
                if(conta==1)
                    int1+=numero;
                else if(conta==2)
                    int2+=numero;
                else if(conta==3)
                    int3+=numero;
                else if(conta==4)
                    int4+=numero;
                numero.erase();
            }
        }
        ente1=atoi(int1.c_str());
        ente2=atoi(int2.c_str());
        ente3=atoi(int3.c_str());
        ente4=atoi(int4.c_str());
        int1.erase();
        int2.erase();
        int3.erase();
        int4.erase();
        bloq_solidos.append(new solidos(ente1,ente2,ente3,ente4));
        scene->addItem(bloq_solidos.back());
    }
    archivo.close();
}

void Interfaz::dibujarIntermedios()//dibuja los solidos interiores del mapa
{
    int x_ini=100, y_ini=100;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<14;j++)
        {
            bloq_solidos.append(new solidos(x_ini,y_ini,50,50));
            scene->addItem(bloq_solidos.back());
            x_ini+=100;
        }
        x_ini=100;
        y_ini+=100;
    }
}

void Interfaz::dibujarLadrillos(std::string ruta)//dibuja los ladrillos que pueden ser destruidos del mapa
{
    ifstream archivo;
    string coorde,numero,int1,int2,digi;
    int ente1,ente2,len,conta;
    archivo.open(ruta, ios::in);
    srand(time(NULL));
    int num=rand()%55;
    int contador=1;
    bool aqui=true;
    while(!archivo.eof())
    {
        if (archivo.eof())
            break;
        getline(archivo,coorde);
        len=coorde.length();
        conta=0;
        for (int i=0; i<=len;i++)
        {
            digi=coorde[i];
            if (digi!="," and digi[0]!='\000' )
            {
                numero+=digi;
            }
            else
            {
                conta+=1;
                if(conta==1)
                    int1+=numero;
                else if(conta==2)
                    int2+=numero;
                numero.erase();
            }
        }
        ente1=atoi(int1.c_str());
        ente2=atoi(int2.c_str());
        int1.erase();
        int2.erase();
        if(contador==num)
        {
            bloq_destru.append(new destructibles(ente1,ente2,aqui));
            scene->addItem(new puerta(ente1,ente2));
            scene->addItem(bloq_destru.back());
        }
        else
        {
            bloq_destru.append(new destructibles(ente1,ente2));
            scene->addItem(bloq_destru.back());
        }
        contador++;
    }
    archivo.close();
}

