#ifndef AGENTE_H
#define AGENTE_H

#include <QVector>


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
    void addObjetivo();
    bool objetivosCompletos();
    void eliminarObjetivo();
    void moverIzq();
    void moverDer();
    void moverArr();
    void moverAba();
    int getSizeIObjetivos();

private:
    int posI;
    int posJ;
    bool traje;
    QVector <QString> *objetivos;
};

#endif // AGENTE_H
