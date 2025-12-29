#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "gererMem.h"

// Structure commune pour stocker mot + occurrences
typedef struct {
    char *mot;
    int occurences;
} MotCompteur;

// ALGORITHME 1: Tableau dynamique
typedef struct {
    MotCompteur *mots;
    int nb_mots;
    int capacite;
    InfoMem *infoMem;
} TableauMots;

// ALGORITHME 2: Liste chaînée
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

// ALGORITHME 3: Table de hachage
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