#include "algo_tableau.h"
#include <string.h>
#include <stdlib.h>

TableauMots* creerTableau(InfoMem *infoMem) {
    TableauMots *tab = myMalloc(sizeof(TableauMots), infoMem);
    if (!tab) return NULL;
    
    tab->capacite = 100;
    tab->nb_mots = 0;
    tab->infoMem = infoMem;
    tab->mots = myMalloc(tab->capacite * sizeof(MotCompteur), infoMem);
    
    if (!tab->mots) {
        myFree(tab, infoMem, sizeof(TableauMots));
        return NULL;
    }
    
    return tab;
}

void ajouterMotTableau(TableauMots *tab, const char *mot) {
    // Recherche si le mot existe déjà
    for (int i = 0; i < tab->nb_mots; i++) {
        if (strcmp(tab->mots[i].mot, mot) == 0) {
            tab->mots[i].occurences++;
            return;
        }
    }
    
    // Le mot n'existe pas, on l'ajoute
    if (tab->nb_mots >= tab->capacite) {
        int old_cap = tab->capacite;
        tab->capacite *= 2;
        tab->mots = myRealloc(tab->mots, 
                             tab->capacite * sizeof(MotCompteur),
                             tab->infoMem,
                             old_cap * sizeof(MotCompteur));
    }
    
    int len = strlen(mot) + 1;
    tab->mots[tab->nb_mots].mot = myMalloc(len, tab->infoMem);
    strcpy(tab->mots[tab->nb_mots].mot, mot);
    tab->mots[tab->nb_mots].occurences = 1;
    tab->nb_mots++;
}

int comparerOccurences(const void *a, const void *b) {
    MotCompteur *m1 = (MotCompteur*)a;
    MotCompteur *m2 = (MotCompteur*)b;
    return m2->occurences - m1->occurences;
}

void trierTableau(TableauMots *tab) {
    qsort(tab->mots, tab->nb_mots, sizeof(MotCompteur), comparerOccurences);
}

void libererTableau(TableauMots *tab) {
    if (!tab) return;
    
    for (int i = 0; i < tab->nb_mots; i++) {
        int len = strlen(tab->mots[i].mot) + 1;
        myFree(tab->mots[i].mot, tab->infoMem, len);
    }
    
    myFree(tab->mots, tab->infoMem, tab->capacite * sizeof(MotCompteur));
    myFree(tab, tab->infoMem, sizeof(TableauMots));
}