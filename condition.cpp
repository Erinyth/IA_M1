#include "condition.hh"
#include "bdc.hh"

bool Condition::estConditionApplicable(baseDeConnaissance & bdc)
{
    for (unsigned int i(0); i<bdc.getFaits().size(); i++)
    {
        if (eltTeste == bdc.getFaits()[i].getTypeFait())    //Si le type de fait est équivalent
        {
            //Ce n'est pas un integer, donc l'opérateur est soit = soit =/=
            if (!valEstChiffre && bdc.getFaits()[i].estFaitChiffre() == false)
            {
                if (operateur == "=")   //Si l'opérateur est =
                {
                    if (valeurChaine == bdc.getFaits()[i].getValFait())     //Si la valeur est égale
                        return true;
                } else if (operateur == "<>")  //Si l'opérateur est =/=
                {
                    if (valeurChaine != bdc.getFaits()[i].getValFait())     //Si la valeur est différente
                        return true;
                }
            }
            //C'est un integer, donc l'operateur peut être =, =/=, <, <=, =, >=, >
            else if (valEstChiffre && bdc.getFaits()[i].estFaitChiffre() == true)
            {
                if (operateur == "=")   //Si l'opérateur est =
                {
                    if (valeurInt == bdc.getFaits()[i].getValFaitChiffre())     //Si la valeur est égale
                        return true;
                } else if (operateur == "<>")  //Si l'opérateur est =/=
                {
                    if (valeurInt != bdc.getFaits()[i].getValFaitChiffre())     //Si la valeur est différente
                        return true;
                }
                else if (operateur == "<")  //Si l'opérateur est <
                {
                    if (bdc.getFaits()[i].getValFaitChiffre() < valeurInt)     //Si la valeur est strictement inférieure
                        return true;
                }
                else if (operateur == "<=")  //Si l'opérateur est <=
                {
                    if (bdc.getFaits()[i].getValFaitChiffre() <= valeurInt)     //Si la valeur est inférieure ou égale
                        return true;
                }
                else if (operateur == ">=")  //Si l'opérateur est >=
                {
                    if (bdc.getFaits()[i].getValFaitChiffre() >= valeurInt)     //Si la valeur est supérieure ou égale
                        return true;
                }
                else if (operateur == ">")  //Si l'opérateur est >
                {
                    if (bdc.getFaits()[i].getValFaitChiffre() > valeurInt)     //Si la valeur est strictement supérieure
                        return true;
                }
            }
        }
    }
    //Si aucun des cas précédents n'a renvoyé true, alors la règle n'est pas applicable
    return false;
}
