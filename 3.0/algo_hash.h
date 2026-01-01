#ifndef ALGO_HASH_H
#define ALGO_HASH_H

#include "structures.h"
#include "utils.h"

TableHash* creerTableHash(InfoMem *infoMem);
void ajouterMotHash(TableHash *th, const char *mot);
void libererTableHash(TableHash *th);
void extraireMotsHash(const char *fichier, TableHash *th);
void afficherHash(TableHash *th, int nb_mots);

#endif