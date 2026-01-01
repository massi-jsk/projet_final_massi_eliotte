#ifndef ALGO_TABLEAU_H
#define ALGO_TABLEAU_H

#include "structures.h"
#include "utils.h"

TableauMots* creerTableau(InfoMem *infoMem);
void ajouterMotTableau(TableauMots *tab, const char *mot);
void trierTableau(TableauMots *tab);
void libererTableau(TableauMots *tab);
void extraireMotsTableau(const char *fichier, TableauMots *tab);
void afficherTableau(TableauMots *tab, int nb_mots);

#endif