#pragma once

#include "condition.hh"
#include "resultat.hh"
#include "fait.hh"
#include <iostream>

class Regle{
public:
    Regle(): vecConditions(), vecResultatRegle(), chainageAvantEffectue(false), chainageArriereEffectue(false)
    {}

    /*
     *  Getters
     */
    std::vector<Condition>& getConditions()
    { return vecConditions; }

    std::vector<Resultat>& getResRegle()
    { return vecResultatRegle; }

    bool chainageAvantEstFait() const
    { return chainageAvantEffectue; }

    bool chainageArriereEstFait() const
    { return chainageArriereEffectue; }

    /*
     *  Setters
     */
    void ajoutResultat(Resultat res)
    { vecResultatRegle.push_back(res); }

    void ajoutCondition(Condition cond)
    { vecConditions.push_back(cond); }

    void chainageAvantComplete()
    { chainageAvantEffectue = true; }

    void chainageArriereComplete()
    { chainageArriereEffectue = true; }

    /*
     *  Methodes
     */
    /**
     * @brief estRegleApplicable retourne vrai si la règle est appliquable avec la BDC actuelle
     * @param BDC
     * @return */
    bool estRegleApplicable(baseDeConnaissance * BDC) const;

    /**
     * @brief donneResultat retourne vrai si l'élément est un résultat de cette règle
     * @param BDC
     * @return
     */
    bool donneResultat(Fait & faitATest) const;

    /** @brief affichageRegle affiche toutes les informations concernant une règle */
    void affichageRegle();

    /**
     * @brief InformationRegle Renvoie une string des informations concernant la règle
     * @return
     */
    std::string InformationRegle();

private:
    std::vector<Condition> vecConditions;
    std::vector<Resultat> vecResultatRegle;

    bool chainageAvantEffectue;
    bool chainageArriereEffectue;
};
