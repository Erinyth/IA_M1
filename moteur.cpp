#include "moteur.hh"
#include <sstream>

#define TAILLE_MAX_TEST 100000000

/**
 * @brief explode
 * @param s
 * @param delim
 * @return
 * https://stackoverflow.com/questions/12966957/is-there-an-equivalent-in-c-of-phps-explode-function
 * Fonction eclatant une chaine par rapport à son délimiteur
 */
std::vector<std::string> explodeMoteur(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

bool Moteur::lancementRecherche(std::string faitAChercher, std::string typeRecherche, std::string critere)
{
    std::vector<std::string> resFaitChercher = explodeMoteur(faitAChercher,':');
    bool estChiffre = false;
    //Comparaison du premier caractère de la valeur
    std::string premCar = resFaitChercher[1].substr(0,1);
    if (premCar == "%") //Si la valeur est un integer
    {
        std::string valeurSansPourcent = resFaitChercher[1].substr(1);
        resFaitChercher[1] = valeurSansPourcent;
        estChiffre = true;
    }

    Fait faitTmp(resFaitChercher[0],resFaitChercher[1], estChiffre);

    bool resultat;
    if (typeRecherche == "AV")
        resultat = chainageAvant(faitTmp, critere);
    else
        resultat = chainageArriere(faitTmp, critere);

    return resultat;
}

bool Moteur::nouveauFaitParRegle(Regle regleEnCours)
{
    //On vérifie que au moins un des résultat de la règle est nouveau
    int nombreNouveauFaits = 0;
    for (unsigned int j(0); j<regleEnCours.getResRegle().size();j++)
    {
        Resultat resultatEnCours = regleEnCours.getResRegle()[j];
        if (resultatEnCours.getOperateur() == "=")
        {
            Fait faitTmp(resultatEnCours.getElement(), resultatEnCours.getValeur(), resultatEnCours.estResultatChiffre());
            bool nouveau = BDC->appartientFaitBDC(faitTmp);
            //Nouveau est à false si l'élément n'existe pas
            if (!nouveau)
                nombreNouveauFaits++;
        }
        else
        {
            Fait faitTmp = BDC->creerFaitAvecOperateur(resultatEnCours);
            BDC->appartientFaitBDC(faitTmp);
            bool nouveau = BDC->appartientFaitBDC(faitTmp);
            if (!nouveau)
                nombreNouveauFaits++;
        }
    }
    if (nombreNouveauFaits == 0)
        return false;
    else
        return true;
}

bool Moteur::regleApplicableExistante(std::string type)
{
    for (unsigned int i(0); i<BDC->getRegles().size(); i++)  //Parcours des règles
    {
        Regle regleEnCours = BDC->getRegles()[i];

        if (type == "AV")
        {
            //Si le chainage avant n'a pas été effectué sur cette règle
            if (regleEnCours.chainageAvantEstFait() == false)
            {
                bool nouveauFaitExistant = nouveauFaitParRegle(regleEnCours);

                //Si il est utile de vérifier cette règle
                if (nouveauFaitExistant)
                {
                    //Si la règle est applicable
                    if (regleEnCours.estRegleApplicable(BDC))
                    {
                        std::cout << "Au moins une règle est applicable: la règle " << i+1 << std::endl;;
                        return true;
                    }
                }
            }
        }
        else
            if (type == "AR")
            {
                if (regleEnCours.chainageArriereEstFait() == false)
                    if (regleEnCours.estRegleApplicable(BDC))
                        return true;
            }

    }
    return false;
}


bool Moteur::chainageAvant(Fait & faitATest, std::string gestionConflit)
{
    if (BDC->appartientFaitBDC(faitATest))
    {
        std::string info = "Le fait: " + faitATest.InformationFait() + " appartient déjà à la base de connaissance";
        ajoutInfoDeroulement(info);
        return true;
    }
    else
    {
        std::cout << "***** DEMARRAGE CHAINAGE AVANT *****" << std::endl;
        //TANT QUE F n'est pas dans  BF ET QU'il existe dans BR une règle applicable FAIRE
        while(!BDC->appartientFaitBDC(faitATest) && regleApplicableExistante("AV"))
        {
            //Choisir une règle applicable  R (étape de résolution de conflits, utilisation d'heuristiques, de métarègles)
            if (gestionConflit == "premier")
            {
                //Conflit: On applique la première règle applicable
                for (unsigned int i(0); i<BDC->getRegles().size();i++)   //Parcours des règles
                {
                    Regle & regleEnCours = BDC->getRegles()[i];
                    if (!regleEnCours.chainageAvantEstFait() && regleEnCours.estRegleApplicable(BDC))
                    {
                        std::string infoRegle = "Règle déclenchée :\n " + regleEnCours.InformationRegle() + "\n";
                        ajoutInfoDeroulement(infoRegle);

                        // BF = BF union concl(R) (déclenchement de la règle R, sa conclusion est rajoutée à la base de faits)
                        for (unsigned int j(0); j<regleEnCours.getResRegle().size();j++)
                        {
                            Resultat resultatEnCours = regleEnCours.getResRegle()[j];
                            //Si le résultat lu de la règle est un fait classique (fait = valeur)
                            if (resultatEnCours.getOperateur() == "=")
                            {
                                Fait faitTmp(resultatEnCours.getElement(), resultatEnCours.getValeur(), resultatEnCours.estResultatChiffre());
                                BDC->ajoutFait(faitTmp);
                                std::string infoFait = "Fait ajouté : " + faitTmp.InformationFait() + "\n";
                                ajoutInfoDeroulement(infoFait);
                                //std::cout << "DEBUG: Fait ajouté: ";
                                //faitTmp.affichageFait();

                                break;
                            }
                            else    //Cas du <,>,<=,>=
                            {
                                Fait faitTmp = BDC->creerFaitAvecOperateur(resultatEnCours);
                                BDC->ajoutFait(faitTmp);
                                std::string infoFait = "Fait ajouté : " + faitTmp.InformationFait() + "\n";
                                ajoutInfoDeroulement(infoFait);
                                //std::cout << "DEBUG: Fait ajouté: ";
                                //faitTmp.affichageFait();
                                break;
                            }
                        }

                        // BR = BR - R  (désactivation de R)
                        regleEnCours.chainageAvantComplete(); //On indique que cette règle a maintenant été utilisée par le chainage avant

                        //Arret de la boucle for
                        break;
                    }
                }
            }
            if (gestionConflit == "nombrePremisse")
            {
                //Conflit: On applique la règle avec le plus de prémisse
                int nombrePremisseMax = 0;
                int indiceRegleALancer;

                for (unsigned int i(0); i<BDC->getRegles().size();i++)
                {
                    Regle regleTmp = BDC->getRegles()[i];
                    if (!regleTmp.chainageAvantEstFait() && regleTmp.estRegleApplicable(BDC))
                    {
                        int nombrePremisseRegle = regleTmp.getConditions().size();
                        if (nombrePremisseMax < nombrePremisseRegle)
                        {
                            nombrePremisseMax = nombrePremisseRegle;
                            indiceRegleALancer = i;
                        }
                    }
                }

                //Ici, on a la règle activable avec le plus de prémisse
                Regle & regleEnCours = BDC->getRegles()[indiceRegleALancer];
                std::string infoRegle = "Règle appliquée : " + regleEnCours.InformationRegle() + "\n";
                ajoutInfoDeroulement(infoRegle);

                // BF = BF union concl(R) (déclenchement de la règle R, sa conclusion est rajoutée à la base de faits)
                for (unsigned int j(0); j<regleEnCours.getResRegle().size();j++)
                {
                    Resultat resultatEnCours = regleEnCours.getResRegle()[j];
                    //Si le résultat lu de la règle est un fait classique (fait = valeur)
                    if (resultatEnCours.getOperateur() == "=")
                    {
                        Fait faitTmp(resultatEnCours.getElement(), resultatEnCours.getValeur(), resultatEnCours.estResultatChiffre());
                        BDC->ajoutFait(faitTmp);
                        std::string infoFait = "Fait ajouté : " + faitTmp.InformationFait() + "\n";
                        ajoutInfoDeroulement(infoFait);
                        break;
                    }
                    else    //Cas du <,>,<=,>=
                    {
                        Fait faitTmp = BDC->creerFaitAvecOperateur(resultatEnCours);
                        BDC->ajoutFait(faitTmp);
                        std::string infoFait = "Fait ajouté : " + faitTmp.InformationFait() + "\n";
                        ajoutInfoDeroulement(infoFait);
                        break;
                    }
                }

                // BR = BR - R  (désactivation de R)
                regleEnCours.chainageAvantComplete(); //On indique que cette règle a maintenant été utilisée par le chainage avant
            }
        }
        if (BDC->appartientFaitBDC(faitATest))
        {
            std::cout << "***** CHAINAGE AVANT TERMINE *****" << std::endl;
            return true;
        }
        else
        {
            std::cout << "***** CHAINAGE AVANT TERMINE *****" << std::endl;
            return false;
        }
    }
}

bool Moteur::testConditionAvecOperateur(Condition & condATest, std::string gestionConflit)
{
    bool valide = true;
    unsigned int valeurFait = condATest.getValeurChiffre();
    std::string oper = condATest.getOperateur();
    //Méthode qui va être répétée pour tous les opérateurs autre que = et <>,
    //avec le for qui va changer suivant les opérateurs
    if (oper == "<" || oper == "<=")
    {
        if (oper == "<")
            valeurFait = valeurFait-1;
        for (valeurFait; valeurFait>=0; valeurFait--)
        {
            std::stringstream ss;
            ss << valeurFait;
            std::string valTmp = ss.str(); //Conversion de la valeur numérique en chaine pour créer un fait à tester
            // Création du fait à tester
            Fait faitTmp(condATest.getEltTest(),valTmp,condATest.estValChiffre());
            // On lance le chainage arrière sur ce fait temporaire
            valide = chainageArriere(faitTmp, gestionConflit);
            //Si le fait est vérifiable
            if (valide)
            {
                //Il existe un fait vérifiable, donc on arrête notre recherche
                break;
            }
        }
    }
    if (oper == ">=" || oper == ">")
    {
        if (oper == ">")
            valeurFait = valeurFait+1;
        for (valeurFait; valeurFait<=TAILLE_MAX_TEST; valeurFait++)
            //On peut mettre une grand valeur de TAILLE_MAX_TEST puisque l'on vérifiera d'abord qu'il existe un élément
            //de taille supérieure à la valeurFait initiale. On arrivera pas jusqu'a ce for sinon
        {
            std::stringstream ss;
            ss << valeurFait;
            std::string valTmp = ss.str();
            Fait faitTmp(condATest.getEltTest(),valTmp,condATest.estValChiffre());
            std::cout << "Fait en cours:" << std::endl;
            faitTmp.affichageFait();
            std::cout << std::endl;
            valide = chainageArriere(faitTmp, gestionConflit);
            if (valide)
                break;
        }
    }
    return valide;
}

bool Moteur::verifierPremisses(Regle & regTmp, std::string gestionConflit)
{
    bool valide = true;
    bool OK = true;
    //On vérifier les prémisses de cette règle, un à un
    for (unsigned int j(0); j<regTmp.getConditions().size();j++)
    {
        //Si la condition n'est ni connue dans la BDC ni un résultat de règle
        if (!regTmp.getConditions()[j].estResultatAutreRegle(BDC) && !regTmp.getConditions()[j].estConditionApplicable(BDC))
        {
            std::string info = "La condition " + regTmp.InformationRegle() + " ne peut être obtenue.\n";
            ajoutInfoDeroulement(info);
            OK = false;
            valide = false;
            break;
        }
    }
    if (OK) //Toutes les conditions sont des résultats de règle, ou alors sont applicables via la BDC
        //On va donc vérifier que ces conditions sont elles même réalisables
    {
        for (unsigned int i(0); i<regTmp.getConditions().size();i++) //Parcours des conditions
        {
            Condition conditionEnCours = regTmp.getConditions()[i];

            if (conditionEnCours.getOperateur() == "=") //Cas du =
            {
                //Dans ce cas, on doit juste vérifier que le fait fonctionne pour cette valeur
                Fait faitTmp(conditionEnCours.getEltTest(),conditionEnCours.getValeurChaine(),conditionEnCours.estValChiffre());
                valide = valide && chainageArriere(faitTmp, gestionConflit);
            }
            if (conditionEnCours.getOperateur() == "<>") //Cas du =
            {
                //Dans ce cas, on doit juste vérifier que le fait ne fonctionn pas pour cette valeur
                Fait faitTmp(conditionEnCours.getEltTest(),conditionEnCours.getValeurChaine(),conditionEnCours.estValChiffre());
                valide = valide && !chainageArriere(faitTmp, gestionConflit);
            }
            //On doit trouver ici un fait qui valide pour <, >, <=, >=
            else
            {
                //On appelle la fonction qui va vérifier tous les faits possible menant à la condition
                valide = valide && testConditionAvecOperateur(conditionEnCours,gestionConflit);
            }
        }
    }
    return valide;
}

bool Moteur::chainageArriere(Fait & faitATest, std::string gestionConflit)
{
    bool valide = true;
    if (BDC->appartientFaitBDC(faitATest))
    {
        std::string infoFait = "Le fait suivant: " + faitATest.InformationFait() + " appartient déjà à la base de connaissance\n";
        ajoutInfoDeroulement(infoFait);
        return valide;
    }
    else
    {
        std::cout << "***** DEMARRAGE CHAINAGE ARRIERE *****" << std::endl;
        // Construire ER ensemble de règles R, telle que F ∈ conclusion(R)
        std::vector<Regle> vecSousBut;
        for (unsigned int i(0); i<BDC->getRegles().size();i++)
        {
            if (BDC->getRegles()[i].donneResultat(faitATest))
            {
                vecSousBut.push_back(BDC->getRegles()[i]);
            }
        }
        if (vecSousBut.size() == 0)
            return false;

        bool valide = true;
        while (valide && (vecSousBut.size() > 0))
        {
            int indiceRegleAChercher;
            int tailleMaxPremisse = 0;
            if (gestionConflit == "premier")
            {
                //On prend le premier élément de vecteur de sous
                indiceRegleAChercher = 0;
            }
            if (gestionConflit == "nombrePremisse")
            {
                for (unsigned int i(0); i<vecSousBut.size();i++)
                {
                    Regle regleEnCours = vecSousBut[i];
                    if (regleEnCours.getConditions().size() > tailleMaxPremisse)
                    {
                        tailleMaxPremisse = regleEnCours.getConditions().size();
                        indiceRegleAChercher = i;
                    }
                }
            }

            Regle regTmp = vecSousBut[indiceRegleAChercher];
            std::string infoRegle = "Règle en cours d'analyse :\n " + regTmp.InformationRegle() + "\n";
            ajoutInfoDeroulement(infoRegle);
            //On l'enlève des sous but à vérifier
            vecSousBut.erase(vecSousBut.begin()+indiceRegleAChercher);
            //On vérifier les prémisses
            valide = valide && verifierPremisses(regTmp,gestionConflit);

            if (valide) //Les prémisses sont vérifiées, on ajoute l'élément
            {
                std::string infoFait = "Fait ajouté : " + faitATest.InformationFait() + "\n";
                ajoutInfoDeroulement(infoFait);
                BDC->ajoutFait(faitATest);
            }
        }

        return valide;

        std::cout << "***** CHAINAGE ARRIERE TERMINE *****" << std::endl;
    }
}
