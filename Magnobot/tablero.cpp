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
    QString ruta = "";
    int usuario = 0;
    switch (usuario) {
        case 0:
            ruta = "/home/anderojas/Proyectos/Magnobot/Iconos/";
        break;
        case 1:
            ruta = "/home/alchemixt/qt_projects/MagnobotIA/Magnobot/Iconos/";
        break;
    }

    QPixmap pix(ruta+"logo_univalle.png");
    ui->lb_univalleLogo->setPixmap(pix);
    robot = new Agente();
    arbol = new QVector<Nodo*>();
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

    if (ui->comboBoxAlgoritmo->currentText() == "Amplitud") busquedaAmplitud();
    else qWarning("botón ejecutar OK. Función no implementada aún");

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

    /* Selección de ruta */
        QString ruta = "";
        int usuario = 0;
        switch (usuario) {
            case 0:
                ruta = "/home/anderojas/Proyectos/Magnobot/Iconos/";
            break;
            case 1:
                ruta = "/home/alchemixt/qt_projects/MagnobotIA/Magnobot/Iconos/";
            break;
        }

    if (!tablero.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int lineaTableroI = 0;

    while (!tablero.atEnd()) {

        QByteArray line = tablero.readLine();
        QString linea (line);

        QStringList caracteres = linea.split(QRegExp("\\s"));

        for (int j = 0; j < caracteres.size()-1; j++) {

            QString valor = caracteres.at(j).toLocal8Bit().constData();
            QTableWidgetItem *campo = ui->tableTableroJuego->item(lineaTableroI, j);

            if (campo == NULL) {
                campo = new QTableWidgetItem();
                ui->tableTableroJuego->setItem(lineaTableroI, j, campo);

            }

            if (valor == "1") {

                campo->setIcon(QPixmap(100,100));
                campo->setIcon(QPixmap::fromImage(QImage(ruta+"Pared01.png")));
                qDebug("Encontrado ladrillos");
            }

            else if (valor == "2") {

                campo->setIcon(QPixmap::fromImage(QImage(ruta+"mega01.png")));
                qDebug("encontrado robot");
                robot->setPosI(lineaTableroI);
                robot->setPosJ(j);

            }

            else if (valor == "3") {

                campo->setIcon(QPixmap::fromImage(QImage(ruta+"traje.png")));
                qDebug("Encontrado traje");

            }

            else if (valor == "4") {

                campo->setIcon(QPixmap::fromImage(QImage(ruta+"Pared02.png")));
                qDebug("Encontrado campo magnético 1");

            }

            else if (valor == "5") {

                campo->setIcon(QPixmap::fromImage(QImage(ruta+"Pared03.png")));
                qDebug("Encontrado campo magnético 2");

            }

            else if (valor == "6") {

                campo->setIcon(QPixmap::fromImage(QImage(ruta+"key.jpg")));
                qDebug("Encontrado ítem");
                robot->addObjetivo();

            }

            matrizValores [lineaTableroI][j] = valor.toInt();
            if (valor == "2") matrizValores[lineaTableroI][j] = 0;
            cout << " valor en (" << lineaTableroI << "," << j << ") es: " << matrizValores[lineaTableroI][j] << endl;

            campo->setFlags(Qt::ItemIsEnabled);

        }

        lineaTableroI++;

    }

    tablero.close();
    cout << "Termina la construcción del juego en la interfaz\n";
    //cout << "posición en i saliendo de la carga en interfaz: " << robot->getPosI() << endl;

    for (int i = 0; i < 10; i++) {

        QString fila = "fila " + QString::number(i) + ": ";

        for (int j = 0; j < 10; j++) {

            int code = matrizValores[i][j];
            fila += QString::number(code);

        }

        cout << fila.toStdString() << endl;

    }

}

void Tablero::busquedaAmplitud() {

    int posIRobot = robot->getPosI();
    int posJRobot = robot->getPosJ();

    Nodo *raiz = new Nodo(posIRobot, posJRobot, NULL, 0);
    arbol->append(raiz);
    Nodo *meta = NULL;
    int con = 0;

    while (!robot->objetivosCompletos()) {
        if (con % 100000 == 0)
            cout << "iteración " << con << endl;
        con++;
        Nodo *nodo = arbol->first();
        int i = nodo->getPosI();
        int j = nodo->getPosJ();

        if (i == 9 && j == 8) {

            cout << "buscando en: (" << i << "," << j << ")\n";
            cout << "valor encontrado: " << matrizValores[i][j] << endl;

        }

        int codigo = matrizValores[i][j];

        if (codigo == 6) {

            robot->eliminarObjetivo();
            matrizValores[i][j] = 0;
            arbol->clear();
            arbol->append(nodo);
            cout << "objetivo encontrado en (" << i << "," << j << ")" << endl;

        }

        if (robot->objetivosCompletos()) {

            meta = nodo;
            cout << "SIII" << endl;

        }

        else {
            cout << "buscando en: (" << i << "," << j << ")\n";

            //cout << "valor encontrado: " << codigo << endl;

            if (i > 0) {

                int posI = i-1;
                int costoAcumulado = explorar(posI, j);
                cout << "costo explorado en (" << posI << "," << j << ") es: " << costoAcumulado << endl;
                if (costoAcumulado != -1) {
                    Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado);
                    arbol->append(nuevoNodo);

                }

            }

            if (i < (ui->tableTableroJuego->rowCount()-1)) {

                int posI = i+1;
                int costoAcumulado = explorar(posI, j);
                cout << "costo explorado en (" << posI << "," << j << ") es: " << costoAcumulado << endl;
                if (costoAcumulado != -1) {
                    Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado);
                    arbol->append(nuevoNodo);

                }

            }

            if (j > 0) {

                int posJ = j-1;
                int costoAcumulado = explorar(i, posJ);
                cout << "costo explorado en (" << i << "," << posJ << ") es: " << costoAcumulado << endl;
                if (costoAcumulado != -1) {
                    Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado);
                    arbol->append(nuevoNodo);

                }

            }

            if (j < ui->tableTableroJuego->columnCount()-1) {

                int posJ = j+1;
                int costoAcumulado = explorar(i, posJ);
                cout << "costo explorado en (" << i << "," << posJ << ") es: " << costoAcumulado << endl;
                if (costoAcumulado != -1) {
                    Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado);
                    arbol->append(nuevoNodo);

                }

            }

        }

        arbol->pop_front();
        //cout << arbol->size() << endl;

    }

    Nodo *tmp = meta;
    int i = tmp->getPosI();
    int j = tmp->getPosJ();
    QString pos = "(" + QString::number(i) + "," + QString::number(j) + ")";
    string coordenada = pos.toStdString();
    cout << coordenada << endl;

    while (tmp->getPadre() != NULL) {

        tmp = tmp->getPadre();
        int i = tmp->getPosI();
        int j = tmp->getPosJ();
        pos = "(" + QString::number(i) + "," + QString::number(j) + ")";
        coordenada = pos.toStdString();
        cout << coordenada << endl;

    }

}

int Tablero::explorar(int i, int j) {

    int codigo = matrizValores[i][j];

    if (codigo == 0 || codigo == 3 || codigo == 6) return 1;

    else if (codigo == 4) return 4;

    else if (codigo == 5) return 7;

    else return -1;

}
