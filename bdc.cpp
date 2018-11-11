#include "bdc.hh"

#include "fait.hh"
#include "regle.hh"
#include "condition.hh"
#include "resultat.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

/**
 * @brief explode
 * @param s
 * @param delim
 * @return
 * https://stackoverflow.com/questions/12966957/is-there-an-equivalent-in-c-of-phps-explode-function
 * Fonction eclatant une chaine par rapport à son délimiteur
 */
std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

bool baseDeConnaissance::ajouterFaitDepuisTexte(std::string faitTexte)
{
    std::vector<std::string> res = explode(faitTexte, ':');

    bool estChiffre = false;
    //Comparaison du premier caractère de la valeur
    std::string premCar = res[1].substr(0,1);
    if (premCar == "%") //Si la valeur est un integer
    {
        std::string valeurSansPourcent = res[1].substr(1);
        res[1] = valeurSansPourcent;
        estChiffre = true;
    }

    Fait faitTmp(res[0],res[1], estChiffre);

    bool valide = verificationCoherenceFait(faitTmp);

    if (valide)
    {
        ajoutFait(faitTmp);
        return true;
    }
    else
        return false;
}

bool baseDeConnaissance::ajouterRegleDepuisTexte(std::string regleTexte)
{
    Regle regleTMP;

    std::vector<std::string> chaine = explode(regleTexte, '/');

    std::string conditions = chaine[0];    //Chaine de toutes les conditions
    std::vector<std::string> resCond = explode(conditions, ',');
    for (unsigned int i(0); i<resCond.size(); i++)
    {
        Condition condTmp = creerCondition(resCond[i]);
        regleTMP.ajoutCondition(condTmp);
    }

    std::string resultat = chaine[1];      //Chaine de tous les résultats
    std::vector<std::string> resRes = explode(resultat, ',');
    for (unsigned int i(0); i<resRes.size(); i++)
    {
        Resultat resTmp = creerResultat(resRes[i]);
        regleTMP.ajoutResultat(resTmp);
    }

    bool ajoutValide = verificationCoherenceRegle(regleTMP);
    if (ajoutValide)
    {
        ajoutRegle(regleTMP);
        return true;
    }
    else
        return false;
}


void baseDeConnaissance::creerFaits(std::ifstream & fichierEntree)
{
    std::string ligneEnCours;
    for (unsigned int i(0); i<getNbFaits(); i++)
    {
        getline(fichierEntree, ligneEnCours);

        ajouterFaitDepuisTexte(ligneEnCours);
    }
}

Condition baseDeConnaissance::creerCondition(std::string chaineCondition)
{
    std::vector<std::string> chaineCond = explode(chaineCondition, ' ');

    std::string elementTmp = chaineCond[0];
    std::string opTmp = chaineCond[1];
    std::string valeurTmp = chaineCond[2];
    bool estChiffre = false;

    //Comparaison du premier caractère de la valeur
    std::string premCar = valeurTmp.substr(0,1);
    if (premCar == "%") //Si la valeur est un integer
    {
        std::string valeurSansPourcent = valeurTmp.substr(1);
        valeurTmp = valeurSansPourcent;
        estChiffre = true;
    }

    Condition condTmp(elementTmp, valeurTmp, opTmp, estChiffre);
    return condTmp;
}

Resultat baseDeConnaissance::creerResultat(std::string chaineResultat)
{
    std::vector<std::string> chaineRes = explode(chaineResultat, ' ');
    std::string elementTmp = chaineRes[1];
    std::string opTmp = chaineRes[2];
    std::string valeurTmp = chaineRes[3];
    bool estChiffre;

    //Comparaison du premier caractère de la valeur
    std::string premCar = valeurTmp.substr(0,1);
    if (premCar == "%") //Si la valeur est un integer
    {
        std::string valeurSansPourcent = valeurTmp.substr(1);
        valeurTmp = valeurSansPourcent;
        estChiffre = true;
    }

    Resultat resTmp(elementTmp,valeurTmp,opTmp,estChiffre);
    return resTmp;
}

void baseDeConnaissance::creerRegles(std::ifstream & fichierEntree)
{
    //Exemple de règle: symptome = fievre,symptome = mal -> maladie = gastro
    std::string ligneEnCours;
    for (unsigned int i(0); i<getNbRegles(); i++)
    {
        getline(fichierEntree, ligneEnCours);

        ajouterRegleDepuisTexte(ligneEnCours);
    }
}

void baseDeConnaissance::viderBDC()
{
    nbFaits = 0;
    listeFait.clear();
    nbRegles = 0;
    listeRegle.clear();
}

