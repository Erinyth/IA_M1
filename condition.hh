#pragma once
#include <string>
#include <vector>
#include <iostream>

class baseDeConnaissance;

class Condition{
public:
    Condition(std::string eltTest, std::string valeur, std::string op, bool chiffre): eltTeste(eltTest), valeurChaine(valeur), operateur(op), valEstChiffre(chiffre)
    {
        if (valEstChiffre)
        {
            valeurInt = std::stoi(valeurChaine);
        }
    }

    std::string getEltTest() const
    { return eltTeste; }

    std::string getValeurChaine() const
    {  return valeurChaine; }

    std::string getOperateur() const
    { return operateur; }

    bool estValChiffre() const
    { return valEstChiffre; }

    int getValeurChiffre() const
    { return valeurInt; }

    void affichageCondition() const
    {
        std::cout << eltTeste << " " << operateur << " " << valeurChaine;
    }

    /**
     * @brief estConditionApplicable Retourne true si une condition est applicable
     * @param bdc
     * @return
     */
    bool estConditionApplicable(baseDeConnaissance * bdc) const;

    /**
     * @brief estResultatAutreRegle Retourne true si cette condition est le résultat d'une règle
     * @param BDC
     * @return
     */
    bool estResultatAutreRegle(baseDeConnaissance * BDC) const;

private:
    std::string eltTeste;
    std::string valeurChaine;
    std::string operateur;

    bool valEstChiffre;
    int valeurInt;
};
