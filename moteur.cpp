#include "moteur.hh"
#include <sstream>

bool Moteur::appartientFaitBDC(Fait & faitATest)
{
    for (unsigned int i(0); i<BDC->getFaits().size(); i++)
    {
        if (faitATest == BDC->getFaits()[i])
        {
            return true;
        }
    }
    return false;
}

bool Moteur::regleApplicableExistante(std::string type)
{
    for (unsigned int i(0); i<BDC->getRegles().size(); i++)  //Parcours des règles
    {
        std::cout << "DEBUG: Regle " << i << ": ";
        if (type == "AV")
        {
            if (BDC->getRegles()[i].chainageAvantEstFait() == false)
            {
                std::cout << "Chainage avant NON FAIT ";
                if (BDC->getRegles()[i].estRegleApplicable(BDC))
                {
                    std::cout << "et regle APPLICABLE" << std::endl;;
                    return true;
                }
                std::cout << "mais NON APPLICABLE" << std::endl;
            }
            else
                std::cout << "Chainage avant DEJA effectué" << std::endl;
        }
        else
            if (type == "AR")
            {
                if (BDC->getRegles()[i].chainageArriereEstFait() == false)
                    if (BDC->getRegles()[i].estRegleApplicable(BDC))
                        return true;
            }
    }
    return false;
}

void Moteur::chainageAvant(Fait & faitATest)
{
    std::cout << "***** DEMARRAGE CHAINAGE AVANT *****" << std::endl;
    //TANT QUE F n'est pas dans  BF ET QU'il existe dans BR une règle applicable FAIRE
    while(!appartientFaitBDC(faitATest) && regleApplicableExistante("AV"))
    {
        //Choisir une règle applicable  R (étape de résolution de conflits, utilisation d'heuristiques, de métarègles)
        //Conflit: On applique la première règle applicable
        for (unsigned int i(0); i<BDC->getRegles().size();i++)   //Parcours des règles
        {
            if (!BDC->getRegles()[i].chainageAvantEstFait() && BDC->getRegles()[i].estRegleApplicable(BDC))
            {
                // BF = BF union concl(R) (déclenchement de la règle R, sa conclusion est rajoutée à la base de faits)
                for (unsigned int j(0); j<BDC->getRegles()[i].getResRegle().size();j++)
                {
                    Fait faitTmp(BDC->getRegles()[i].getResRegle()[j].getElement(), BDC->getRegles()[i].getResRegle()[j].getValeur(), BDC->getRegles()[i].getResRegle()[j].estResultatChiffre());
                    BDC->ajoutFait(faitTmp);
                    std::cout << "DEBUG: Fait ajouté: ";
                    faitTmp.affichageFait();
                }

                // BR = BR - R  (désactivation de R)
                BDC->getRegles()[i].chainageAvantComplete(); //On indique que cette règle a maintenant été utilisée par le chainage avant

                //Arret de la boucle for
                break;
            }
        }
    }
    if (appartientFaitBDC(faitATest))
    {
        std::cout << "Le fait suivant: ";
        faitATest.affichageFait();
        std::cout << "a été obtenu. C'est un succès!" << std::endl;
    }
    else
    {
        std::cout << "Le fait suivant: ";
        faitATest.affichageFait();
        std::cout << "n'a pas été obtenu. C'est un échec!" << std::endl;
    }
    std::cout << "***** CHAINAGE AVANT TERMINE *****" << std::endl;
}

