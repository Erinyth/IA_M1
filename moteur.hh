#pragma once
#include "bdc.hh"

class Moteur{
public:
    Moteur(baseDeConnaissance * baseDC): BDC(baseDC), infoDeroulement()
    {}

    /**
     * @brief lancementRecherche Lance la recherche depuis l'interface
     * @param faitAChercher
     * @param typeRecherche
     * @param critere
     * @return
     */
    bool lancementRecherche(std::string faitAChercher, std::string typeRecherche, std::string critere);

    /**
     * @brief regleApplicable Retourne true si il existe une règle applicable dans la base de données
     * Applicable implique que les faits sont disponibles et que la règle n'a pas déjà été utilisée
     * @param type  Peut être AV ou AR suivant le type de chainage qui l'appelle
     * @return
     */
    bool regleApplicableExistante(std::string type);

    /**
     * @brief chainageAvant Lance le chainage avant avec le mode de gestion de conflit
     * @param faitATest
     * @param gestionConflit
     * @return
     */
    bool chainageAvant(Fait & faitATest, std::string gestionConflit);

    /**
     * @brief chainageArriere Lance le chainage arrière avec le mode de gestion de conflit
     * @param faitATest
     * @param gestionConflit
     * @return
     */
    bool chainageArriere(Fait & faitATest, std::string gestionConflit);

    /**
     * @brief verifierPremisses Vérifie les prémisses d'une règle
     * @param gestionConflit
     * @param regTmp
     * @return
     */
    bool verifierPremisses(Regle & regTmp, std::string gestionConflit);

    /**
     * @brief testFaitAvecOperateur Vérifie si un fait menant à cette condition existe dans la BDC, et vérifiant les signes
     * <, <=, =>, >, donc en parcourant tous les cas possibles
     * @param condTMP
     * @param gestionConflit
     * @return
     */
    bool testConditionAvecOperateur(Condition & condTMP, std::string gestionConflit);

    /**
     * @brief nouveauFaitParRegle Vérifier qu'une règle peut nous donner des faits non connus
     * @param regleEnCours
     * @return
     */
    bool nouveauFaitParRegle(Regle regleEnCours);

    /**
     * @brief getInfoDeroulement Ces trois methodes permettent d'envoyer à la fenêtre les informations sur le déroulement
     * des chainages
     * @return
     */
    std::string getInfoDeroulement()
    { return infoDeroulement; }

    void resetInfoDeroulement()
    { infoDeroulement = ""; }

    void ajoutInfoDeroulement(std::string infoSup)
    { infoDeroulement = infoDeroulement + infoSup; }



private:
    baseDeConnaissance * BDC;
    std::string infoDeroulement;
};