void baseDeConnaissance::creationBaseConnaissance(const char* fichierDonnees)
{
    //On enlève toutes les connaissances
    viderBDC();

    std::ifstream fichier(fichierDonnees, std::ios::in);  // on ouvre le fichier en lecture

    if(fichier)  // si l'ouverture a réussi
    {
        std::string ligneEnCours;
        getline(fichier, ligneEnCours);
        setNbFaits(std::stoi(ligneEnCours));

        getline(fichier, ligneEnCours);
        setNbRegles(std::stoi(ligneEnCours));

        getline(fichier, ligneEnCours);    //Ligne /--Faits

        //Création de tous les faits
        creerFaits(fichier);

        getline(fichier, ligneEnCours);    //Ligne /--Regles

        //Création de toutes les règles
        creerRegles(fichier);

        fichier.close();
    }
    else
    {
        std::cerr << "Ouverture du fichier impossible" << std::endl;
        exit(1);
    }
}


bool baseDeConnaissance::appartientFaitBDC(Fait faitTest)
{
    for (unsigned int i(0); i<listeFait.size(); i++)
    {
        if (listeFait[i] == faitTest)
            return true;
    }
    return false;
}

Fait baseDeConnaissance::creerFaitAvecOperateur(Resultat & res)
{
    std::string elTmp = res.getElement();

    if (res.getOperateur() == "<")
    {
        std::string ajout = "*<";
        elTmp = elTmp + ajout;
    }
    if (res.getOperateur() == "<=")
    {
        std::string ajout = "*<=";
        elTmp = elTmp + ajout;
    }
    if (res.getOperateur() == ">=")
    {
        std::string ajout = "*>=";
        elTmp = elTmp + ajout;
    }
    if (res.getOperateur() == ">")
    {
        std::string ajout = "*>";
        elTmp = elTmp + ajout;
    }

    Fait faitTmp(elTmp, res.getValeur(), res.estResultatChiffre());

    return faitTmp;
}

std::string baseDeConnaissance::InformationsCompleteBDC()
{
    std::string informations = "";
    for (unsigned int i(1); i<listeFait.size()+1; i++)
    {
        informations = informations + "********** FAITS " + std::to_string(i) + " **********\n";
        informations = informations + listeFait[i-1].InformationFait();
    }

    for (unsigned int i(1); i<listeRegle.size()+1; i++)
    {
        informations = informations +  "********** REGLE " + std::to_string(i) + " **********\n";
        informations = informations + listeRegle[i-1].InformationRegle();
    }
    return informations;
}

std::string baseDeConnaissance::sauvegardeBDC()
{
    std::string chaineSauvegarde = "";
    chaineSauvegarde = chaineSauvegarde + std::to_string(getNbFaits()) + "\n";
    chaineSauvegarde = chaineSauvegarde + std::to_string(getNbRegles()) + "\n";
    chaineSauvegarde = chaineSauvegarde + "/-- Faits\n";

    for (unsigned int i(0); i<getNbFaits(); i++)
    {
        Fait faitEnCours = getFaits()[i];
        if (faitEnCours.getValFaitChiffre())    //Si c'est un chiffre
            chaineSauvegarde = chaineSauvegarde + faitEnCours.getTypeFait() + ":%" + faitEnCours.getValFait() + "\n";
        else
            chaineSauvegarde = chaineSauvegarde + faitEnCours.getTypeFait() + ":" + faitEnCours.getValFait() + "\n";
    }

    chaineSauvegarde = chaineSauvegarde + "/-- Regles\n";

    for (unsigned int i(0); i<getNbRegles(); i++)
    {
        Regle regleEnCours = getRegles()[i];

        for (unsigned int j(0); j<regleEnCours.getConditions().size();j++)
        {
            Condition condEnCours = regleEnCours.getConditions()[j];
            if (condEnCours.estValChiffre())
                chaineSauvegarde = chaineSauvegarde + condEnCours.getEltTest() + " " + condEnCours.getOperateur() + " %" + condEnCours.getValeurChaine();
            else
                chaineSauvegarde = chaineSauvegarde + condEnCours.getEltTest() + " " + condEnCours.getOperateur() + " " + condEnCours.getValeurChaine();

            if (j < regleEnCours.getConditions().size()-1)
                chaineSauvegarde = chaineSauvegarde + ",";
        }

        chaineSauvegarde = chaineSauvegarde + " \/ ";

        for (unsigned int j(0); j<regleEnCours.getResRegle().size();j++)
        {
            Resultat resEnCours = regleEnCours.getResRegle()[j];
            if (resEnCours.estResultatChiffre())
                chaineSauvegarde = chaineSauvegarde + resEnCours.getElement() + " " + resEnCours.getOperateur() + " %" + resEnCours.getValeur();
            else
                chaineSauvegarde = chaineSauvegarde + resEnCours.getElement() + " " + resEnCours.getOperateur() + " " + resEnCours.getValeur();
        }

        chaineSauvegarde = chaineSauvegarde + "\n";
    }

    return chaineSauvegarde;
}


