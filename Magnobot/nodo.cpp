#include "nodo.hpp"

Nodo::Nodo(int pos1, int pos2, Nodo *nodo, int valorCosto)
{
    padre = nodo;
    posI = pos1;
    posJ = pos2;
    costo = valorCosto;

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
