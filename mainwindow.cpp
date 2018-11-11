#include "mainwindow.h"
#include "iostream"
#include <sstream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    moteur = new Moteur(&BDC);

    this->setFixedSize(400, 210);
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
    _layoutQuestion->addWidget(createFirstOrHigherGroup(), 0, 2, 1, 2);

    _question = new QLineEdit();
    _question->setFixedWidth(200);
    _layoutQuestion->addWidget(_question, 1, 0, 1, 2);

    _show2 = new QPushButton("Afficher", this);
    _show2->setMaximumWidth(70);
    _layoutQuestion->addWidget(_show2, 1, 2);
    _send = new QPushButton("Envoyer", this);
    _send->setMaximumWidth(70);
    _layoutQuestion->addWidget(_send, 1, 3);

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
    QObject::connect(_add, &QPushButton::clicked, this, &MainWindow::Add);
    QObject::connect(_send, &QPushButton::clicked, this, &MainWindow::Test);
    QObject::connect(_show, &QPushButton::clicked, this, &MainWindow::Affichage);
    QObject::connect(_show2, &QPushButton::clicked, this, &MainWindow::Affichage2);
}

MainWindow::~MainWindow()
{}

QGroupBox *MainWindow::createFactOrRuleGroup()
{
    _vBase = new QVBoxLayout();
    _factOrRule = new QGroupBox(tr("Ajout"));
    _fact = new QRadioButton(tr("Fait"));
    _fact->setChecked(true);
    _rule = new QRadioButton(tr("Règle"));

    _vBase->addWidget(_fact);
    _vBase->addWidget(_rule);
    _vBase->addStretch(1);
    _factOrRule->setLayout(_vBase);

    return _factOrRule;
}

QGroupBox *MainWindow::createForwardOrBackwardGroup()
{
    _vQuestionfb = new QVBoxLayout();
    _forwardOrBackward = new QGroupBox(tr("Méthode"));
    _forward = new QRadioButton(tr("Forward"));
    _forward->setChecked(true);
    _backward = new QRadioButton(tr("Backward"));

    _vQuestionfb->addWidget(_forward);
    _vQuestionfb->addWidget(_backward);
    _vQuestionfb->addStretch(1);
    _forwardOrBackward->setLayout(_vQuestionfb);
    _forwardOrBackward->setMinimumHeight(200);

    return _forwardOrBackward;
}

QGroupBox *MainWindow::createFirstOrHigherGroup()
{
    _vQuestionfh = new QVBoxLayout();
    _firstOrHigher = new QGroupBox(tr("Critère"));
    _first = new QRadioButton(tr("Première"));
    _first->setChecked(true);
    _higher = new QRadioButton(tr("Nb prémisses"));

    _vQuestionfh->addWidget(_first);
    _vQuestionfh->addWidget(_higher);
    _vQuestionfh->addStretch(1);
    _firstOrHigher->setLayout(_vQuestionfh);
    _firstOrHigher->setMinimumHeight(200);

    return _firstOrHigher;
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
    QObject::connect(_aboutUs, &QAction::triggered, this, &MainWindow::infoCrea);

    _howToUse = new QAction("&Comment ça marche ?", this);
    _howToUse->setShortcuts(QKeySequence::WhatsThis);
    _howToUse->setStatusTip("Affiche un tutoriel pour utiliser l'application");
    QObject::connect(_howToUse, &QAction::triggered, this, &MainWindow::infoTuto);
}

void MainWindow::createMenus()
{
    _file = new QMenu(this);
    _file = menuBar()->addMenu("Fichier");
    _file->addAction(_save);
    _file->addAction(_load);
    _file->addSeparator();
    _file->addAction(_exit);

    _help = new QMenu(this);
    _help = menuBar()->addMenu("Aide");
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

        QString donneesSauvegarde = QString::fromStdString(BDC.sauvegardeBDC());

        if ( file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &file );
            stream << donneesSauvegarde << endl;
        }
    }
}

void MainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Ouverture de la base de connaissances"), "",
                                                    tr("Base de Connaissances (*.bdc);;All Files (*)"));

    if (fileName.isEmpty())
    {
        QMessageBox::StandardButton info;
        info = QMessageBox::information(this, "Informations", "Echec du chargement");
    }
    else
    {
        std::string nomFichierEntree = fileName.toStdString();
        const char * nomFichierChar = nomFichierEntree.c_str();
        BDC.creationBaseConnaissance(nomFichierChar);

        //POPUP OK
        QMessageBox::StandardButton info;
        info = QMessageBox::information(this, "Informations", "Fichier chargé avec succès");
    }
}


void MainWindow::infoCrea()
{
    QMessageBox::StandardButton info;
    info = QMessageBox::information(this, "Nous concernant", "Programme créé par MOHR Anaïs et PIGACHE Bastien\n"
                                                             "sous la direction de Madame AMGHAR Tassadit dans le "
                                                             "cadre du projet d'intelligence artificielle de Master 1 informatique.");
}