bool baseDeConnaissance::verificationCoherenceFait(Fait faitAAjouter)
{
    //On a considéré qu'un fait vrai ne peut être passé à faux et inversement
    //On a considéré qu'un fait ayant une valeur chiffrée ne peux être modifié
    if (faitAAjouter.getValFait() == "vrai" || faitAAjouter.getValFait() == "faux" || faitAAjouter.estFaitChiffre())
    {
        for (unsigned int i(0); i<listeFait.size(); i++)
        {
            Fait faitEnCours = listeFait[i];
            //Si il existe déjà un fait de même nom avec une valeur existante
            if (faitEnCours.getTypeFait() == faitAAjouter.getTypeFait())
                return false;
        }
    }
    return true;
}

bool baseDeConnaissance::verificationCoherenceRegle(Regle regleAAjouter)
{
    //Cas
    //A et B -> X et nonX
    //ou encore A et B -> age = 3 et age = 8
    std::vector<Resultat> resultatAProbleme;

    for (unsigned int i(0); i<regleAAjouter.getResRegle().size();i++)
    {
        Resultat resEnCours = regleAAjouter.getResRegle()[i];
        if (resEnCours.getValeur() == "vrai" || resEnCours.getValeur() == "faux" || resEnCours.estResultatChiffre())
        {
            if (!resultatAProbleme.empty())
            {
                for (unsigned int j(0); j<resultatAProbleme.size(); j++)
                {
                    Resultat resProblemeEnCours = resultatAProbleme[j];

                    //Si c'est le même élément mais avec une valeur différente, ce n'est pas cohérent
                    if (resEnCours.getElement() == resProblemeEnCours.getElement())
                        if (resEnCours.getOperateur() == resProblemeEnCours.getOperateur())
                            if (resEnCours.getValeur() != resProblemeEnCours.getValeur())
                                return false;
                }
            }
            resultatAProbleme.push_back(resEnCours);
        }
    }
    //Cas
    //D et E -> L
    //D et E -> nonL
    for (unsigned int i(0); i<listeRegle.size(); i++)
    {
        Regle regleEnCours = listeRegle[i];

        int nombreConditionEq = 0;
        if (regleEnCours.getConditions().size() == regleAAjouter.getConditions().size())
        {
            for (unsigned int j(0); j<regleEnCours.getConditions().size(); j++)
            {
                for (unsigned int k(0); k<regleAAjouter.getConditions().size(); k++)
                {
                    Condition conditionEnCours = regleEnCours.getConditions()[j];
                    Condition conditionAAjouter = regleAAjouter.getConditions()[k];

                    //Si on a des conditions identiques entre la règle à ajouter et la règle en train d'être parcourure
                    if (conditionEnCours == conditionAAjouter)
                        nombreConditionEq++;    //On augmente le nombre de conditions équivalent
                }
            }

            //Si les conditions des deux règles sont les mếmes (autant de conditions equivalents qu'il y a de conditions)
            if (nombreConditionEq == regleEnCours.getConditions().size() && nombreConditionEq == regleAAjouter.getConditions().size())
            {
                //Si il y a autant de résultats
                if (regleEnCours.getResRegle().size() == regleAAjouter.getResRegle().size())
                {
                    for (unsigned int j(0); j<regleEnCours.getResRegle().size(); j++)
                    {
                        for (unsigned int k(0); k<regleAAjouter.getResRegle().size(); k++)
                        {
                            Resultat resEnCours = regleEnCours.getResRegle()[j];
                            Resultat resAAjouter = regleAAjouter.getResRegle()[k];

                            //Si on a des resultats booléens ou des chiffres
                            if (resEnCours.getValeur() == "vrai" || resEnCours.getValeur() == "faux" || resEnCours.estResultatChiffre())
                            {
                                //Si il est question du même élément
                                if (resEnCours.getElement() == resAAjouter.getElement())
                                    if (resEnCours.getOperateur() == resAAjouter.getOperateur())
                                        //Mais que le résultat est différent
                                        if (resEnCours.getValeur() != resAAjouter.getValeur())
                                            return false;
                            }
                        }
                    }
                }
            }
        }
    }
    //Sinon, aucun problème n'a été trouvé
    return true;
}
