#include "tablero.hpp"
#include "ui_tablero.h"
#include <iostream>
#include <string>
#include <QThread>
#include <QInputDialog>
using namespace std;

Tablero::Tablero(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tablero)
{
    ui->setupUi(this);
    get_ruta();
    ruta += "/";
    cout << ruta.toStdString();

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
    else if (ui->comboBoxAlgoritmo->currentText() == "Profundidad (evita ciclos)") busquedaProfundidad();
    else if (ui->comboBoxAlgoritmo->currentText() == "Costo uniforme") buscaCostoUniforme();
    else if (ui->comboBoxAlgoritmo->currentText() == "Avara") busquedaAvara();
    else if (ui->comboBoxAlgoritmo->currentText() == "A*") busquedaAEstrella();
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
                robot->addObjetivo(lineaTableroI, j);

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

int Tablero::calcularHeuristica(int i, int j) {

    Nodo *objetivoBuscado = robot->getPosicionObjetivo(0);

    //cout << "Entra para heurística (" << i << "," << j << ")\n";

    int dif_i = qAbs(objetivoBuscado->getPosI() - i);
    int dif_j = qAbs(objetivoBuscado->getPosJ() - j);

    int manhattan = dif_i + dif_j;

    int heuristica = manhattan;

    for (int k = 1; k < robot->getPosicionesObjetivos()->size(); k++) {

        heuristica += robot->getPosicionObjetivo(k)->getCostoEstimado();

    }

    //cout << "Heurística = " << heuristica << endl;
    //cout << "Costo real acumulado = " << costoReal << endl;
    //cout << heuristica << endl;
    return heuristica;

}

void Tablero::busquedaAEstrella(){

    QVector<Nodo*> *nodosTmp = new QVector<Nodo*>();
    int flag = robot->getPosicionesObjetivos()->size();
    int pos_i = robot->getPosI();
    int pos_j = robot->getPosJ();
    int nuevaPosI = pos_i;
    int nuevaPosJ = pos_j;

    while (flag > 0) {

        for (int i = 0; i < robot->getPosicionesObjetivos()->size(); i++) {

            nuevaPosI = robot->getPosicionesObjetivos()->at(i)->getPosI();
            nuevaPosJ = robot->getPosicionesObjetivos()->at(i)->getPosJ();

            int diferenciaI = qAbs(pos_i - nuevaPosI);
            int diferenciaJ = qAbs(pos_j - nuevaPosJ);

            int manhattan = diferenciaI + diferenciaJ;
            robot->getPosicionesObjetivos()->at(i)->setCostoEstimado(manhattan);



        }

        ordenarNodosObjetivos();
        nodosTmp->append(robot->getPosicionObjetivo(0));
        robot->getPosicionesObjetivos()->pop_front();
        flag--;
        pos_i = nodosTmp->at(nodosTmp->size()-1)->getPosI();
        pos_j = nodosTmp->at(nodosTmp->size()-1)->getPosJ();

    }

    int heuristica = 0;

    for (int i = 0; i < nodosTmp->size(); i++) {

        robot->getPosicionesObjetivos()->append(nodosTmp->at(i));
        heuristica += nodosTmp->at(i)->getCostoEstimado();
        cout << "Costo para el objetivo " << (i+1) << "de: " << nodosTmp->at(i)->getCostoEstimado() << endl;

    }

    cout << "Iniciando búsqueda por Avara\n";
    // Posición inicial es la posición del robot
    int posIRobot = robot->getPosI();
    int posJRobot = robot->getPosJ();

    int numeroNodosExpandidos = 0;
    int numObjetivos = 0;

    Nodo *raiz = new Nodo(posIRobot, posJRobot, NULL, 0, false, 0, 0, heuristica);
    arbol->append(raiz);
    Nodo *meta = NULL;

    while (!robot->objetivosCompletos()) {

        Nodo *nodo = arbol->first();
        int i = nodo->getPosI();
        int j = nodo->getPosJ();

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
            numObjetivos += 1;
            nodo->setValida();

        }

        // Si el código es un traje...
        else if (codigo == 3) {

            nodo->setTraje(true);
            numObjetivos += 1;
            nodo->setValida();

        }

        // Si ha encontrado todos los objetivos
        if (robot->objetivosCompletos()) {

            // ¡Tenemos la meta! ¡Eureka!
            meta = nodo;

        }

        else {

            numeroNodosExpandidos++;

            if (i > 0) {

                int posI = i-1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje()); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        Nodo *tmp = nodo->getPadre();
                        bool crear = true;

                        while (tmp != NULL) {

                            // Evita devolverse a los padres ...
                            if (tmp->getPosI() == posI &&
                                    tmp->getPosJ() == j && numObjetivos == tmp->getValida()) {

                                crear = false;
                                break;

                            }

                            tmp = tmp->getPadre();

                        }

                        if (crear == true) {

                            int nuevaHeuristica = calcularHeuristica(posI, j);
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                       numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                            arbol->append(nuevoNodo);

                        }

                    }

                    else {

                        int nuevaHeuristica = calcularHeuristica(posI, j);
                        Nodo *nuevoNodo = new Nodo(posI,j,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                   numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (i < (ui->tableTableroJuego->rowCount() - 1)) {

                int posI = i+1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje()); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        Nodo *tmp = nodo->getPadre();
                        bool crear = true;

                        while (tmp != NULL) {

                            // Evita devolverse a los padres ...
                            if (tmp->getPosI() == posI &&
                                    tmp->getPosJ() == j && numObjetivos == tmp->getValida()) {

                                crear = false;
                                break;

                            }

                            tmp = tmp->getPadre();

                        }

                        if (crear == true) {

                            int nuevaHeuristica = calcularHeuristica(posI, j);
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                       numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                            arbol->append(nuevoNodo);

                        }

                    }

                    else {

                        int nuevaHeuristica = calcularHeuristica(posI, j);
                        Nodo *nuevoNodo = new Nodo(posI,j,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                   numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j > 0) {

                int posJ = j-1;
                int costoAcumulado = explorar(i, posJ,nodo->getTraje()); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        Nodo *tmp = nodo->getPadre();
                        bool crear = true;

                        while (tmp != NULL) {

                            // Evita devolverse a los padres ...
                            if (tmp->getPosI() == i &&
                                    tmp->getPosJ() == posJ && numObjetivos == tmp->getValida()) {

                                crear = false;
                                break;

                            }

                            tmp = tmp->getPadre();

                        }

                        if (crear == true) {

                            int nuevaHeuristica = calcularHeuristica(i, posJ);
                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                       numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                            arbol->append(nuevoNodo);

                        }

                    }

                    else {

                        int nuevaHeuristica = calcularHeuristica(i, posJ);
                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                   numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j < (ui->tableTableroJuego->columnCount() - 1)) {

                int posJ = j+1;
                int costoAcumulado = explorar(i, posJ,nodo->getTraje()); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        Nodo *tmp = nodo->getPadre();
                        bool crear = true;

                        while (tmp != NULL) {

                            // Evita devolverse a los padres ...
                            if (tmp->getPosI() == i &&
                                    tmp->getPosJ() == posJ && numObjetivos == tmp->getValida()) {

                                crear = false;
                                break;

                            }

                            tmp = tmp->getPadre();

                        }

                        if (crear == true) {

                            int nuevaHeuristica = calcularHeuristica(i, posJ);
                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                       numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                            arbol->append(nuevoNodo);

                        }

                    }

                    else {

                        int nuevaHeuristica = calcularHeuristica(i, posJ);
                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                   numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                        arbol->append(nuevoNodo);

                    }

                }

            }

        }

        cout << "Heurística en (" << nodo->getPosI() << "," << nodo->getPosJ() << "): " <<
                nodo->getCostoEstimado() << endl;
        cout << "Costo en (" << nodo->getPosI() << "," << nodo->getPosJ() << "): " <<
                nodo->getCosto() << endl;
        cout << "Valor de f(n) (" << nodo->getPosI() << "," << nodo->getPosJ() << "): " <<
                nodo->getCostoEstimado(true) << endl;
        arbol->pop_front();
        ordenarArbol(true, true);

    }

    Nodo *tmp = meta;
    cout << "Profundidad del árbol = " << meta->getProfundidad() << endl;
    cout << "Número de nodos expandidos = " << numeroNodosExpandidos << endl;

    while (tmp != NULL) {

        camino->push_front(tmp);
        tmp = tmp->getPadre();

    }

    //variables que cargarán la anterior posición
    int old_x = 0;
    int old_y = 0;

    for (int i = 0; i < camino->size(); i++) {

        int posI = camino->at(i)->getPosI();
        int posJ = camino->at(i)->getPosJ();

        //cout << "El costo en " << posI << "," << posJ << " es: " << camino->at(i)->getCosto() << endl;

        //Aqui desplazamos el en la GUI
        desplazar(old_x, old_y, posI, posJ, ruta);

        //seteamos old_x y old_y con la posición actual
        old_x = posI;
        old_y = posJ;
    }

    cout << "El costo fue de " << camino->at(camino->size()-1)->getCosto() << " unidades de fuerza\n";

}


