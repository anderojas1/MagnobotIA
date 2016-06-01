#ifndef NODO_H
#define NODO_H

#include <QVector>

class Nodo
{
public:
    Nodo(int pos1, int pos2, Nodo *nodo, int valor, bool traje, int validaDevolver);
    ~Nodo();
    void setPadre (Nodo *nodo);
    void setCosto(int valor);
    void setPosI(int pos);
    void setPosJ(int pos);
    Nodo *getPadre();
    int getPosI();
    int getPosJ();
    int getCosto();
    void setTraje(bool traje);
    bool getTraje();
    void setValida();
    int getValida();

private:

    int costo;
    Nodo *padre;
    int posI;
    int posJ;
    bool traje;
    int valida;

};

#endif // NODO_H
