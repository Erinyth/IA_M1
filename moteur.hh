#pragma once
#include "bdc.hh"

class Moteur{
public:
    Moteur(baseDeConnaissance baseDC): BDC(baseDC)
    {}

    /**
     * @brief regleApplicable Retourne true si une règle est applicable dans la base de données
     * @return
     */
    bool regleApplicable();

    /**
     * @brief appartientFaitBDC Retourne true si faitATest appartient déjà aux faits dans la base de données
     * @param faitATest
     * @return
     */
    bool appartientFaitBDC(Fait faitATest);

    /**
     * @brief chainageAvant Lance le moteur en chainage avant
     * @param faitATest
     */
    void chainageAvant(Fait faitATest);

    /**
     * @brief chainageArriere Lance le moteur en chainage arriètre
     */
    void chainageArriere();

private:
    baseDeConnaissance BDC;
};