//Algoritmo de busqueda informada->Avara
void Tablero::busquedaAvara(){

    QVector<Nodo*> *nodosTmp = new QVector<Nodo*>();
    int flag = robot->getPosicionesObjetivos()->size();
    int pos_i = robot->getPosI();
    int pos_j = robot->getPosJ();
    int nuevaPosI = pos_i;
    int nuevaPosJ = pos_j;

    while (flag > 0) {

        for (int i = 0; i < robot->getPosicionesObjetivos()->size(); i++) {

            nuevaPosI = robot->getPosicionesObjetivos()->at(i)->getPosI();
            nuevaPosJ = robot->getPosicionesObjetivos()->at(i)->getPosJ();

            int diferenciaI = qAbs(pos_i - nuevaPosI);
            int diferenciaJ = qAbs(pos_j - nuevaPosJ);

            int manhattan = diferenciaI + diferenciaJ;
            robot->getPosicionesObjetivos()->at(i)->setCostoEstimado(manhattan);



        }

        ordenarNodosObjetivos();
        nodosTmp->append(robot->getPosicionObjetivo(0));
        robot->getPosicionesObjetivos()->pop_front();
        flag--;
        pos_i = nodosTmp->at(nodosTmp->size()-1)->getPosI();
        pos_j = nodosTmp->at(nodosTmp->size()-1)->getPosJ();

    }

    int heuristica = 0;

    for (int i = 0; i < nodosTmp->size(); i++) {

        robot->getPosicionesObjetivos()->append(nodosTmp->at(i));
        heuristica += nodosTmp->at(i)->getCostoEstimado();
        cout << "Costo para el objetivo " << (i+1) << "de: " << nodosTmp->at(i)->getCostoEstimado() << endl;

    }

    cout << "Iniciando búsqueda por Avara\n";
    // Posición inicial es la posición del robot
    int posIRobot = robot->getPosI();
    int posJRobot = robot->getPosJ();

    int numeroNodosExpandidos = 0;
    int numObjetivos = 0;

    Nodo *raiz = new Nodo(posIRobot, posJRobot, NULL, 0, false, 0, 0, heuristica);
    arbol->append(raiz);
    Nodo *meta = NULL;

    while (!robot->objetivosCompletos()) {

        Nodo *nodo = arbol->first();
        int i = nodo->getPosI();
        int j = nodo->getPosJ();

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
            numObjetivos += 1;
            nodo->setValida();

        }

        // Si el código es un traje...
        else if (codigo == 3) {

            nodo->setTraje(true);
            numObjetivos += 1;
            nodo->setValida();

        }

        // Si ha encontrado todos los objetivos
        if (robot->objetivosCompletos()) {

            // ¡Tenemos la meta! ¡Eureka!
            meta = nodo;

        }

        else {

            numeroNodosExpandidos++;

            if (i > 0) {

                int posI = i-1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje()); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        Nodo *tmp = nodo->getPadre();
                        bool crear = true;

                        while (tmp != NULL) {

                            // Evita devolverse a los padres ...
                            if (tmp->getPosI() == posI &&
                                    tmp->getPosJ() == j && numObjetivos == tmp->getValida()) {

                                crear = false;
                                break;

                            }

                            tmp = tmp->getPadre();

                        }

                        if (crear == true) {

                            int nuevaHeuristica = calcularHeuristica(posI, j);
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                       numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                            arbol->append(nuevoNodo);

                        }

                    }

                    else {

                        int nuevaHeuristica = calcularHeuristica(posI, j);
                        Nodo *nuevoNodo = new Nodo(posI,j,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                   numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (i < (ui->tableTableroJuego->rowCount() - 1)) {

                int posI = i+1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje()); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        Nodo *tmp = nodo->getPadre();
                        bool crear = true;

                        while (tmp != NULL) {

                            // Evita devolverse a los padres ...
                            if (tmp->getPosI() == posI &&
                                    tmp->getPosJ() == j && numObjetivos == tmp->getValida()) {

                                crear = false;
                                break;

                            }

                            tmp = tmp->getPadre();

                        }

                        if (crear == true) {

                            int nuevaHeuristica = calcularHeuristica(posI, j);
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                       numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                            arbol->append(nuevoNodo);

                        }

                    }

                    else {

                        int nuevaHeuristica = calcularHeuristica(posI, j);
                        Nodo *nuevoNodo = new Nodo(posI,j,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                   numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j > 0) {

                int posJ = j-1;
                int costoAcumulado = explorar(i, posJ,nodo->getTraje()); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        Nodo *tmp = nodo->getPadre();
                        bool crear = true;

                        while (tmp != NULL) {

                            // Evita devolverse a los padres ...
                            if (tmp->getPosI() == i &&
                                    tmp->getPosJ() == posJ && numObjetivos == tmp->getValida()) {

                                crear = false;
                                break;

                            }

                            tmp = tmp->getPadre();

                        }

                        if (crear == true) {

                            int nuevaHeuristica = calcularHeuristica(i, posJ);
                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                       numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                            arbol->append(nuevoNodo);

                        }

                    }

                    else {

                        int nuevaHeuristica = calcularHeuristica(i, posJ);
                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                   numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j < (ui->tableTableroJuego->columnCount() - 1)) {

                int posJ = j+1;
                int costoAcumulado = explorar(i, posJ,nodo->getTraje()); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        Nodo *tmp = nodo->getPadre();
                        bool crear = true;

                        while (tmp != NULL) {

                            // Evita devolverse a los padres ...
                            if (tmp->getPosI() == i &&
                                    tmp->getPosJ() == posJ && numObjetivos == tmp->getValida()) {

                                crear = false;
                                break;

                            }

                            tmp = tmp->getPadre();

                        }

                        if (crear == true) {

                            int nuevaHeuristica = calcularHeuristica(i, posJ);
                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                       numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                            arbol->append(nuevoNodo);

                        }

                    }

                    else {

                        int nuevaHeuristica = calcularHeuristica(i, posJ);
                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo, nodo->getCosto()+costoAcumulado, nodo->getTraje(),
                                                   numObjetivos, nodo->getProfundidad() + 1, nuevaHeuristica);
                        arbol->append(nuevoNodo);

                    }

                }

            }

        }

        cout << "Heurística en (" << nodo->getPosI() << "," << nodo->getPosJ() << "): " << nodo->getCostoEstimado() << endl;
        arbol->pop_front();
        ordenarArbol(true, false);

    }

    Nodo *tmp = meta;
    cout << "Profundidad del árbol = " << meta->getProfundidad() << endl;
    cout << "Número de nodos expandidos = " << numeroNodosExpandidos << endl;

    while (tmp != NULL) {

        camino->push_front(tmp);
        tmp = tmp->getPadre();

    }

    cout << "Ruta escogida\n";
    for (int i = 0; i < camino->size(); i++) {

        cout << "(" << camino->at(i)->getPosI() << "," << camino->at(i)->getPosJ() << ")\n";

    }

    //variables que cargarán la anterior posición
    int old_x = 0;
    int old_y = 0;

    for (int i = 0; i < camino->size(); i++) {

        int posI = camino->at(i)->getPosI();
        int posJ = camino->at(i)->getPosJ();

        cout << "El costo en " << posI << "," << posJ << " es: " << camino->at(i)->getCosto() << endl;

        //Aqui desplazamos el en la GUI
        desplazar(old_x, old_y, posI, posJ, ruta);

        //seteamos old_x y old_y con la posición actual
        old_x = posI;
        old_y = posJ;
    }

    cout << "El costo fue de " << camino->at(camino->size()-1)->getCosto() << " unidades de fuerza\n";

}

