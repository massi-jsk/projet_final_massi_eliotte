#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "gererMem.h"

typedef struct {
    char *mot;
    int occurences;
} MotCompteur;

typedef struct {
    MotCompteur *mots;
    int nb_mots;
    int capacite;
    InfoMem *infoMem;
} TableauMots;

typedef struct NoeudMot {
    char *mot;
    int occurences;
    struct NoeudMot *suivant;
} NoeudMot;

typedef struct {
    NoeudMot *tete;
    int nb_mots;
    InfoMem *infoMem;
} ListeMots;

#define TAILLE_TABLE 1000

typedef struct EntreeHash {
    char *mot;
    int occurences;
    struct EntreeHash *suivant;
} EntreeHash;

typedef struct {
    EntreeHash **table;
    int nb_mots;
    InfoMem *infoMem;
} TableHash;

#endif