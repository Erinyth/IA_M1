#include "regle.hh"

bool Regle::estRegleApplicable(baseDeConnaissance * BDC) const
{
    unsigned int nbConditionsApplicables(0);
    for (unsigned int i(0); i<vecConditions.size(); i++)
    {
        if (vecConditions[i].estConditionApplicable(BDC))
            nbConditionsApplicables++;
    }

    if (nbConditionsApplicables == vecConditions.size())
        return true;
    else
        return false;
}

bool Regle::donneResultat(Fait & faitATest) const
{
    for (unsigned int i(0); i<vecResultatRegle.size();i++)
    {
        if (faitATest.getTypeFait() == vecResultatRegle[i].getElement())
            if (faitATest.getValFait() == vecResultatRegle[i].getValeur())
                return true;
    }
    return false;
}

void Regle::affichageRegle()
{
    std::cout << "Condition(s) de la règle:" << std::endl;
    for (unsigned int i(0); i<vecConditions.size(); i++)
    {
        vecConditions[i].affichageCondition();
        std::cout << ",";
    }
    std::cout << std::endl;
    std::cout << "Resultat(s) de la règle:" << std::endl;
    for (unsigned int i(0); i<vecResultatRegle.size(); i++)
    {
        vecResultatRegle[i].affichageResultat();
        std::cout << ",";
    }
    std::cout << std::endl;
}

std::string Regle::InformationRegle()
{
    std::string InfoRegle = "";
    InfoRegle = InfoRegle + "Si ";
    for (unsigned int i(0); i<vecConditions.size(); i++)
    {
        InfoRegle = InfoRegle + vecConditions[i].InformationCondition();
        InfoRegle = InfoRegle + ",";
    }
    InfoRegle = InfoRegle + " alors ";
    for (unsigned int i(0); i<vecResultatRegle.size(); i++)
    {
       InfoRegle = InfoRegle + vecResultatRegle[i].InformationResultat();
       InfoRegle = InfoRegle + ",";
    }
    return InfoRegle;
}
