#include "tablero.hpp"
#include "ui_tablero.h"
#include <iostream>
#include <string>
using namespace std;

Tablero::Tablero(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tablero)
{
    ui->setupUi(this);
}

Tablero::~Tablero()
{
    delete ui;
}

void Tablero::on_buttonSalir_clicked()
{
    exit(0);
}

void Tablero::on_buttonSubirArchivo_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"), "/home/",tr("*.txt"));
    ui->lineRutaArchivo->setText(path);
}

void Tablero::on_buttonEjecutar_clicked()
{
    qWarning("botón ejecutar OK. Función no implementada aún");
}

void Tablero::on_comboBoxBusqueda_currentIndexChanged(const QString &arg1)
{
    if (arg1.toStdString() == "No informada") {

        ui->comboBoxAlgoritmo->clear();

        ui->comboBoxAlgoritmo->addItem("Amplitud");
        ui->comboBoxAlgoritmo->addItem("Costo uniforme");
        ui->comboBoxAlgoritmo->addItem("Profundidad (evita ciclos)");

    }

    else {

        ui->comboBoxAlgoritmo->clear();

        ui->comboBoxAlgoritmo->addItem("Avara");
        ui->comboBoxAlgoritmo->addItem("A*");

    }
}

void Tablero::on_buttonCargarArchivo_clicked()
{
    QFile tablero(ui->lineRutaArchivo->text()); // = QFile::QFile(ui->lineRutaArchivo->text());

    if (!tablero.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int lineaTableroI = 0;

    while (!tablero.atEnd()) {

        QByteArray line = tablero.readLine();
        QString linea (line);

        QStringList caracteres = linea.split(QRegExp("\\s"));

        for (int j = 0; j < caracteres.size(); j++) {

            QString valor = caracteres.at(j).toLocal8Bit().constData();
            QTableWidgetItem *campo = ui->tableTableroJuego->item(lineaTableroI, j);

            if (campo == NULL) {
                campo = new QTableWidgetItem();
                ui->tableTableroJuego->setItem(lineaTableroI, j, campo);

            }

            if (valor == "1") {

                campo->setIcon(QPixmap::fromImage(QImage("/home/anderojas/Proyectos/Magnobot/Iconos/ladrillos.jpeg")));
                qDebug("Encontrado ladrillos");
            }

            else if (valor == "2") {

                campo->setIcon(QPixmap::fromImage(QImage("/home/anderojas/Proyectos/Magnobot/Iconos/robot.jpeg")));
                qDebug("encontrado robot");

            }

            else if (valor == "3") {

                campo->setIcon(QPixmap::fromImage(QImage("/home/anderojas/Proyectos/Magnobot/Iconos/traje.jpg")));
                qDebug("Encontrado traje");

            }

            else if (valor == "4") {

                campo->setIcon(QPixmap::fromImage(QImage("/home/anderojas/Proyectos/Magnobot/Iconos/campo1.png")));
                qDebug("Encontrado campo magnético 1");

            }

            else if (valor == "5") {

                campo->setIcon(QPixmap::fromImage(QImage("/home/anderojas/Proyectos/Magnobot/Iconos/campo2.jpeg")));
                qDebug("Encontrado campo magnético 2");

            }

            else if (valor == "6") {

                campo->setIcon(QPixmap::fromImage(QImage("/home/anderojas/Proyectos/Magnobot/Iconos/copa.jpg")));
                qDebug("Encontrado ítem");

            }

            //campo->setText(valor);
            campo->setTextAlignment(2);

            campo->setFlags(Qt::ItemIsEnabled);

        }

        lineaTableroI++;

    }

    ui->lineRutaArchivo->setText("");

}

