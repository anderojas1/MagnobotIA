#ifndef AGENTE_H
#define AGENTE_H

#include <QVector>
#include <nodo.hpp>


class Agente
{
public:
    Agente();
    Agente(int pos1, int pos2);
    ~Agente();
    void setPosI(int pos);
    int getPosI();
    void setPosJ(int pos);
    int getPosJ();
    void addObjetivo(int posI, int posJ);
    bool objetivosCompletos();
    void eliminarObjetivo();
    void moverIzq();
    void moverDer();
    void moverArr();
    void moverAba();
    int getSizeIObjetivos();
    void setTraje (bool proteccion);
    bool getTraje();
    Nodo *getPosicionObjetivo(int i);
    QVector<Nodo*> *getPosicionesObjetivos();

private:
    int posI;
    int posJ;
    bool traje;
    QVector <Nodo*> *objetivos;
};

#endif // AGENTE_H