bool Moteur::verifierPremisses(Regle & regTmp)
{
    bool valide = true;
    bool OK = true;
    //On vérifier les prémisses de cette règle, un à un
    for (unsigned int j(0); j<regTmp.getConditions().size();j++)
    {
        //
        std::cout << "DEBUG VERIF PREMISSE: ";
        regTmp.getConditions()[j].affichageCondition();
        std::cout << std::endl;
        //
        //Si la condition n'est ni connue dans la BDC ni un résultat de règle
        if (!regTmp.getConditions()[j].estResultatAutreRegle(BDC) && !regTmp.getConditions()[j].estConditionApplicable(BDC))
        {
            //
            std::cout << "DEBUG: La condition:";
            regTmp.getConditions()[j].affichageCondition();
            std::cout << "ne peut être obtenue." << std::endl;
            //
            OK = false;
            valide = false;
            break;
        }
    }
    if (OK) //Toutes les conditions sont des résultats de règle, ou alors sont applicables via la BDC
        //On va donc vérifier que ces conditions sont elles même réalisables
    {
        std::cout << "DEBUG: Toutes les prémisses pour cette fois sont réalisables." << std::endl;
        for (unsigned int i(0); i<regTmp.getConditions().size();i++) //Parcours des conditions
        {
            if (regTmp.getConditions()[i].getOperateur() == "=") //Cas du =
            {
                //Dans ce cas, on doit juste vérifier que le fait fonctionne pour cette valeur
                Fait faitTmp(regTmp.getConditions()[i].getEltTest(),regTmp.getConditions()[i].getValeurChaine(),regTmp.getConditions()[i].estValChiffre());
                //
                //std::cout << "CAS DU =" << std::endl;
                //std::cout << "DEBUG: Lancement chainage arrière de: ";
                //faitTmp.affichageFait();
                //std::cout << std::endl;
                //
                valide = valide && chainageArriere(faitTmp);
            }
            if (regTmp.getConditions()[i].getOperateur() == "<>") //Cas du =
            {
                //Dans ce cas, on doit juste vérifier que le fait fonctionne pour cette valeur
                Fait faitTmp(regTmp.getConditions()[i].getEltTest(),regTmp.getConditions()[i].getValeurChaine(),regTmp.getConditions()[i].estValChiffre());
                //
                //std::cout << "CAS DU =" << std::endl;
                //std::cout << "DEBUG: Lancement chainage arrière de: ";
                //faitTmp.affichageFait();
                //std::cout << std::endl;
                //
                valide = valide && !chainageArriere(faitTmp);
            }
            //On doit trouver ici un fait qui valide
            if (regTmp.getConditions()[i].getOperateur() == "<")
            {
                std::cout << "CAS DU <" << std::endl;
                for (unsigned int j(0); j<regTmp.getConditions()[i].getValeurChiffre();j++) //Parcours des conditions
                {
                    std::stringstream ss;
                    ss << j;
                    std::string str = ss.str();
                    Fait faitTmp(regTmp.getConditions()[i].getEltTest(),str,regTmp.getConditions()[i].estValChiffre());
                    //
                    //std::cout << "DEBUG: Lancement chainage arrière de: ";
                    //faitTmp.affichageFait();
                    //std::cout << std::endl;
                    //
                    valide = chainageArriere(faitTmp);
                    if (valide)
                    {
                        break;
                    }
                }
            }
        }
    }
    return valide;
}


bool Moteur::chainageArriere(Fait & faitATest)
{
    bool valide = true;
    //SI (F ∈ BF) ALORS ChaînageArriere
    if (appartientFaitBDC(faitATest))
    {
        std::cout << "Le fait suivant: ";
        faitATest.affichageFait();
        std::cout << "appartient déjà à la base de connaissance." << std::endl;
        return valide;
    }
    else //SINON
    {
        std::cout << "***** DEMARRAGE CHAINAGE ARRIERE *****" << std::endl;
        // Construire ER ensemble de règles R, telle que F ∈ conclusion(R)
        std::vector<Regle> vecSousBut;
        for (unsigned int i(0); i<BDC->getRegles().size();i++)
        {
            if (BDC->getRegles()[i].estResultat(faitATest))
            {
                vecSousBut.push_back(BDC->getRegles()[i]);
            }
        }

        if (vecSousBut.size() == 0)
            return false;

        bool valide = true;
        while (valide && (vecSousBut.size() > 0))
        {
            //On prend le premier élément de vecteur de sous
            Regle regTmp = vecSousBut[0];
            std::cout << "DEBUG: Regle en cours dans vecSousBut: ****" << std::endl;;
            regTmp.affichageRegle();
            std::cout << "********" << std::endl;
            //On l'enlève des sous but à vérifier
            vecSousBut.erase(vecSousBut.begin());
            //On vérifier les prémisses
            valide = valide && verifierPremisses(regTmp);
        }

        return valide;

        std::cout << "***** CHAINAGE ARRIERE TERMINE *****" << std::endl;
    }
}

