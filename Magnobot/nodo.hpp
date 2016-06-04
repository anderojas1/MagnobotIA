#ifndef NODO_H
#define NODO_H

#include <QVector>

class Nodo
{
public:
    Nodo(int pos1, int pos2, Nodo *nodo, int valor, bool traje, int validaDevolver, int nivel, int heuristica = 0);
    Nodo(int pos1, int pos2);
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
    void setProfundidad(int nivel);
    int getProfundidad();
    int getCostoEstimado(bool flag = false);
    void setCostoEstimado(int heuristica);

private:

    int costo;
    Nodo *padre;
    int posI;
    int posJ;
    bool traje;
    int valida;
    int profundidad;
    int costoEstimado;

};

#endif // NODO_H
