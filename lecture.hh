#pragma once

#include <vector>
#include <string>
#include "bdc.hh"

/**
 * @brief lectureComplete
 * Va lire le fichier d'entrée et créer la base de connaissance associée
 */
void creationBaseConnaissance(char* fichierDonnees, baseDeConnaissance & BDC);

/**
 * @brief Va lire toutes les règles  et les ajouter à la base de connaissances
 */
void creerRegles(std::ifstream & fichierEntree, baseDeConnaissance & BDC);

/**
 * @brief lectureFait
 * Va créer tous les faits dans la base de connaissance
 */
void creerFaits(std::ifstream & fichierEntree, baseDeConnaissance & BDC);

/**
 * @brief explode
 * @param s
 * @param delim
 * @return
 * https://stackoverflow.com/questions/12966957/is-there-an-equivalent-in-c-of-phps-explode-function
 * Fonction eclatant une chaine par rapport à son délimiteur
 */
std::vector<std::string> explode(std::string const & s, char delim);
