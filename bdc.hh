#pragma once
#include "fait.hh"
#include "regle.hh"
#include <fstream>
#include <sstream>

class baseDeConnaissance{
public:
    baseDeConnaissance(): nbFaits(0), listeFait(), nbRegles(0), listeRegle()
    {}

    /**
     * Setters et getters sur les nombres de faits et règles
     */
    void setNbFaits(unsigned int nb)
    { nbFaits = nb; }

    void setNbRegles(unsigned int nb)
    { nbRegles = nb; }

    unsigned int getNbFaits()
    { return nbFaits; }

    unsigned int getNbRegles()
    { return nbRegles; }

    std::vector<Fait>& getFaits()
    { return listeFait; }

    std::vector<Regle>& getRegles()
    { return listeRegle; }

    /**
     * Méthodes d'ajout de règles et faits
     */
    void ajoutFait(Fait f)
    { listeFait.push_back(f); }

    void ajoutRegle(Regle & r)
    { listeRegle.push_back(r); }

    /**
     * Méthodes d'affichage des règles et faits
     */
    void affichageEnsembleFaits()
    {
        for (unsigned int i(0); i<listeFait.size(); i++)
        {
            std::cout << "********** FAITS " << i+1 << " **********" << std::endl;
            listeFait[i].affichageFait();
        }
    }

    void affichageEnsembleRegles()
    {
        for (unsigned int i(0); i<listeRegle.size(); i++)
        {
            std::cout << "********** REGLE " << i+1 << " **********" << std::endl;
            listeRegle[i].affichageRegle();
        }
    }

    /**
     * @brief appartientFaitBDC Retourne true si un fait existe dans la base de connaissance
     * @param faitTest
     * @return
     */
    bool appartientFaitBDC(Fait faitTest);

    /**
     * @brief creerFaitAvecOperateur Ajout un fait dans la base en fonction de l'opérateur (<,>,<=,>=)
     * @param res
     */
    Fait creerFaitAvecOperateur(Resultat & res);

    /**
     * @brief ajouterFaitDepuisTexte Ajoute un fait dans la BDC depuis sa chaine
     * @param faitTexte
     */
    bool ajouterFaitDepuisTexte(std::string faitTexte);

    /**
     * @brief ajouterRegleDepuisTexte Ajoute une regle dans la BDC depuis sa chaine
     * @param regleTexte
     */
    bool ajouterRegleDepuisTexte(std::string regleTexte);

    /**
     * @brief lectureComplete
     * Va lire le fichier d'entrée et créer la base de connaissance associée
     */
    void creationBaseConnaissance(const char* fichierDonnees);

    /**
     * @brief Va lire toutes les règles  et les ajouter à la base de connaissances
     */
    void creerRegles(std::ifstream & fichierEntree);

    /**
     * @brief lectureFait
     * Va créer tous les faits dans la base de connaissance
     */
    void creerFaits(std::ifstream & fichierEntree);

    /**
     * @brief creerCondition Créer une condition d'une règle
     * @param chaineCondition
     * @return
     */
    Condition creerCondition(std::string chaineCondition);

    /**
     * @brief creerResultat Créer un résultat d'une règle
     * @param chaineResultat
     * @return
     */
    Resultat creerResultat(std::string chaineResultat);

    /**
     * @brief viderBDC Vide toutes les connaissances
     */
    void viderBDC();

    /**
     * @brief InformationsCompleteBDC Retourne sous forme de string l'ensemble des connaissances
     * @return
     */
    std::string InformationsCompleteBDC();

    /**
     * @brief sauvegardeBDC Envoi la chaine permettant la sauvegarde dans un fichier
     * @return
     */
    std::string sauvegardeBDC();

    /**
     * @brief verificationCoherenceFait Verifie qu'un fait est cohérent avant de l'ajouter
     * @return
     */
    bool verificationCoherenceFait(Fait faitAAjouter);

    /**
     * @brief verificationCoherenceRegle Verifie qu'une règle est cohérente avant de l'ajouter
     * @param regleAAjouter
     * @return
     */
    bool verificationCoherenceRegle(Regle regleAAjouter);

    private:
        unsigned int nbFaits;
    std::vector<Fait> listeFait;
    unsigned int nbRegles;
    std::vector<Regle> listeRegle;
};
