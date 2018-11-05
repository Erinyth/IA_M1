#include <iostream>
#include "lecture.hh"
#include "bdc.hh"
#include "moteur.hh"

using namespace std;

int main()
{
    baseDeConnaissance BDC;

    // std::cout<< "DEBUG: Lecture" << std::endl;
    //PC FAC
    char * fichierBC = "/home/etudiant/Bureau/Cours/IA/IA_M1/baseDeConnaissance.txt";
    //PC MAISON
    //char * fichierBC = "/home/prozengan/Bureau/IA_M1/baseDeConnaissance.txt";
    creationBaseConnaissance(fichierBC, BDC);

    /* AFFICHAGE POUR VERIFIER LA LECTURE CONFORME
    std::cout << "***************************** AFFICHAGE DE TOUS LES FAITS INITIAUX *****************************" << std::endl;
    BDC.affichageEnsembleFaits();
    std::cout << std::endl;

    std::cout << "***************************** AFFICHAGE DE TOUTES LES REGLES INITIALES *****************************" << std::endl;
    BDC.affichageEnsembleRegles();
    std::cout << std::endl;
    */

    std::cout << "***************************** TESTS *****************************" << std::endl;

    Fait test("michel","bizarre",false);
    Moteur m1(&BDC);
    //m1.chainageAvant(test);
    bool chainAr = m1.chainageArriere(test);
    if (chainAr)
    {
        std::cout << "Le chainage arrière pour ";
        test.affichageFait();
        std::cout << " est un succès!" << std::endl;
    }
    else
    {
        std::cout << "Le chainage arrière pour ";
        test.affichageFait();
        std::cout << " est un échec!" << std::endl;
    }

    // std::cout << "***************************** AFFICHAGE DE TOUS LES FAITS FINAUX *****************************" << std::endl;
    // BDC.affichageEnsembleFaits();
    std::cout << std::endl;


    return 0;
}