void Tablero::busquedaAmplitud() {

    cout << "Iniciando búsqueda por amplitud\n";
    // Posición inicial es la posición del robot
    int posIRobot = robot->getPosI();
    int posJRobot = robot->getPosJ();

    int numeroNodosExpandidos = 0;

    // Se crea el nodo raíz con la posición del robot
    Nodo *raiz = new Nodo(posIRobot, posJRobot, NULL, 0, false, 0, 0);
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
            cout << "Eliminando objetivo encontrado\n";

            robot->eliminarObjetivo();
            matrizValores[i][j] = 0;
            arbol->clear();
            arbol->append(nodo);
            cout << "objetivo encontrado en (" << i << "," << j << ")" << endl;
            devolver = true;

        }

        // Si el código es un traje...
        else if (codigo == 3) {

            nodo->setTraje(true);

        }

        // Si ha encontrado todos los objetivos
        if (robot->objetivosCompletos()) {

            // ¡Tenemos la meta! ¡Eureka!
            meta = nodo;
            cout << "Eureka\n";

        }

        // Si faltan objetivos
        else {

            // Se suma 1 al número de nodos expandidos

            numeroNodosExpandidos++;

            /* Los if a continuación son usados para evaluar si se puede mover a izquierda, derecha
             * arriba o a abajo, para evitar desbordamientos
             * */

            if (i > 0) {

                int posI = i-1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje()); // Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        // Evita devolverse al padre...
                        if (!(nodo->getPadre()->getPosI() == posI &&
                                nodo->getPadre()->getPosJ() == j)) {

                            // Si no es la posición del padre crea un nuevo nodo (campo) para ser evaluado)
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);

                        }

                        // Se devuelve sólo si en la posición actual encontró un objetivo
                        // variable devolver de tipo bool
                        else if (devolver == true) {

                            // Crea un nodo y pone false a devolver
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                    }

                    // Si es la raíz no hay problemas. No existe padre
                    else {

                        Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                   nodo->getProfundidad() + 1);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (i < (ui->tableTableroJuego->rowCount()-1)) {

                int posI = i+1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje());
                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (!(nodo->getPadre()->getPosI() == posI &&
                                nodo->getPadre()->getPosJ() == j)) {

                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);

                        } else if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                   nodo->getProfundidad() + 1);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j > 0) {

                int posJ = j-1;
                int costoAcumulado = explorar(i, posJ, nodo->getTraje());
                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (!(nodo->getPadre()->getPosI() == i &&
                                nodo->getPadre()->getPosJ() == posJ)) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);

                        } else if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                   nodo->getProfundidad() + 1);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j < ui->tableTableroJuego->columnCount()-1) {

                int posJ = j+1;
                int costoAcumulado = explorar(i, posJ, nodo->getTraje());
                if (costoAcumulado != -1) {
                    if (nodo != raiz) {

                        if (!(nodo->getPadre()->getPosI() == i &&
                                nodo->getPadre()->getPosJ() == posJ)) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);

                        } else if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), 0,
                                                   nodo->getProfundidad() + 1);
                        arbol->append(nuevoNodo);

                    }

                }

            }

        }

        // Elimina el primer nodo del vector
        arbol->pop_front();

    }

    Nodo *tmp = meta;
    cout << "Profundidad del árbol = " << meta->getProfundidad() << endl;
    cout << "Número de nodos expandidos = " << numeroNodosExpandidos << endl;

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

