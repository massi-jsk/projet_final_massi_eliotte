#ifndef ALGO_TABLEAU_H
#define ALGO_TABLEAU_H

#include "structures.h"

TableauMots* creerTableau(InfoMem *infoMem);
void ajouterMotTableau(TableauMots *tab, const char *mot);
void trierTableau(TableauMots *tab);
void libererTableau(TableauMots *tab);

#endif