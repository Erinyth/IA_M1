#pragma once
#include "bdc.hh"

class Moteur{
public:
    Moteur(baseDeConnaissance * baseDC): BDC(baseDC)
    {}

    /**
     * @brief regleApplicable Retourne true si il existe une règle applicable dans la base de données
     * Applicable implique que les faits sont disponibles et que la règle n'a pas déjà été utilisée
     * @param type  Peut être AV ou AR suivant le type de chainage qui l'appelle
     * @return
     */
    bool regleApplicableExistante(std::string type);

    /**
     * @brief appartientFaitBDC Retourne true si faitATest appartient déjà aux faits dans la base de données
     * @param faitATest
     * @return
     */
    bool appartientFaitBDC(Fait & faitATest);

    /**
     * @brief ajoutFaitAvecOperateur Ajout des faits en fonction des opérateurs <, <=, >=, >=
     * @param oper
     */
    void ajoutFaitAvecOperateur(std::string oper);

    /**
     * @brief chainageAvant Lance le moteur en chainage avant
     * @param faitATest
     */
    void chainageAvant(Fait & faitATest);

    /**
     * @brief chainageArriere Lance le moteur en chainage arriètre
     */
    bool chainageArriere(Fait & faitATest);

    /**
     * @brief verifierPremisses Vérifie les prémisses d'une règle
     * @param regTmp
     * @return
     */
    bool verifierPremisses(Regle & regTmp);

    /**
     * @brief testFaitAvecOperateur Vérifie si un fait menant à cette condition existe dans la BDC, et vérifiant les signes
     * <, <=, =>, >, donc en parcourant tous les cas possibles
     * @param condTMP
     * @param oper
     * @return
     */
    bool testConditionAvecOperateur(Condition & condTMP);

private:
    baseDeConnaissance * BDC;
};