void Tablero::ordenarArbol(bool flag1, bool flag2){

    int i,j = 0;
    Nodo *v = NULL;

    for (i = 1; i < arbol->size(); i++){
         v = arbol->at(i);
         j = i - 1;

         if (flag1 == false) {

             while (j >= 0 && arbol->at(j)->getCosto() > v->getCosto()){
                arbol->replace((j + 1),arbol->at(j));
                j--;
             }

             arbol->replace((j + 1),v);

         }

         else {

             if (flag2 == true) {

                 while (j >= 0 && arbol->at(j)->getCostoEstimado(true) > v->getCostoEstimado(true)){
                    arbol->replace((j + 1),arbol->at(j));
                    j--;
                 }

                 arbol->replace((j + 1),v);

             }

             else {

                 while (j >= 0 && arbol->at(j)->getCostoEstimado() > v->getCostoEstimado()){
                    arbol->replace((j + 1),arbol->at(j));
                    j--;
                 }

                 arbol->replace((j + 1),v);

             }

         }

    }

}

void Tablero::ordenarNodosObjetivos(){

    int i,j = 0;
    Nodo *v = NULL;

    for (i = 1; i < robot->getPosicionesObjetivos()->size(); i++){
         v = robot->getPosicionesObjetivos()->at(i);
         j = i - 1;

         while (j >= 0 && robot->getPosicionesObjetivos()->at(j)->getCostoEstimado() > v->getCostoEstimado()){
                robot->getPosicionesObjetivos()->replace((j + 1),robot->getPosicionesObjetivos()->at(j));
                j--;
         }

         robot->getPosicionesObjetivos()->replace((j + 1),v);
    }

}

