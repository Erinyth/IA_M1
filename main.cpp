#include <iostream>
#include "lecture.hh"
#include "bdc.hh"
#include "moteur.hh"

using namespace std;

int main()
{
    baseDeConnaissance BDC;


    cout<< "Lecture" << endl;
    //PC FAC
    char * fichierBC = "/home/etudiant/Bureau/Cours/IA/Projet/ProjetIASysExp/baseDeConnaissance.txt";
    //PC MAISON
    //char * fichierBC = "/home/prozengan/ProjetIASysExp/baseDeConnaissance.txt";
    creationBaseConnaissance(fichierBC, BDC);

    std::cout << "***************************** AFFICHAGE DE TOUS LES FAITS INITIAUX *****************************" << std::endl;
    BDC.affichageEnsembleFaits();
    std::cout << std::endl;

    std::cout << "***************************** AFFICHAGE DE TOUTES LES REGLES INITIALES *****************************" << std::endl;
    BDC.affichageEnsembleRegles();
    std::cout << std::endl;

    std::cout << "***************************** TESTS *****************************" << std::endl;


    Fait test("nom","jean",false);
    Moteur m1(BDC);
    m1.chainageAvant(test);

    std::cout << "***************************** AFFICHAGE DE TOUS LES FAITS FINAUX *****************************" << std::endl;
    //BDC.affichageEnsembleFaits();
    std::cout << std::endl;


    return 0;
}

