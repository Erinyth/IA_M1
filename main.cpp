#include <iostream>
#include "lecture.hh"
#include "bdc.hh"

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

    std::cout << "***************************** AFFICHAGE DE TOUS LES FAITS *****************************" << std::endl;
    BDC.affichageEnsembleFaits();
    std::cout << std::endl;

    std::cout << "***************************** AFFICHAGE DE TOUTES LES REGLES *****************************" << std::endl;
    BDC.affichageEnsembleRegles();
    std::cout << std::endl;

    std::cout << "***************************** TESTS *****************************" << std::endl;




    return 0;
}