void Tablero::buscaCostoUniforme() {

    int numeroNodosExpandidos = 0;

    // Posición inicial es la posición del robot
    int posIRobot = robot->getPosI();
    int posJRobot = robot->getPosJ();

    // Se crea el nodo raíz con la posición del robot
    Nodo *raiz = new Nodo(posIRobot, posJRobot, NULL, 0,false,0, 0);
    // Se concatena al vector de búsqueda por amplitud
    arbol->append(raiz);
    // El nodo meta es cuando encuentra el último objetivo
    Nodo *meta = NULL;
    bool devolver = false;
    int numObjetivos = 0;

    int para = 0;

    while (!robot->objetivosCompletos()) {  // Mientras le falte uno o más objetivos...
        para ++;
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
            numObjetivos += 1;
            nodo->setValida();

        }

        // Si el código es un traje...
        else if (codigo == 3) {

            nodo->setTraje(true);
            numObjetivos += 1;
            nodo->setValida();
            cout << "validador de devolución vale " << nodo->getValida() << endl;
            cout << "Validador anterior vale " << nodo->getPadre()->getValida() << endl;

        }

        // Si ha encontrado todos los objetivos
        if (robot->objetivosCompletos()) {

            // ¡Tenemos la meta! ¡Eureka!
            meta = nodo;

        }

        // Si faltan objetivos
        else {

            cout << "Expandiendo nodo (" << nodo->getPosI() << "," << nodo->getPosJ() << ")\n";
            numeroNodosExpandidos++;

            /* Los if a continuación son usados para evaluar si se puede mover a izquierda, derecha
             * arriba o a abajo, para evitar desbordamientos
             * */

            if (i < (ui->tableTableroJuego->rowCount()-1)) {

                int posI = i+1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje());
                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                        else {

                            Nodo *tmp = nodo->getPadre();
                            bool crear = true;

                            while (tmp != NULL) {

                                // Evita devolverse a los padres ...
                                if (tmp->getPosI() == posI &&
                                        tmp->getPosJ() == j && nodo->getValida() == tmp->getValida()) {

                                    crear = false;
                                    break;

                                }

                                tmp = tmp->getPadre();

                            }

                            if (crear == true) {

                                Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                           nodo->getProfundidad() + 1);
                                arbol->append(nuevoNodo);

                            }

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                   nodo->getProfundidad() + 1);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j < ui->tableTableroJuego->columnCount()-1) {

                int posJ = j+1;
                int costoAcumulado = explorar(i, posJ, nodo->getTraje());

                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);
                            devolver = false;

                        }

                        else {

                            Nodo *tmp = nodo->getPadre();
                            bool crear = true;

                            while (tmp != NULL) {

                                // Evita devolverse a los padres ...
                                if (tmp->getPosI() == i &&
                                        tmp->getPosJ() == posJ && nodo->getValida() == tmp->getValida()) {

                                    crear = false;
                                    break;

                                }

                                tmp = tmp->getPadre();

                            }

                            if (crear == true) {

                                Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                           nodo->getProfundidad() + 1);
                                arbol->append(nuevoNodo);

                            }

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                   nodo->getProfundidad() + 1);
                        arbol->append(nuevoNodo);

                    }

                }

            }

            if (j > 0) {

                int posJ = j-1;
                int costoAcumulado = explorar(i, posJ, nodo->getTraje());

                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);
                            devolver = false;


                        }

                        else {

                            Nodo *tmp = nodo->getPadre();
                            bool crear = true;

                            while (tmp != NULL) {

                                // Evita devolverse a los padres ...
                                if (tmp->getPosI() == i &&
                                        tmp->getPosJ() == posJ && nodo->getValida() == tmp->getValida()) {

                                    crear = false;
                                    break;

                                }

                                tmp = tmp->getPadre();

                            }

                            if (crear == true) {

                                Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                           nodo->getProfundidad() + 1);
                                arbol->append(nuevoNodo);

                            }

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                   nodo->getProfundidad() + 1);
                        arbol->append(nuevoNodo);


                    }

                }

            }


            if (i > 0) {

                int posI = i-1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje());// Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        if (devolver == true) {

                            // Crea un nodo y pone false a devolver
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                       nodo->getProfundidad() + 1);
                            arbol->append(nuevoNodo);
                            devolver = false;


                        }

                        else {

                            Nodo *tmp = nodo->getPadre();
                            bool crear = true;

                            while (tmp != NULL) {

                                // Evita devolverse a los padres
                                if (tmp->getPosI() == posI &&
                                        tmp->getPosJ() == j && nodo->getValida() == tmp->getValida()) {

                                    crear = false;
                                    break;

                                }

                                tmp = tmp->getPadre();

                            }

                            if (crear == true) {

                                Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                           nodo->getProfundidad() + 1);
                                arbol->append(nuevoNodo);


                            }

                        }

                    }

                    // Si es la raíz no hay problemas. No existe padre
                    else {

                        Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado+nodo->getCosto(), nodo->getTraje(), numObjetivos,
                                                   nodo->getProfundidad() + 1);
                        arbol->append(nuevoNodo);

                    }

                }

            }

        }

        // Elimina el primer nodo del vector

        arbol->pop_front();
        ordenarArbol();
        cout << "(" << nodo->getPosI() << "," << nodo->getPosJ() << ") con costo de " << nodo->getCosto() << endl;

    }

    Nodo *tmp = meta;
    cout << "La profundidad por búsqueda costo uniforme = " << meta->getProfundidad() << endl;
    cout << "Número de nodos expandidos = " << numeroNodosExpandidos << endl;

    while (tmp != NULL) {

        camino->push_front(tmp);
        tmp = tmp->getPadre();

    }

    //variables que cargarán la anterior posición
    int old_x = 0;
    int old_y = 0;

    for (int i = 0; i < camino->size(); i++) {

        int posI = camino->at(i)->getPosI();
        int posJ = camino->at(i)->getPosJ();

        //Aqui desplazamos el en la GUI
        desplazar(old_x, old_y, posI, posJ, ruta);

        //seteamos old_x y old_y con la posición actual
        old_x = posI;
        old_y = posJ;

    }

    cout << "El costo fue de " << camino->at(camino->size()-1)->getCosto() << " unidades de fuerza\n";

}


