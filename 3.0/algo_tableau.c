#include "algo_tableau.h"

TableauMots* creerTableau(InfoMem *infoMem) {
    TableauMots *tab = (TableauMots*)myMalloc(sizeof(TableauMots), infoMem);
    if (!tab) return NULL;
    
    tab->capacite = 100;
    tab->nb_mots = 0;
    tab->infoMem = infoMem;
    tab->mots = (MotCompteur*)myMalloc(tab->capacite * sizeof(MotCompteur), infoMem);
    
    if (!tab->mots) {
        myFree(tab, infoMem, sizeof(TableauMots));
        return NULL;
    }
    
    return tab;
}

void ajouterMotTableau(TableauMots *tab, const char *mot) {
    int i;
    for (i = 0; i < tab->nb_mots; i++) {
        if (monStrcmp(tab->mots[i].mot, mot) == 0) {
            tab->mots[i].occurences++;
            return;
        }
    }
    
    if (tab->nb_mots >= tab->capacite) {
        int old_cap = tab->capacite;
        tab->capacite *= 2;
        tab->mots = (MotCompteur*)myRealloc(tab->mots, 
                                            tab->capacite * sizeof(MotCompteur),
                                            tab->infoMem,
                                            old_cap * sizeof(MotCompteur));
    }
    
    int len = monStrlen(mot) + 1;
    tab->mots[tab->nb_mots].mot = (char*)myMalloc(len, tab->infoMem);
    monStrcpy(tab->mots[tab->nb_mots].mot, mot);
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
    
    int i;
    for (i = 0; i < tab->nb_mots; i++) {
        int len = monStrlen(tab->mots[i].mot) + 1;
        myFree(tab->mots[i].mot, tab->infoMem, len);
    }
    
    myFree(tab->mots, tab->infoMem, tab->capacite * sizeof(MotCompteur));
    myFree(tab, tab->infoMem, sizeof(TableauMots));
}

void extraireMotsTableau(const char *fichier, TableauMots *tab) {
    FILE *f = fopen(fichier, "r");
    if (!f) {
        printf("ERREUR: Impossible d'ouvrir %s\n", fichier);
        return;
    }
    
    char buffer[256];
    int idx = 0;
    int c;
    
    while ((c = fgetc(f)) != EOF) {
        if (estLettre(c)) {
            if (idx < 255) {
                buffer[idx] = c;
                idx++;
            }
        } else {
            if (idx > 0) {
                buffer[idx] = '\0';
                mettreEnMinuscules(buffer);
                ajouterMotTableau(tab, buffer);
                idx = 0;
            }
        }
    }
    
    if (idx > 0) {
        buffer[idx] = '\0';
        mettreEnMinuscules(buffer);
        ajouterMotTableau(tab, buffer);
    }
    
    fclose(f);
}

void afficherTableau(TableauMots *tab, int nb_mots) {
    trierTableau(tab);
    
    int limite = nb_mots;
    if (limite == 0 || limite > tab->nb_mots) {
        limite = tab->nb_mots;
    }
    
    printf("\n=== RESULTATS ===\n");
    int i;
    for (i = 0; i < limite; i++) {
        printf("%s : %d\n", tab->mots[i].mot, tab->mots[i].occurences);
    }
    printf("\nNombre total de mots differents : %d\n", tab->nb_mots);
}