#include "moteur.hh"


bool Moteur::appartientFaitBDC(Fait faitATest)
{
    for (unsigned int i(0); i<BDC.getFaits().size(); i++)
    {
        std::cout << "Fait à test: " ;
        faitATest.affichageFait();
        std::cout << "Fait de la base comparé: ";
        BDC.getFaits()[i].affichageFait();
        if (faitATest == BDC.getFaits()[i])
        {
            std::cout << "** Acceptée **" << std::endl;
            return true;
        }
    }
    std::cout << "** Non acceptée **" << std::endl;
    return false;
}

bool Moteur::regleApplicable()
{
    for (unsigned int i(0); i<BDC.getRegles().size(); i++)  //Parcours des règles
    {
        if (!BDC.getRegles()[i].estRegleApplicable(BDC))
            return false;
    }
    return true;
}

void Moteur::chainageAvant(Fait faitATest)
{
    //TEST APPLICABILITE
    /*
    for (unsigned int i(0); i<BDC.getRegles().size(); i++)  //Parcours des règles
    {
        if (BDC.getRegles()[i].estRegleApplicable(BDC))
        {
            std::cout << "REGLE " << i+1 << " APPLICABLE!" << std::endl;
        }

        if (!BDC.getRegles()[i].estRegleApplicable(BDC))
        {
            std::cout << "REGLE " << i+1 << " NON APPLICABLE!" << std::endl;
        }
    }
    */

    //TANT QUE F n'est pas dans  BF ET QU'il existe dans BR une règle applicable FAIRE
    while(!appartientFaitBDC(faitATest) && regleApplicable())
    {
        std::cout << "Coucou de test" << std::endl;
        // choisir une règle applicable  R (étape de résolution de conflits, utilisation d'heuristiques, de métarègles)
        //Conflit: On applique la première règle applicable
        for (unsigned int i(0); i<BDC.getRegles().size();i++)   //Parcours des règles
        {
            if (BDC.getRegles()[i].estRegleApplicable(BDC))
            {
                // BF = BF union concl(R) (déclenchement de la règle R, sa conclusion est rajoutée à la base de faits)
                for (unsigned int j(0); j<BDC.getRegles()[i].getResRegle().size();j++)
                {
                    if (BDC.getRegles()[i].getResRegle()[j].estResultatChiffre())   //Si le résultat de la règle est une valeur chiffrée
                    {
                        Fait faitTmp(BDC.getRegles()[i].getResRegle()[j].getElement(), BDC.getRegles()[i].getResRegle()[j].getValeur(), BDC.getRegles()[i].getResRegle()[j].estResultatChiffre());
                        BDC.ajoutFait(faitTmp);
                    }
                    std::cout << "Fait ajouté" << std::endl;
                }
                std::cout << "Règle " << i << " à supprimer." << std::endl;
                // BR = BR - R  (désactivation de R)
                BDC.getRegles().erase(BDC.getRegles().begin()+i);
                std::cout << "Règle " << i << " supprimée." << std::endl;
            }
        }
    }
    std::cout << "***** CHAINAGE AVANT TERMINE *****" << std::endl;
    if (appartientFaitBDC(faitATest))
    {
        std::cout << "Le fait suivant: " << std::endl;
        faitATest.affichageFait();
        std::cout << "a été obtenu. C'est un succès!" << std::endl;
    }
    else
    {
        std::cout << "Le fait suivant: " << std::endl;
        faitATest.affichageFait();
        std::cout << "n'a pas été obtenu. C'est un échec!" << std::endl;
    }


}

void chainageArriere()
{

}