/*
 * Para que este método funcione, revisar apropiadamente cómo tener en cuenta que el robot lleve
 * traje en las evaluaciones a las casillas, sobre todo en la de costos, donde se consideran muchas
 * ramas y no en todas el robot lleva el traje
 * */

int Tablero::explorar(int i, int j, bool traje) {

    // Toma valor en la matriz asociada
    int codigo = matrizValores[i][j];

    if (codigo == 1) return -1; // Muros

    else if (traje == true) return 1; // Si lleva traje es inmune

    // Si no lleva traje
    else {

        if (codigo == 0 || codigo == 3 || codigo == 6) return 1; // Si no es ningún campo magnético

        else if (codigo == 4) return 4; // Campo magnético tipo 1

        else if (codigo == 5) return 7; // Campo magnético tipo 2

    }

    return -1;

}

void Tablero::get_ruta(){
    //definimos el perfil en el que estamos para seleccionar la ruta
    int perfil = 0;

    bool ok;
    QInputDialog* inputDialog = new QInputDialog();
    inputDialog->setOptions(QInputDialog::NoButtons);

    QString text =  inputDialog->getText(NULL ,"QInputDialog::getText() Example",
                                          "Escoja su perfil\n"
                                          "0) Anderson\n"
                                          "1) Jhon Erik\n"
                                          "2) Julián\n"
                                          "3) Otro", QLineEdit::Normal,
                                          QDir::home().dirName(), &ok);

     if (ok && !text.isEmpty())
     {
        perfil = text.toInt();
     }
     switch (perfil) {
        case 0:
            ruta = "/home/anderojas/Proyectos/Magnobot/Iconos/";
        break;
        case 1:
            ruta = "/home/alchemixt-ub16/Documentos/Proyectos/Magnobot/Iconos/";
        break;
        case 2:
            ruta = "/home/julian/Desktop/IA/Proyecto copia /MagnobotIA/Magnobot/Iconos/";
        break;
        case 3:
            ruta = QFileDialog::getExistingDirectory(this, tr("Abrir directorio iconos"), "/home", QFileDialog::ShowDirsOnly);
        break;

    }
}

