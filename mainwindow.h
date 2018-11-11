#pragma once
#include <QMainWindow>
#include <QtWidgets>
#include "bdc.hh"
#include "moteur.hh"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void saveToFile();
    void loadFromFile();

    void infoCrea();
    void infoTuto();

    void Add();
    void Test();
    void Affichage();
    void Affichage2();

private:
    baseDeConnaissance BDC;
    Moteur * moteur;

    QGridLayout * _layoutPrincipal;
    QTabWidget * _tabs;

    /* Onglet d'ajout de faits et règles */
    QGridLayout * _layoutBase;

    QVBoxLayout * _vBase;
    QGroupBox * _factOrRule;
    QRadioButton * _fact;
    QRadioButton * _rule;
    QGroupBox *createFactOrRuleGroup();

    QLineEdit * _text;

    QPushButton * _show;
    QPushButton * _add;


    /* Onglet d'interrogation de la base */
    QGridLayout * _layoutQuestion;

    QVBoxLayout * _vQuestionfb;
    QGroupBox * _forwardOrBackward;
    QRadioButton * _forward;
    QRadioButton * _backward;
    QGroupBox *createForwardOrBackwardGroup();

    QVBoxLayout * _vQuestionfh;
    QGroupBox * _firstOrHigher;
    QRadioButton * _first;
    QRadioButton * _higher;
    QGroupBox *createFirstOrHigherGroup();

    QLineEdit * _question;

    QPushButton * _show2;
    QPushButton * _send;


    /* Barre de menus */
    void createActions();
    void createMenus();

    QMenu * _file;
    QAction * _save;
    QAction * _load;
    QAction * _exit;

    QMenu * _help;
    QAction * _aboutUs;
    QAction * _howToUse;


    QWidget * _window;
};
