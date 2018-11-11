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

    std::string getElement() const
    { return element; }

    std::string getValeur() const
    { return valeur; }

    std::string getOperateur() const
    { return operateur; }

    bool estResultatChiffre() const
    { return estValeurChiffree; }

    int valeurResultatChiffre() const
    { return valeurChiffre; }

    void affichageResultat()
    {
        std::cout << element << " " << operateur << " " << valeur << std::endl;
    }

    std::string InformationResultat()
    {
        std::string InfoResultat = "";
        InfoResultat = InfoResultat + element + " " + operateur + " " + valeur + "\n";
        return InfoResultat;
    }

private:
    std::string element;
    std::string valeur;
    std::string operateur;

    bool estValeurChiffree;
    int valeurChiffre;
};
