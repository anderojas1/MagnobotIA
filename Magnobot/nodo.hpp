#ifndef NODO_H
#define NODO_H

#include <QVector>

class Nodo
{
public:
    Nodo(int pos1, int pos2, Nodo *nodo, int valor);
    ~Nodo();
    void setPadre (Nodo *nodo);
    void setCosto(int valor);
    void setPosI(int pos);
    void setPosJ(int pos);
    Nodo *getPadre();
    int getPosI();
    int getPosJ();
    int getCosto();

private:

    int costo;
    Nodo *padre;
    int posI;
    int posJ;

};

#endif // NODO_H
