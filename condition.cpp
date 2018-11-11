#include "condition.hh"
#include "bdc.hh"


/**
 * @brief eclate
 * @param s
 * @param delim
 * @return
 * https://stackoverflow.com/questions/12966957/is-there-an-equivalent-in-c-of-phps-explode-function
 * Fonction eclatant une chaine par rapport à son délimiteur
 */
std::vector<std::string> eclate(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

bool Condition::verifApplicationChiffre(Fait & faitATest) const
{
    if (operateur == "=")   //Si l'opérateur est =
    {
        if (valeurInt == faitATest.getValFaitChiffre())     //Si la valeur est égale
            return true;
    } else if (operateur == "<>")  //Si l'opérateur est =/=
    {
        if (valeurInt != faitATest.getValFaitChiffre())     //Si la valeur est différente
            return true;
    }
    else if (operateur == "<")  //Si l'opérateur est <
    {
        if (faitATest.getValFaitChiffre() < valeurInt)     //Si la valeur est strictement inférieure
            return true;
    }
    else if (operateur == "<=")  //Si l'opérateur est <=
    {
        if (faitATest.getValFaitChiffre() <= valeurInt)     //Si la valeur est inférieure ou égale
            return true;
    }
    else if (operateur == ">=")  //Si l'opérateur est >=
    {
        if (faitATest.getValFaitChiffre() >= valeurInt)     //Si la valeur est supérieure ou égale
            return true;
    }
    else if (operateur == ">")  //Si l'opérateur est >
    {
        if (faitATest.getValFaitChiffre() > valeurInt)     //Si la valeur est strictement supérieure
            return true;
    }
    return false;
}

bool Condition::estConditionApplicable(baseDeConnaissance * bdc) const
{
    for (unsigned int i(0); i<bdc->getFaits().size(); i++)
    {
        Fait faitEnCours = bdc->getFaits()[i];

        /*
         * Deux types de fait possibles:
         *  - Les faits classique: element = valeur
         *  - Les faits à operateur: element*operateur = valeur, par exemple age:infs = 30
         */

        std::vector<std::string> faitExplode = eclate(faitEnCours.getTypeFait(), '*');

        if (faitExplode.size() == 1) // Fait classique, sans * donc sans opérateur
        {
            if (eltTeste == faitEnCours.getTypeFait())    //Si le type de fait est équivalent
            {
                //Ce n'est pas un integer, donc l'opérateur est soit = soit =/=
                if (!valEstChiffre && faitEnCours.estFaitChiffre() == false)
                {
                    if (operateur == "=")   //Si l'opérateur est =
                    {
                        if (valeurChaine == faitEnCours.getValFait())     //Si la valeur est égale
                            return true;
                    } else if (operateur == "<>")  //Si l'opérateur est =/=
                    {
                        if (valeurChaine != faitEnCours.getValFait())     //Si la valeur est différente
                            return true;
                    }
                }
                //C'est un integer, donc l'operateur peut être =, =/=, <, <=, =, >=, >
                else if (valEstChiffre && faitEnCours.estFaitChiffre() == true)
                {
                    return verifApplicationChiffre(faitEnCours);
                }
            }
        }
        else    //L'explode une taille de 2, donc il y a un opérateur. De plus, c'est forcément un fait chiffré
        {
            std::string operateurFait = faitExplode[1];
            std::string eltFaitOperateur = faitExplode[0];
            if (eltTeste == eltFaitOperateur)
            {
                if (faitEnCours.getValFaitChiffre() < valeurInt)
                {
                    //C'est inderterminé pour operateur = > et >=
                    if (operateur == "<" || operateur == "<=")
                    {
                        //Cas operateurFait > et >= : On ne peut rien déterminer
                        if (operateurFait == "<" || operateurFait == "<=")
                            return true;
                    }
                }
                if (faitEnCours.getValFaitChiffre() == valeurInt)
                {
                    if (operateur == operateurFait )
                        return true;
                }
                if (faitEnCours.getValFaitChiffre() > valeurInt)
                {
                    //Ce n'est pas possible pour operateur = < et <=
                    if (operateur == ">" || operateur == ">=")
                    {
                        //Cas operateurFait > et >= : On ne peut rien déterminer
                        if (operateurFait == ">" || operateurFait == ">=")
                            return true;
                    }
                }
            }
        }
    }
    //Si aucun des cas précédents n'a renvoyé true, alors la règle n'est pas applicable
    return false;
}


bool Condition::estResultatAutreRegle(baseDeConnaissance * BDC) const
{
    for (unsigned int i(0); i<BDC->getRegles().size(); i++) //Parcours de toutes les règles
    {
        for (unsigned int j(0); j<BDC->getRegles()[i].getResRegle().size(); j++)    //Parcours des résultats d'une règle
        {
            Resultat resultatEnCours = BDC->getRegles()[i].getResRegle()[j];
            if (this->getEltTest() == resultatEnCours.getElement())    //Si même élément
            {
                if (this->getOperateur() == resultatEnCours.getOperateur())    //Si même opérateur
                {
                    if (this->getValeurChaine() == resultatEnCours.getValeur())    //Si même valeur
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


