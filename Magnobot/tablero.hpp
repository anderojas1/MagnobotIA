#ifndef TABLERO_HPP
#define TABLERO_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <string>

namespace Ui {
class Tablero;
}

class Tablero : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tablero(QWidget *parent = 0);
    ~Tablero();

private slots:
    void on_buttonSalir_clicked();

    void on_buttonSubirArchivo_clicked();

    void on_buttonEjecutar_clicked();

    void on_comboBoxBusqueda_currentIndexChanged(const QString &arg1);

    void on_buttonCargarArchivo_clicked();

private:
    Ui::Tablero *ui;
};

#endif // TABLERO_HPP
