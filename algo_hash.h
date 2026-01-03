#ifndef ALGO_HASH_H
#define ALGO_HASH_H

#include "structures.h"

TableHash* creerTableHash(InfoMem *infoMem);
void ajouterMotHash(TableHash *th, const char *mot);
MotCompteur* tableHashVersTableau(TableHash *th);
void libererTableHash(TableHash *th);

#endif