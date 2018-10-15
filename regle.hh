#pragma once

#include "condition.hh"
#include "resultat.hh"
#include <iostream>

class Regle{
public:
    Regle(): vecConditions(), vecResultatRegle()
    {}

    /**
     * @brief affichageRegle affiche toutes les informations concernant une règle
     */
    void affichageRegle()
    {
        std::cout << "Condition(s) de la règle:" << std::endl;
        for (unsigned int i(0); i<vecConditions.size(); i++)
        {
            vecConditions[i].affichageCondition();
        }
        std::cout << std::endl;
        std::cout << "Resultat(s) de la règle:" << std::endl;
        for (unsigned int i(0); i<vecResultatRegle.size(); i++)
        {
            vecResultatRegle[i].affichageResultat();
        }
        std::cout << std::endl;
    }

    /*
     *  Getters
     */
    Condition getConditionsIndice(int indice)
    {
        return vecConditions[indice];
    }

    Resultat getResRegleIndice(int indice){
        return vecResultatRegle[indice];
    }


    /*
     *  Setters
     */
    void ajoutResultat(Resultat res)
    {
        vecResultatRegle.push_back(res);
    }


    void ajoutCondition(Condition cond)
    {
        vecConditions.push_back(cond);
    }

private:
    std::vector<Condition> vecConditions;
    std::vector<Resultat> vecResultatRegle;
};
