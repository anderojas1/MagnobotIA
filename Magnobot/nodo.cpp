#include "nodo.hpp"

Nodo::Nodo(int pos1, int pos2, Nodo *nodo, int valorCosto, bool traje, int validaDevolver, int nivel, int heuristica)
{
    padre = nodo;
    posI = pos1;
    posJ = pos2;
    costo = valorCosto;
    this->traje = traje;
    valida = validaDevolver;
    profundidad = nivel;
    costoEstimado = heuristica;

}

Nodo::Nodo(int pos1, int pos2) {

   posI = pos1;
   posJ = pos2;
   padre = NULL;
   valida = NULL;
   traje = NULL;
   costo = NULL;

}

Nodo::~Nodo() {

}

int Nodo::getCosto() {

    return costo;

}

int Nodo::getPosI() {

    return posI;

}

int Nodo::getPosJ() {

    return posJ;
}

void Nodo::setCosto(int valor) {

    costo = valor;

}

void Nodo::setPadre(Nodo *nodo) {

    padre = nodo;

}

void Nodo::setPosI(int pos) {

    posI = pos;

}

void Nodo::setPosJ(int pos) {

    posJ = pos;

}

Nodo* Nodo::getPadre() {

    return padre;

}

void Nodo::setTraje(bool chaleco) {

    traje = chaleco;

}

bool Nodo::getTraje() {

    return traje;

}

int Nodo::getValida() {

    return valida;

}

void Nodo::setValida() {

    valida++;

}

void Nodo::setProfundidad(int nivel) {

    profundidad = nivel;

}

int Nodo::getProfundidad() {

    return profundidad;

}

int Nodo::getCostoEstimado(bool flag) {

    if (flag == false) return costoEstimado;
    else return costo + costoEstimado;

}

void Nodo::setCostoEstimado(int heuristica) {

    costoEstimado = heuristica;

}
