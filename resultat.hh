#pragma once
#include <string>


class Resultat{
public:
    Resultat(std::string elt, std::string val): element(elt), valeur(val)
    {}

    std::string getElement()
    { return element; }

    std::string getValeur()
    { return valeur; }

    void affichageResultat()
    {
        std::cout << element  << " = " << valeur << std::endl;
    }


private:
    std::string element;
    std::string valeur;
};
