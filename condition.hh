#pragma once
#include <string>
#include <vector>
#include <iostream>

class baseDeConnaissance;
class Fait;

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

    std::string InformationCondition() const
    {
        std::string InfoCondition = "";
        InfoCondition = InfoCondition + eltTeste + " " + operateur + " " + valeurChaine;
        return InfoCondition;
    }

    bool const operator==(Condition const& b)
    {
        if ((this->eltTeste == b.getEltTest()) && (this->valeurChaine == b.getValeurChaine()) && (this->operateur == b.getOperateur()) && (this->valeurInt == b.getValeurChiffre()))
            return true;
        else
            return false;
    }

    /**
     * @brief estConditionApplicable Retourne true si une condition est applicable
     * @param bdc
     * @return
     */
    bool estConditionApplicable(baseDeConnaissance * bdc) const;

    /**
     * @brief verifApplicationChiffre Appelé depuis estConditionApplicable
     * Va faire les vérifications lorsque le fait est un chiffre
     * @param faitATest
     * @return
     */
    bool verifApplicationChiffre(Fait & faitATest) const;

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
