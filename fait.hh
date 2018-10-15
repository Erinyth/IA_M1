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
        std::cout << "Type fait: " << typeFait << ", Valeur fait: " << valFait << std::endl;
    }

    /*
     *  Getters
     */
    std::string getTypeFait()
    {
        return typeFait;
    }

    std::string getValFait()
    {
        return valFait;
    }

    int getValFaitChiffre()
    {
        return valFaitChiffre;
    }

    bool estFaitChiffre()
    { return valEstChiffre; }


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
