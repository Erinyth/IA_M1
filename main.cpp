#include <iostream>
#include "bdc.hh"
#include "moteur.hh"
#include <QApplication>
#include "mainwindow.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTranslator qtTranslator;
    qtTranslator.load("qt_"+QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    return a.exec();
}