void Tablero::desplazar(int a, int b, int x, int y, QString ruta){
    //cout<<"desplazando desde "<<a<<","<<b<<" hacia"<<x<<","<<y<<endl;
    QTableWidgetItem *casilla_ant = ui->tableTableroJuego->item(a, b);
    QTableWidgetItem *casilla_act = ui->tableTableroJuego->item(x, y);

    if(a==0 && b==0){}else{ casilla_ant->setIcon(QPixmap::fromImage(QImage(ruta+"Pared04.jpg")));}
    casilla_act->setIcon(QPixmap::fromImage(QImage(ruta+"mega01.png")));

    QThread::sleep(1);
    ui->tableTableroJuego->repaint();
}

void Tablero::busquedaProfundidad() {

    // Variable para los nodos expandidos
    int numeroNodosExpandidos = 0;

    // Posición inicial es la posición del robot
    int posIRobot = robot->getPosI();
    int posJRobot = robot->getPosJ();

    // Se crea el nodo raíz con la posición del robot
    Nodo *raiz = new Nodo(posIRobot, posJRobot, NULL, 0, false, 0, 0);
    // Se concatena al vector de búsqueda por amplitud
    arbol->append(raiz);
    // El nodo meta es cuando encuentra el último objetivo
    Nodo *meta = NULL;
    bool devolver = false;
    int numObjetivos = 0;

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
            cout << "objetivo encontrado en (" << i << "," << j << ")" << endl;
            devolver = true;
            arbol->clear();
            arbol->append(nodo);
            nodo->setValida();
            cout << "Pasa por la eliminación del árbol\n";
            numObjetivos++;

        }

        // Si el código es un traje...
        else if (codigo == 3) {

            nodo->setTraje(true);
            devolver = true;
            nodo->setValida();
            numObjetivos++;

        }

        // Posición a insertar. Sirve para eliminar el padre después de crear los hijos
        int posInsert = 0;

        // Si ha encontrado todos los objetivos
        if (robot->objetivosCompletos()) {

            // ¡Tenemos la meta! ¡Eureka!
            meta = nodo;

        }

        // Si faltan objetivos

        else {

            // Sumar 1 al número de nodos expandidos
            numeroNodosExpandidos++;

             /* Los if a continuación son usados para evaluar si se puede mover a izquierda, derecha
             * arriba o a abajo, para evitar desbordamientos
             * */

            if (i < (ui->tableTableroJuego->rowCount()-1)) {

                int posI = i+1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje());
                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                       nodo->getProfundidad() + 1);
                            arbol->insert(posInsert, nuevoNodo);
                            devolver = false;
                            posInsert++;

                        }

                        else {

                            Nodo *tmp = nodo->getPadre();
                            bool crear = true;

                            while (tmp != NULL) {

                                // Evita devolverse a los padres ...
                                if (tmp->getPosI() == posI &&
                                        tmp->getPosJ() == j && numObjetivos == tmp->getValida()) {

                                    crear = false;

                                }

                                tmp = tmp->getPadre();

                            }

                            if (crear == true) {

                                Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                           nodo->getProfundidad() + 1);
                                arbol->insert(posInsert, nuevoNodo);
                                posInsert++;

                            }

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                   nodo->getProfundidad() + 1);
                        arbol->insert(posInsert, nuevoNodo);
                        posInsert++;

                    }

                }

            }

            if (j < ui->tableTableroJuego->columnCount()-1) {

                int posJ = j+1;
                int costoAcumulado = explorar(i, posJ, nodo->getTraje());

                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                       nodo->getProfundidad() + 1);
                            arbol->insert(posInsert, nuevoNodo);
                            devolver = false;
                            posInsert++;

                        }

                        else {

                            Nodo *tmp = nodo->getPadre();
                            bool crear = true;

                            while (tmp != NULL) {

                                // Evita devolverse a los padres ...
                                if (tmp->getPosI() == i &&
                                        tmp->getPosJ() == posJ && numObjetivos == tmp->getValida()) {

                                    crear = false;

                                }

                                tmp = tmp->getPadre();

                            }

                            if (crear == true) {

                                Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                           nodo->getProfundidad() + 1);
                                arbol->insert(posInsert, nuevoNodo);
                                posInsert++;

                            }

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                   nodo->getProfundidad() + 1);
                        arbol->insert(posInsert, nuevoNodo);
                        posInsert++;

                    }

                }

            }

            if (j > 0) {

                int posJ = j-1;
                int costoAcumulado = explorar(i, posJ, nodo->getTraje());

                if (costoAcumulado != -1) {

                    if (nodo != raiz) {

                        if (devolver == true) {

                            Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                       nodo->getProfundidad() + 1);
                            arbol->insert(posInsert, nuevoNodo);
                            devolver = false;
                            posInsert++;

                        }

                        else {

                            Nodo *tmp = nodo->getPadre();
                            bool crear = true;

                            while (tmp != NULL) {

                                // Evita devolverse a los padres ...
                                if (tmp->getPosI() == i &&
                                        tmp->getPosJ() == posJ && numObjetivos == tmp->getValida()) {

                                    crear = false;

                                }

                                tmp = tmp->getPadre();

                            }

                            if (crear == true) {

                                Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                           nodo->getProfundidad() + 1);
                                arbol->insert(posInsert, nuevoNodo);
                                posInsert++;

                            }

                        }

                    } else {

                        Nodo *nuevoNodo = new Nodo(i,posJ,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                   nodo->getProfundidad() + 1);
                        arbol->insert(posInsert, nuevoNodo);
                        posInsert++;

                    }

                }

            }


            if (i > 0) {

                int posI = i-1;
                int costoAcumulado = explorar(posI, j,nodo->getTraje());// Explora la posición

                // Si no es un muro
                if (costoAcumulado != -1) {

                    // Si no es la raíz
                    if (nodo != raiz) {

                        if (devolver == true) {

                            // Crea un nodo y pone false a devolver
                            Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                       nodo->getProfundidad() + 1);
                            arbol->insert(posInsert, nuevoNodo);
                            devolver = false;
                            posInsert++;

                        }

                        else {

                            Nodo *tmp = nodo->getPadre();
                            bool crear = true;

                            while (tmp != NULL) {

                                // Evita devolverse a los padres
                                if (tmp->getPosI() == posI &&
                                        tmp->getPosJ() == j && numObjetivos == tmp->getValida()) {

                                    crear = false;

                                }

                                tmp = tmp->getPadre();

                            }

                            if (crear == true) {

                                Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                           nodo->getProfundidad() + 1);
                                arbol->insert(posInsert, nuevoNodo);
                                posInsert++;

                            }

                        }

                    }

                    // Si es la raíz no hay problemas. No existe padre
                    else {

                        Nodo *nuevoNodo = new Nodo(posI,j,nodo,costoAcumulado, nodo->getTraje(), numObjetivos,
                                                   nodo->getProfundidad() + 1);
                        arbol->insert(posInsert, nuevoNodo);
                        posInsert++;

                    }

                }

            }

        }

        // Elimina el nodo padre
        arbol->remove(posInsert);

    }

    Nodo *tmp = meta;
    cout << "La profundidad por búsqueda preferente por profundidad = " << meta->getProfundidad() << endl;
    cout << "Número de nodos expandidos = " << numeroNodosExpandidos << endl;

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
