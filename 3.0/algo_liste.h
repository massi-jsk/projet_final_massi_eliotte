#ifndef ALGO_LISTE_H
#define ALGO_LISTE_H

#include "structures.h"
#include "utils.h"

ListeMots* creerListe(InfoMem *infoMem);
void ajouterMotListe(ListeMots *liste, const char *mot);
void libererListe(ListeMots *liste);
void extraireMotsListe(const char *fichier, ListeMots *liste);
void afficherListe(ListeMots *liste, int nb_mots);

#endif