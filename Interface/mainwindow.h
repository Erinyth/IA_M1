#pragma once
#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QGridLayout * _layoutPrincipal;
    QTabWidget * _tabs;

    /* Onglet d'ajout de faits et règles */
    QGridLayout * _layoutBase;

    QGroupBox *createFactOrRuleGroup();

    QLineEdit * _text;

    QPushButton *_show;
    QPushButton *_add;


    /* Onglet d'interrogation de la base */
    QGridLayout * _layoutQuestion;

    QGroupBox *createForwardOrBackwardGroup();

    QLineEdit * _question;

    QPushButton * _send;


    /* Barre de menus */
    void createActions();
    void createMenus();

    void saveToFile();
    void loadFromFile();

    QMenu * _file;
    QAction * _load;
    QAction * _save;
    QAction * _exit;

    QMenu * _help;
    QAction * _aboutUs;
    QAction * _howToUse;


    QWidget * _window;
};
