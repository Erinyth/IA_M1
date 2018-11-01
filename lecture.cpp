#include "lecture.hh"

#include "fait.hh"
#include "regle.hh"
#include "condition.hh"
#include "resultat.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

void creerFaits(std::ifstream & fichierEntree, baseDeConnaissance & BDC)
{
    std::string ligneEnCours;
    for (unsigned int i(0); i<BDC.getNbFaits(); i++)
    {
        getline(fichierEntree, ligneEnCours);
        std::vector<std::string> res = explode(ligneEnCours, ':');

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
        BDC.ajoutFait(faitTmp);
    }
}

Condition creerCondition(std::string chaineCondition)
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

Resultat creerResultat(std::string chaineResultat)
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

void creerRegles(std::ifstream & fichierEntree, baseDeConnaissance & BDC)
{
    //Exemple de règle: symptome = fievre,symptome = mal -> maladie = gastro
    std::string ligneEnCours;
    for (unsigned int i(0); i<BDC.getNbRegles(); i++)
    {
        Regle regleTMP;

        getline(fichierEntree, ligneEnCours);
        std::vector<std::string> chaine = explode(ligneEnCours, '/');

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
        BDC.ajoutRegle(regleTMP);
    }
}

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

void creationBaseConnaissance(char* fichierDonnees, baseDeConnaissance & BDC)
{
    std::ifstream fichier(fichierDonnees, std::ios::in);  // on ouvre le fichier en lecture

    if(fichier)  // si l'ouverture a réussi
    {
        std::string ligneEnCours;
        getline(fichier, ligneEnCours);
        BDC.setNbFaits(std::stoi(ligneEnCours));

        getline(fichier, ligneEnCours);
        BDC.setNbRegles(std::stoi(ligneEnCours));

        //Création de tous les faits
        creerFaits(fichier,BDC);

        //Création de toutes les règles
        creerRegles(fichier,BDC);

        fichier.close();
    }
    else
    {
        std::cerr << "Ouverture du fichier impossible" << std::endl;
        exit(1);
    }
}

