#ifndef TABLERO_HPP
#define TABLERO_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <string>
#include <QVector>
#include "agente.hpp"
#include "nodo.hpp"

namespace Ui {
class Tablero;
}

class Tablero : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tablero(QWidget *parent = 0);
    ~Tablero();
    void busquedaAvara();
    void busquedaAmplitud();
    void busquedaProfundidad();
    QString get_ruta();
    void desplazar(int a, int b, int x, int y, QString ruta);
    void ordenarArbol();
    void ordenarNodosObjetivos();
    void buscaCostoUniforme();

private slots:
    void on_buttonSalir_clicked();

    void on_buttonSubirArchivo_clicked();

    void on_buttonEjecutar_clicked();

    void on_comboBoxBusqueda_currentIndexChanged(const QString &arg1);

    void on_buttonCargarArchivo_clicked();

private:
    Ui::Tablero *ui;
    int matrizValores [10][10];
    Agente *robot;
    QVector <Nodo*> *arbol;
    int explorar(int i, int j, bool traje);
    QVector <Nodo*> *camino;
};

#endif // TABLERO_HPP
