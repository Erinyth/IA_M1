#pragma once
#include <string>


class Resultat{
public:
    Resultat(std::string elt, std::string val, std::string ope, bool estC): element(elt), valeur(val), operateur(ope), estValeurChiffree(estC)
    {
        if (estValeurChiffree)
        {
            valeurChiffre = std::stoi(valeur);
        }
    }

    std::string getElement()
    { return element; }

    std::string getValeur()
    { return valeur; }

    std::string getOperateur()
    { return operateur; }

    bool estResultatChiffre()
    { return estValeurChiffree; }

    int valeurResultatChiffre()
    { return valeurChiffre; }

    void affichageResultat()
    {
        std::cout << element  << " = " << valeur << std::endl;
    }


private:
    std::string element;
    std::string valeur;
    std::string operateur;

    bool estValeurChiffree;
    int valeurChiffre;
};
