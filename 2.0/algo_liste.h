#ifndef ALGO_LISTE_H
#define ALGO_LISTE_H

#include "structures.h"

ListeMots* creerListe(InfoMem *infoMem);
void ajouterMotListe(ListeMots *liste, const char *mot);
void libererListe(ListeMots *liste);

#endif