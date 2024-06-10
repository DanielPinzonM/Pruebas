#include "avion.h"

avion::avion(int ExtremoIzquierdo, int ExtremoDerecho)
{
    Vida = 100;

    PosicionLanzamiento = QRandomGenerator::global()->bounded(1,3);
    Imagen = new QGraphicsPixmapItem(QPixmap("Recursos/Avion"+QString(char(PosicionLanzamiento+48))+".png"));
    Imagen->setScale(1);

    PosicionLanzamiento = QRandomGenerator::global()->bounded(1,3);

    if(PosicionLanzamiento == 1)
    {
        Imagen->setPos(ExtremoDerecho+100, 50);
        DireccionPositiva = false;
    }
    else if(PosicionLanzamiento == 2)
    {
        Imagen->setPos(ExtremoIzquierdo-100, 50);
        Imagen->setTransform(QTransform().translate(60, 0).scale(-1, 1), false);
        DireccionPositiva = true;
    }

    PosicionLanzamiento = QRandomGenerator::global()->bounded(ExtremoIzquierdo, ExtremoDerecho);
    BombaLanzada = false;

    TiempoMover = new QTimer();
    connect(TiempoMover, SIGNAL(timeout()), this, SLOT(Mover()));
    TiempoMover->start(16);
}

short int avion::GetVida()
{
    return Vida;
}

QGraphicsPixmapItem* avion::GetImagen()
{
    return Imagen;
}

void avion::Mover()
{
    if(DireccionPositiva == true)
    {
        Imagen->setPos(Imagen->pos().x()+5, Imagen->pos().y());

        if(BombaLanzada == false && Imagen->pos().x() >= PosicionLanzamiento)
        {
            qDebug() << "Lanzamiento";
            BombaLanzada = true;
        }
    }
    else
    {
        Imagen->setPos(Imagen->pos().x()-5, Imagen->pos().y());

        if(BombaLanzada == false && Imagen->pos().x() <= PosicionLanzamiento)
        {
           qDebug() << "Lanzamiento";
           BombaLanzada = true;
        }
    }
}