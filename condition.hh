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

    std::string getEltTest()
    { return eltTeste; }

    std::string getValeurChaine()
    {  return valeurChaine; }

    std::string getOperateur()
    { return operateur; }

    bool estValChiffre()
    { return valEstChiffre; }

    int getValeurChiffre()
    { return valeurInt; }

    void affichageCondition()
    {
        std::cout << eltTeste << " " << operateur << " " << valeurChaine << std::endl;
        std::cout << "Test: " << valeurInt + 50 << std::endl;
    }

    bool estConditionApplicable(baseDeConnaissance & bdc);

private:
    std::string eltTeste;
    std::string valeurChaine;
    std::string operateur;

    bool valEstChiffre;
    int valeurInt;
};
