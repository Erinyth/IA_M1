#include "mainwindow.h"
#include "iostream"
#include <sstream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(400, 200);
    _layoutPrincipal = new QGridLayout();
    _tabs = new QTabWidget();

    /* ---------- ONGLET BASE ---------- */
    _layoutBase = new QGridLayout();
    QWidget * _wBase = new QWidget(this);
    _wBase->setLayout(_layoutBase);

    _layoutBase->addWidget(createFactOrRuleGroup(), 0, 0);

    _text = new QLineEdit();
    _text->setFixedWidth(200);
    _layoutBase->addWidget(_text, 0, 1, 1, 2);

    _show = new QPushButton("Afficher", this);
    _show->setMaximumWidth(70);
    _layoutBase->addWidget(_show, 1, 2);
    _add = new QPushButton("Ajouter", this);
    _add->setMaximumWidth(70);
    _layoutBase->addWidget(_add, 1, 3);

    _tabs->addTab(_wBase, "Base");
    _layoutPrincipal->addWidget(_tabs, 0, 0, 1, 1);



    /* ---------- ONGLET QUESTION ---------- */
    _layoutQuestion = new QGridLayout();
    QWidget * _wQuestion = new QWidget(this);
    _wQuestion->setLayout(_layoutQuestion);

    _layoutQuestion->addWidget(createForwardOrBackwardGroup(), 0, 0);

    _question = new QLineEdit();
    _question->setFixedWidth(200);
    _layoutQuestion->addWidget(_question, 0, 1, 1, 2);

    _send = new QPushButton("Envoyer", this);
    _send->setMaximumWidth(70);
    _layoutQuestion->addWidget(_send, 1, 2);

    _tabs->addTab(_wQuestion, "Question");
    _layoutPrincipal->addWidget(_tabs, 0, 0, 1, 1);

    /* ---------- BARRE DE MENUS ---------- */
        createActions();
        createMenus();

    /* ---------- FENÊTRE ---------- */
    _window = new QWidget();
        _window->setLayout(_layoutPrincipal);
        setCentralWidget(_window);

    /* ---------- CONNEXIONS ---------- */
}

MainWindow::~MainWindow()
{}

QGroupBox *MainWindow::createFactOrRuleGroup()
{
    QVBoxLayout * _vBase = new QVBoxLayout();
    QGroupBox * _factOrRule = new QGroupBox(tr("Ajout"));
    QRadioButton * _fact = new QRadioButton(tr("Fait"));
        _fact->setChecked(true);
    QRadioButton * _rule = new QRadioButton(tr("Règle"));

    _vBase->addWidget(_fact);
    _vBase->addWidget(_rule);
    _vBase->addStretch(1);
    _factOrRule->setLayout(_vBase);

    return _factOrRule;
}

QGroupBox *MainWindow::createForwardOrBackwardGroup()
{
    QVBoxLayout * _vQuestion = new QVBoxLayout();
    QGroupBox * _forwardOrBackward = new QGroupBox(tr("Méthode"));
    QRadioButton * _forward = new QRadioButton(tr("Forward"));
        _forward->setChecked(true);
    QRadioButton * _backward = new QRadioButton(tr("Backward"));

    _vQuestion->addWidget(_forward);
    _vQuestion->addWidget(_backward);
    _vQuestion->addStretch(1);
    _forwardOrBackward->setLayout(_vQuestion);
    _forwardOrBackward->setMinimumHeight(200);

    return _forwardOrBackward;
}

void MainWindow::createActions()
{
    _save = new QAction("&Sauvegarder", this);
    _save->setShortcuts(QKeySequence::Save);
    _save->setStatusTip("Sauvegarde la scène");
    QObject::connect(_save, &QAction::triggered, this, &MainWindow::saveToFile);

    _load = new QAction("&Ouvrir", this);
    _load->setShortcuts(QKeySequence::Open);
    _load->setStatusTip("Charge une scène");
    QObject::connect(_load, &QAction::triggered, this, &MainWindow::loadFromFile);

    _exit = new QAction("&Quitter", this);
    _exit->setShortcuts(QKeySequence::Quit);
    _exit->setStatusTip("Quitte l'application");
    QObject::connect(_exit, &QAction::triggered, this, &QWidget::close);

    _aboutUs = new QAction("&Nous concernant", this);
    _aboutUs->setStatusTip("Affiche les créateurs de l'application");
    //CONNEXION A FAIRE

    _howToUse = new QAction("&Comment ça marche ?", this);
    _howToUse->setShortcuts(QKeySequence::WhatsThis);
    _howToUse->setStatusTip("Affiche un tutoriel pour utiliser l'application");
    //CONNEXION A FAIRE
}

void MainWindow::createMenus()
{
    _file = new QMenu(this);
    _file = menuBar()->addMenu("&Fichier");
    _file->addAction(_save);
    _file->addAction(_load);
    _file->addSeparator();
    _file->addAction(_exit);

    _help = new QMenu(this);
    _help = menuBar()->addMenu("&Aide");
    _help->addAction(_aboutUs);
    _help->addSeparator();
    _help->addAction(_howToUse);
}


void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Sauvegarde de la base de connaissances"), "",
        tr("Base de Connaissances (*.bdc);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        //A REVOIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIR
        //out << contacts;
    }
}

void MainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Ouverture de la base de connaissances"), "",
        tr("Base de Connaissances (*.bdc);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        // A REVOIR
        /*contacts.empty();
        in >> contacts;

        if (contacts.isEmpty())
        {
            QMessageBox::information(this, tr("Pas de faits et règles dans la base de connaissances"),
                tr("Le fichier que vous essayez d'ouvrir ne contient rien"));
        } else
        {
            QMap<QString, QString>::iterator i = contacts.begin();
            nameLine->setText(i.key());
            addressText->setText(i.value());
        }*/
    }

    //updateInterface(NavigationMode);
}
