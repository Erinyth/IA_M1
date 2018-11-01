#pragma once
#include <string>
#include <iostream>

class Fait{
public:
    Fait(std::string type, std::string val, bool chiffre): typeFait(type), valFait(val), valEstChiffre(chiffre), valFaitChiffre()
    {
        if (valEstChiffre)
        {
            valFaitChiffre = std::stoi(valFait);
        }
    }

    void affichageFait()
    {
        if (valEstChiffre)
            std::cout << "Type fait: " << typeFait << ", Valeur fait: " << valFait << ", Valeur chiffrée" << std::endl;
        else
            std::cout << "Type fait: " << typeFait << ", Valeur fait: " << valFait << ", Valeur chaine" << std::endl;

    }

    /*
     *  Getters
     */
    std::string getTypeFait() const
    {
        return typeFait;
    }

    std::string getValFait() const
    {
        return valFait;
    }

    int getValFaitChiffre() const
    {
        return valFaitChiffre;
    }

    bool estFaitChiffre()
    { return valEstChiffre; }

    bool const operator==(Fait const& b)
    {
        if ((this->typeFait == b.getTypeFait()) && (this->valFait == b.getValFait()) && (this->valFaitChiffre == b.getValFaitChiffre()))
            return true;
        else
            return false;
    }


    /*
     *  Setters
     */
    void setTypeFait(std::string s)
    {
        this->typeFait = s;
    }

    void setValFait(std::string s)
    {
        this -> valFait = s;
    }

private:
    std::string typeFait;
    std::string valFait;

    bool valEstChiffre;
    int valFaitChiffre;
};
