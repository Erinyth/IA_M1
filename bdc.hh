#pragma once
#include "fait.hh"
#include "regle.hh"

class baseDeConnaissance{
public:
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

    std::vector<Fait> getFaits()
    { return listeFait; }

    std::vector<Regle> getRegles()
    { return listeRegle; }

    /**
     * Méthodes d'ajout de règles et faits
     */
    void ajoutFait(Fait f)
    { listeFait.push_back(f); }

    void ajoutRegle(Regle r)
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

private:
    unsigned int nbFaits;
    std::vector<Fait> listeFait;
    unsigned int nbRegles;
    std::vector<Regle> listeRegle;
};
