#include "tablero.hpp"
#include "ui_tablero.h"
#include <iostream>
#include <string>
#include <QThread>
using namespace std;

Tablero::Tablero(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tablero)
{
    ui->setupUi(this);
    QString ruta = get_ruta();

    QPixmap pix(ruta+"logo_univalle.png");
    ui->lb_univalleLogo->setPixmap(pix);
    robot = new Agente();
    arbol = new QVector<Nodo*>();
    camino = new QVector<Nodo*>();

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
    QString ruta = get_ruta();

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

//Algoritmo de busqueda informada->Avara
void Tablero::busquedaAvara(){}

void Tablero::busquedaAmplitud() {

    // Posición inicial es la posición del robot
    int posIRobot = robot->getPosI();
    int posJRobot = robot->getPosJ();

    // Se crea el nodo raíz con la posición del robot
    Nodo *raiz = new Nodo(posIRobot, posJRobot, NULL, 0);
    // Se concatena al vector de búsqueda por amplitud
    arbol->append(raiz);
    // El nodo meta es cuando encuentra el último objetivo
    Nodo *meta = NULL;
    bool devolver = false;

    while (!robot->objetivosCompletos()) {  // Mientras le falte uno o más objetivos...

        // Toma el nodo que se encuentre de primero en el vector y toma la posición. Representa un cuadro en particular
        Nodo *nodo = arbol->first();
        int i = nodo->getPosI();
        int j = nodo->getPosJ();

        // Busca el código en la matriz asociada
        int codigo = matrizValores[i][j];

        // Si es un objetivo...
        if (codigo == 6) {

            /* Elimina un objetivo del vector de objetivos del robot
             * Pone a 0 la posición en la matriz de valores asociada (elimina el objetivo de la matriz)
             * Reinicia el algoritmo de búsqueda
             * El nodo es ahora la nueva posición inicial
             * Se permite devolver al robot
             * */

            robot->eliminarObjetivo();
            matrizValores[i][j] = 0;
            arbol->clear();
            arbol->append(nodo);
            cout << "objetivo encontrado en (" << i << "," << j << ")" << endl;
            devolver = true;

        }

        /*// Si el código es un traje...
        else if (codigo == 3) {

            robot->setTraje(true);

        }*/

        // Si ha encontrado todos los objetivos
        if (robot->objetivosCompletos()) {

            // ¡Tenemos la meta! ¡Eureka!
            meta = nodo;

        }

        // Si faltan objetivos
        else {

            /* Los if a continuación son usados para evaluar si se puede mover a izquierda, derecha
             * arriba o a abajo, para evitar desbordamientos
             * */

            if (i > 0) {

                int posI = i-1;
                int costoAcumulado = explorar(posI, j); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        // Evita devolverse al padre...
                        if (!(nodo->getPadre()->getPosI() == posI &&
                                nodo->getPadre()->getPosJ() == j)) {

                            // Si no es la posición del padre crea un nuevo nodo (campo) para ser evaluado)
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado);
                            arbol->append(nuevoNodo);

                        }

                        // Se devuelve sólo si en la posición actual encontró un objetivo
                        // variable devolver de tipo bool
                        else if (devolver == true) {

                            // Crea un nodo y pone false a devolver
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                    }

                    // Si es la raíz no hay problemas. No existe padre
                    else {

                        Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (i < (ui->tableTableroJuego->rowCount()-1)) {

                int posI = i+1;
                int costoAcumulado = explorar(posI, j);
                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (!(nodo->getPadre()->getPosI() == posI &&
                                nodo->getPadre()->getPosJ() == j)) {

                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado);
                            arbol->append(nuevoNodo);

                        } else if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j > 0) {

                int posJ = j-1;
                int costoAcumulado = explorar(i, posJ);
                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (!(nodo->getPadre()->getPosI() == i &&
                                nodo->getPadre()->getPosJ() == posJ)) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado);
                            arbol->append(nuevoNodo);

                        } else if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j < ui->tableTableroJuego->columnCount()-1) {

                int posJ = j+1;
                int costoAcumulado = explorar(i, posJ);
                if (costoAcumulado != -1) {
                    if (nodo != raiz) {

                        if (!(nodo->getPadre()->getPosI() == i &&
                                nodo->getPadre()->getPosJ() == posJ)) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado);
                            arbol->append(nuevoNodo);

                        } else if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado);
                        arbol->append(nuevoNodo);

                    }

                }

            }

        }

        // Elimina el primer nodo del vector
        arbol->pop_front();

    }

    Nodo *tmp = meta;

    while (tmp != NULL) {

        camino->push_front(tmp);
        tmp = tmp->getPadre();

    }
    int costo = 0;

    //variables que cargarán la anterior posición
    int old_x = 0;
    int old_y = 0;

    for (int i = 0; i < camino->size(); i++) {

        int posI = camino->at(i)->getPosI();
        int posJ = camino->at(i)->getPosJ();

        cout << "El costo en " << posI << "," << posJ << " es: " << camino->at(i)->getCosto() << endl;

        //Aqui desplazamos el en la GUI
        QString ruta = get_ruta();
        desplazar(old_x, old_y, posI, posJ, ruta);

        //seteamos old_x y old_y con la posición actual
        old_x = posI;
        old_y = posJ;

        if (matrizValores[posI][posJ] == 3)
            robot->setTraje(true);

        if (robot->getTraje() == true)
            costo += 1;
        else
            costo += camino->at(i)->getCosto();

    }

    cout << "El costo fue de " << costo << " unidades de fuerza\n";

}

/*
 * Para que este método funcione, revisar apropiadamente cómo tener en cuenta que el robot lleve
 * traje en las evaluaciones a las casillas, sobre todo en la de costos, donde se consideran muchas
 * ramas y no en todas el robot lleva el traje
 * */

int Tablero::explorar(int i, int j) {

    // Toma valor en la matriz asociada
    int codigo = matrizValores[i][j];

    if (codigo == 1) return -1; // Muros

    else if (robot->getTraje() == true) return 1; // Si lleva traje es inmune

    // Si no lleva traje
    else {

        if (codigo == 0 || codigo == 3 || codigo == 6) return 1; // Si no es ningún campo magnético

        else if (codigo == 4) return 4; // Campo magnético tipo 1

        else if (codigo == 5) return 7; // Campo magnético tipo 2

    }

    return -1;

}

QString Tablero::get_ruta(){
    QString ruta = "";
    //definimos el perfil en el que estamos para seleccionar la ruta
    int perfil = 1;

    switch (perfil) {
        case 0:
            ruta = "/home/anderojas/Proyectos/Magnobot/Iconos/";
        break;
        case 1:
            ruta = "/home/alchemixt-ub16/Documentos/Proyectos/Magnobot/Iconos/";
        break;
    }
    return ruta;
}

void Tablero::desplazar(int a, int b, int x, int y, QString ruta){
    cout<<"desplazando desde "<<a<<","<<b<<" hacia"<<x<<","<<y<<endl;
    QTableWidgetItem *casilla_ant = ui->tableTableroJuego->item(a, b);
    QTableWidgetItem *casilla_act = ui->tableTableroJuego->item(x, y);

    if(a==0 && b==0){}else{ casilla_ant->setIcon(QPixmap::fromImage(QImage(ruta+"Pared04.png")));}
    casilla_act->setIcon(QPixmap::fromImage(QImage(ruta+"mega01.png")));

    QThread::sleep(1);
    ui->tableTableroJuego->repaint();
}

