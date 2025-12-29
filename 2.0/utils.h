#ifndef UTILS_H
#define UTILS_H

#include "structures.h"

void normaliserMot(char *mot);
int estCaractereValide(char c);
void extraireMots(const char *fichier, void *structure, int algo, InfoMem *infoMem);
void afficherResultats(void *structure, int algo, int nb_mots_afficher, InfoMem *infoMem);

#endif