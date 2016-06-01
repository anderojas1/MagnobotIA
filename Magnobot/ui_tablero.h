/********************************************************************************
** Form generated from reading UI file 'tablero.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLERO_H
#define UI_TABLERO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tablero
{
public:
    QWidget *centralWidget;
    QPushButton *buttonSalir;
    QPushButton *buttonSubirArchivo;
    QLineEdit *lineRutaArchivo;
    QLabel *labelOpcionesArchivo;
    QPushButton *buttonCargarArchivo;
    QLabel *labelBusqueda;
    QComboBox *comboBoxBusqueda;
    QLabel *labelAlgoritmo;
    QComboBox *comboBoxAlgoritmo;
    QPushButton *buttonEjecutar;
    QLabel *labelOpcionesBusqueda;
    QLabel *labelComandos;
    QTableWidget *tableTableroJuego;
    QLabel *lb_univalleLogo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Tablero)
    {
        if (Tablero->objectName().isEmpty())
            Tablero->setObjectName(QStringLiteral("Tablero"));
        Tablero->resize(1019, 690);
        Tablero->setIconSize(QSize(24, 24));
        centralWidget = new QWidget(Tablero);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        buttonSalir = new QPushButton(centralWidget);
        buttonSalir->setObjectName(QStringLiteral("buttonSalir"));
        buttonSalir->setGeometry(QRect(680, 590, 321, 31));
        buttonSalir->setStyleSheet(QStringLiteral("font: 11pt \"Cantarell\";"));
        buttonSubirArchivo = new QPushButton(centralWidget);
        buttonSubirArchivo->setObjectName(QStringLiteral("buttonSubirArchivo"));
        buttonSubirArchivo->setGeometry(QRect(900, 330, 101, 31));
        lineRutaArchivo = new QLineEdit(centralWidget);
        lineRutaArchivo->setObjectName(QStringLiteral("lineRutaArchivo"));
        lineRutaArchivo->setEnabled(false);
        lineRutaArchivo->setGeometry(QRect(680, 330, 221, 31));
        labelOpcionesArchivo = new QLabel(centralWidget);
        labelOpcionesArchivo->setObjectName(QStringLiteral("labelOpcionesArchivo"));
        labelOpcionesArchivo->setGeometry(QRect(780, 290, 141, 31));
        buttonCargarArchivo = new QPushButton(centralWidget);
        buttonCargarArchivo->setObjectName(QStringLiteral("buttonCargarArchivo"));
        buttonCargarArchivo->setGeometry(QRect(680, 360, 321, 31));
        labelBusqueda = new QLabel(centralWidget);
        labelBusqueda->setObjectName(QStringLiteral("labelBusqueda"));
        labelBusqueda->setGeometry(QRect(680, 450, 101, 31));
        comboBoxBusqueda = new QComboBox(centralWidget);
        comboBoxBusqueda->setObjectName(QStringLiteral("comboBoxBusqueda"));
        comboBoxBusqueda->setGeometry(QRect(780, 450, 221, 31));
        labelAlgoritmo = new QLabel(centralWidget);
        labelAlgoritmo->setObjectName(QStringLiteral("labelAlgoritmo"));
        labelAlgoritmo->setGeometry(QRect(680, 480, 81, 31));
        comboBoxAlgoritmo = new QComboBox(centralWidget);
        comboBoxAlgoritmo->setObjectName(QStringLiteral("comboBoxAlgoritmo"));
        comboBoxAlgoritmo->setGeometry(QRect(780, 480, 221, 31));
        buttonEjecutar = new QPushButton(centralWidget);
        buttonEjecutar->setObjectName(QStringLiteral("buttonEjecutar"));
        buttonEjecutar->setGeometry(QRect(680, 560, 321, 31));
        labelOpcionesBusqueda = new QLabel(centralWidget);
        labelOpcionesBusqueda->setObjectName(QStringLiteral("labelOpcionesBusqueda"));
        labelOpcionesBusqueda->setGeometry(QRect(780, 420, 141, 21));
        labelComandos = new QLabel(centralWidget);
        labelComandos->setObjectName(QStringLiteral("labelComandos"));
        labelComandos->setGeometry(QRect(810, 530, 81, 21));
        tableTableroJuego = new QTableWidget(centralWidget);
        if (tableTableroJuego->columnCount() < 10)
            tableTableroJuego->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableTableroJuego->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        if (tableTableroJuego->rowCount() < 10)
            tableTableroJuego->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(4, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(5, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(6, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(7, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(8, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableTableroJuego->setVerticalHeaderItem(9, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        tableTableroJuego->setItem(0, 0, __qtablewidgetitem20);
        tableTableroJuego->setObjectName(QStringLiteral("tableTableroJuego"));
        tableTableroJuego->setGeometry(QRect(0, 0, 661, 621));
        tableTableroJuego->setMaximumSize(QSize(800, 761));
        tableTableroJuego->setSizeIncrement(QSize(40, 40));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        QBrush brush2(QColor(255, 255, 220, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        tableTableroJuego->setPalette(palette);
        tableTableroJuego->setLayoutDirection(Qt::LeftToRight);
        tableTableroJuego->setLineWidth(1);
        tableTableroJuego->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableTableroJuego->setAutoScrollMargin(0);
        tableTableroJuego->setIconSize(QSize(100, 90));
        tableTableroJuego->setShowGrid(true);
        tableTableroJuego->horizontalHeader()->setDefaultSectionSize(65);
        tableTableroJuego->horizontalHeader()->setHighlightSections(true);
        tableTableroJuego->horizontalHeader()->setStretchLastSection(true);
        tableTableroJuego->verticalHeader()->setCascadingSectionResizes(false);
        tableTableroJuego->verticalHeader()->setDefaultSectionSize(60);
        tableTableroJuego->verticalHeader()->setStretchLastSection(true);
        lb_univalleLogo = new QLabel(centralWidget);
        lb_univalleLogo->setObjectName(QStringLiteral("lb_univalleLogo"));
        lb_univalleLogo->setGeometry(QRect(770, 60, 141, 171));
        Tablero->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Tablero);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1019, 22));
        Tablero->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Tablero);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Tablero->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Tablero);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Tablero->setStatusBar(statusBar);

        retranslateUi(Tablero);

        QMetaObject::connectSlotsByName(Tablero);
    } // setupUi

    void retranslateUi(QMainWindow *Tablero)
    {
        Tablero->setWindowTitle(QApplication::translate("Tablero", "Tablero Magnobot", 0));
        buttonSalir->setText(QApplication::translate("Tablero", "Salir", 0));
        buttonSubirArchivo->setText(QApplication::translate("Tablero", "Escoger", 0));
        labelOpcionesArchivo->setText(QApplication::translate("Tablero", "<html><head/><body><p><span style=\" font-weight:600;\">Opciones de archivo</span></p></body></html>", 0));
        buttonCargarArchivo->setText(QApplication::translate("Tablero", "Cargar archivo", 0));
        labelBusqueda->setText(QApplication::translate("Tablero", "B\303\272squeda", 0));
        comboBoxBusqueda->clear();
        comboBoxBusqueda->insertItems(0, QStringList()
         << QApplication::translate("Tablero", "Informada", 0)
         << QApplication::translate("Tablero", "No informada", 0)
        );
        labelAlgoritmo->setText(QApplication::translate("Tablero", "Algoritmo", 0));
        comboBoxAlgoritmo->clear();
        comboBoxAlgoritmo->insertItems(0, QStringList()
         << QApplication::translate("Tablero", "Avara", 0)
         << QApplication::translate("Tablero", "A*", 0)
        );
        buttonEjecutar->setText(QApplication::translate("Tablero", "Ejecutar", 0));
        labelOpcionesBusqueda->setText(QApplication::translate("Tablero", "<html><head/><body><p><span style=\" font-weight:600;\">Opci\303\263n de b\303\272squeda</span></p></body></html>", 0));
        labelComandos->setText(QApplication::translate("Tablero", "<html><head/><body><p><span style=\" font-weight:600;\">Comandos</span></p></body></html>", 0));
        QTableWidgetItem *___qtablewidgetitem = tableTableroJuego->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Tablero", "0", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableTableroJuego->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Tablero", "1", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableTableroJuego->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Tablero", "2", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableTableroJuego->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Tablero", "3", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableTableroJuego->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("Tablero", "4", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableTableroJuego->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("Tablero", "5", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableTableroJuego->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("Tablero", "6", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableTableroJuego->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("Tablero", "7", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableTableroJuego->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("Tablero", "8", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableTableroJuego->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("Tablero", "9", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableTableroJuego->verticalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("Tablero", "0", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableTableroJuego->verticalHeaderItem(1);
        ___qtablewidgetitem11->setText(QApplication::translate("Tablero", "1", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableTableroJuego->verticalHeaderItem(2);
        ___qtablewidgetitem12->setText(QApplication::translate("Tablero", "2", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableTableroJuego->verticalHeaderItem(3);
        ___qtablewidgetitem13->setText(QApplication::translate("Tablero", "3", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableTableroJuego->verticalHeaderItem(4);
        ___qtablewidgetitem14->setText(QApplication::translate("Tablero", "4", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableTableroJuego->verticalHeaderItem(5);
        ___qtablewidgetitem15->setText(QApplication::translate("Tablero", "5", 0));
        QTableWidgetItem *___qtablewidgetitem16 = tableTableroJuego->verticalHeaderItem(6);
        ___qtablewidgetitem16->setText(QApplication::translate("Tablero", "6", 0));
        QTableWidgetItem *___qtablewidgetitem17 = tableTableroJuego->verticalHeaderItem(7);
        ___qtablewidgetitem17->setText(QApplication::translate("Tablero", "7", 0));
        QTableWidgetItem *___qtablewidgetitem18 = tableTableroJuego->verticalHeaderItem(8);
        ___qtablewidgetitem18->setText(QApplication::translate("Tablero", "8", 0));
        QTableWidgetItem *___qtablewidgetitem19 = tableTableroJuego->verticalHeaderItem(9);
        ___qtablewidgetitem19->setText(QApplication::translate("Tablero", "9", 0));

        const bool __sortingEnabled = tableTableroJuego->isSortingEnabled();
        tableTableroJuego->setSortingEnabled(false);
        tableTableroJuego->setSortingEnabled(__sortingEnabled);

        lb_univalleLogo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Tablero: public Ui_Tablero {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLERO_H