void MainWindow::infoTuto()
{
    QMessageBox::StandardButton info;
    info = QMessageBox::information(this, "Informations", "  *** Onglet base ***\n\n"
                                                          "Dans l'onglet base, nous pouvons choisir d'ajouter des faits ou des règles (cela dépend de la position du bouton) dans notre base de connaissances, "
                                                          "nous supposons que le syntaxe sera toujours respectée. Pour information, la voici : \n\n"
                                                          "Pour les faits : variable:%entier ou variable:chaine de caractère ou variable:bool \n"
                                                          "Pour les règles : variable = string,variable = bool,variable < %entier / variable = string\n"
                                                          "L'opérateur peut bien évidemment être changé tant que cela reste cohérent. De la même façon, nous pouvons ajuster le nombre de prémisses et de résultats.\n"
                                                          "Un fichier d'exemple est disponible à la base du logiciel. Il se nomme baseDeConnaissance.bdc\n\n"
                                                          "Une fois votre fait ou votre règle entrée dans le champ de saisie, appuyez sur le bouton Ajouter afin que l'action soit effectuée. "
                                                          "Si vous souhaitez voir l'état actuel de la base de connaissances, vous pouvez cliquer sur le bouton Afficher.\n"
                                                          "\n"
                                                          "  *** Onglet question ***\n\n"
                                                          "Vous pouvez choisir d'interroger la base de connaissances de plusieurs façons : soit par chaînage avant, soit par "
                                                          "chaînage arrière en sélectionnant celui que vous voulez grâce à la position du bouton.\n"
                                                          "Une fois la méthode déterminée, vous pouvez entrer votre question dans le champ de saisie et cliquer sur le bouton Envoyer. "
                                                          "Celui-ci fera apparaître un PopUp montrant l'état de la base de connaissances après les différents traitements et si, oui ou non, "
                                                          "la requête a une solution.\n"
                                                          "\n"
                                                          "  *** Sauvegarde et chargement ***\n\n"
                                                          "Vous pouvez à tout moment sauvegarder votre base de connaissances en cliquant dans le menu ou avec le raccourci "
                                                          "Ctrl+S. De même, vous pouvez à tout moment charger une base de connaissances en cliquant dans le menu ou avec "
                                                          "le raccourci Ctrl+O.\n");
}


void MainWindow::Add()
{
    std::string factOrRule = _text->text().toStdString();

    //Si fait est coché
    if (_fact->isChecked())
    {
        bool valide = BDC.ajouterFaitDepuisTexte(factOrRule);
        if (valide)
        {
            BDC.setNbFaits(BDC.getNbFaits() + 1);
            QMessageBox::StandardButton info;
            info = QMessageBox::information(this, "Informations", "Fait ajouté à la base de connaissance");
        }
        else
        {
            QMessageBox::StandardButton info;
            info = QMessageBox::information(this, "Informations", "Fait non ajouté à la base de connaissance pour des raisons de cohérence");
        }
    }
    //Si règle est coché
    else if (_rule->isChecked())
    {
        bool valide = BDC.ajouterRegleDepuisTexte(factOrRule);
        if (valide)
        {
            BDC.setNbRegles(BDC.getNbRegles() + 1);
            QMessageBox::StandardButton info;
            info = QMessageBox::information(this, "Informations", "Règle ajoutée à la base de connaissance");
        }
        else
        {
            QMessageBox::StandardButton info;
            info = QMessageBox::information(this, "Informations", "Règle non ajoutée à la base de connaissance pour des raisons de cohérence");
                }
    }
    _text->setText("");
}

void MainWindow::Affichage()
{
    QString InformationsBDC = QString::fromStdString(BDC.InformationsCompleteBDC());

    QMessageBox::StandardButton info;
    info = QMessageBox::information(this, "Base de connaissances", InformationsBDC);
}

void MainWindow::Test()
{
    moteur->resetInfoDeroulement();
    std::string forwardOrBackward = _question->text().toStdString();
    bool resultatRecherche;

    //Si forward est coché
    if (_forward->isChecked())
    {
        if (_first->isChecked()) //Critère de la première règle applicable
            resultatRecherche = moteur->lancementRecherche(forwardOrBackward,"AV", "premier");
        if (_higher->isChecked()) //Critère du plus grand nombre de prémisses
            resultatRecherche = moteur->lancementRecherche(forwardOrBackward,"AV", "nombrePremisse");
        if (resultatRecherche)
        {
            QMessageBox::StandardButton info;
            info = QMessageBox::information(this, "Informations", "Fait recherché trouvé en chaînage avant");
        }
        else
        {
            QMessageBox::StandardButton info;
            info = QMessageBox::information(this, "Informations", "Fait recherché non trouvé en chaînage avant");
        }
    }
    //Si backward est coché
    else //if (_backward->isChecked())
    {
        if (_first->isChecked()) //Critère de la première règle applicable
            resultatRecherche = moteur->lancementRecherche(forwardOrBackward,"AR", "premier");
        if (_higher->isChecked()) //Critère du plus grand nombre de prémisses
            resultatRecherche = moteur->lancementRecherche(forwardOrBackward,"AR", "nombrePremisse");
        if (resultatRecherche)
        {
            QMessageBox::StandardButton info;
            info = QMessageBox::information(this, "Informations", "Fait recherché trouvé en chaînage arrière");
        }
        else
        {
            QMessageBox::StandardButton info;
            info = QMessageBox::information(this, "Informations", "Fait recherché non trouvé en chaînage arrière");
        }
    }
    _question->setText("");
}

void MainWindow::Affichage2()
{
    QString InformationsDeroulement = QString::fromStdString(moteur->getInfoDeroulement());

    QMessageBox::StandardButton info;
    info = QMessageBox::information(this, "Base de connaissances", InformationsDeroulement);
}
