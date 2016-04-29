#include "agente.hpp"
#include <iostream>
using namespace std;

Agente::Agente(int pos1, int pos2) {

    posI = pos1;
    posJ = pos2;
    traje = false;
    objetivos = new QVector<QString>();
}

Agente::Agente() {

    posI = 0;
    posJ = 0;
    traje = false;
    objetivos = new QVector<QString>();
    cout << objetivos->size() << endl;

}

Agente::~Agente() {

}

void Agente::setPosI(int pos) {

    posI = pos;
    cout << "posición en i para el robot " << pos << endl;

}

int Agente::getPosI() {

    if (this == NULL) {

        //cout << this << endl;
        return posI;

    } else {
        cout << this << endl;
        return posI;

    }

}

void Agente::setPosJ(int pos) {

    posJ = pos;
    cout << "posición en j para el robot " << getPosJ() << endl;

}

int Agente::getPosJ() {

    return this->posJ;

}

void Agente::addObjetivo() {

    objetivos->append("objetivo " + QString::number(objetivos->size() +1));
    qDebug("Añadido un ítem");
    cout << "el tamaño es ahora: " << objetivos->size() << endl;

}

bool Agente::objetivosCompletos() {

    return objetivos->isEmpty();

}


void Agente::eliminarObjetivo() {

    cout << "eliminando objetivo...\n";
    objetivos->pop_front();
    cout << "falta(n) " << objetivos->size() << " objetivo(s) por encontrar\n";

}

void Agente::moverDer() {

    posJ += 1;

}

void Agente::moverIzq() {

    posJ -= 1;

}

void Agente::moverAba() {

    posI += 1;
}

void Agente::moverArr() {

    posI -= 1;

}


int Agente::getSizeIObjetivos() {

    return objetivos->size();

}
