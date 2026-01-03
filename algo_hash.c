#include "algo_hash.h"
#include <string.h>
#include <stdlib.h>

unsigned int hash(const char *mot) {
    unsigned int h = 0;
    while (*mot) {
        h = h * 31 + *mot;
        mot++;
    }
    return h % TAILLE_TABLE;
}

TableHash* creerTableHash(InfoMem *infoMem) {
    TableHash *th = myMalloc(sizeof(TableHash), infoMem);
    if (!th) return NULL;
    
    th->table = myMalloc(TAILLE_TABLE * sizeof(EntreeHash*), infoMem);
    if (!th->table) {
        myFree(th, infoMem, sizeof(TableHash));
        return NULL;
    }
    
    for (int i = 0; i < TAILLE_TABLE; i++) {
        th->table[i] = NULL;
    }
    
    th->nb_mots = 0;
    th->infoMem = infoMem;
    return th;
}

void ajouterMotHash(TableHash *th, const char *mot) {
    unsigned int index = hash(mot);
    EntreeHash *courant = th->table[index];
    
    while (courant != NULL) {
        if (strcmp(courant->mot, mot) == 0) {
            courant->occurences++;
            return;
        }
        courant = courant->suivant;
    }
    
    EntreeHash *nouvelle = myMalloc(sizeof(EntreeHash), th->infoMem);
    int len = strlen(mot) + 1;
    nouvelle->mot = myMalloc(len, th->infoMem);
    strcpy(nouvelle->mot, mot);
    nouvelle->occurences = 1;
    nouvelle->suivant = th->table[index];
    th->table[index] = nouvelle;
    th->nb_mots++;
}

int comparerOccurencesHash(const void *a, const void *b) {
    MotCompteur *m1 = (MotCompteur*)a;
    MotCompteur *m2 = (MotCompteur*)b;
    return m2->occurences - m1->occurences;
}

MotCompteur* tableHashVersTableau(TableHash *th) {
    MotCompteur *tab = myMalloc(th->nb_mots * sizeof(MotCompteur), th->infoMem);
    int idx = 0;
    
    for (int i = 0; i < TAILLE_TABLE; i++) {
        EntreeHash *courant = th->table[i];
        while (courant != NULL) {
            tab[idx].mot = courant->mot;
            tab[idx].occurences = courant->occurences;
            idx++;
            courant = courant->suivant;
        }
    }
    
    qsort(tab, th->nb_mots, sizeof(MotCompteur), comparerOccurencesHash);
    return tab;
}

void libererTableHash(TableHash *th) {
    if (!th) return;
    
    for (int i = 0; i < TAILLE_TABLE; i++) {
        EntreeHash *courant = th->table[i];
        while (courant != NULL) {
            EntreeHash *suivant = courant->suivant;
            int len = strlen(courant->mot) + 1;
            myFree(courant->mot, th->infoMem, len);
            myFree(courant, th->infoMem, sizeof(EntreeHash));
            courant = suivant;
        }
    }
    
    myFree(th->table, th->infoMem, TAILLE_TABLE * sizeof(EntreeHash*));
    myFree(th, th->infoMem, sizeof(TableHash));
}