#include "algo_hash.h"

unsigned int hash(const char *mot) {
    unsigned int h = 0;
    while (*mot) {
        h = h * 31 + (*mot);
        mot++;
    }
    return h % TAILLE_TABLE;
}

TableHash* creerTableHash(InfoMem *infoMem) {
    TableHash *th = (TableHash*)myMalloc(sizeof(TableHash), infoMem);
    if (!th) return NULL;
    
    th->table = (EntreeHash**)myMalloc(TAILLE_TABLE * sizeof(EntreeHash*), infoMem);
    if (!th->table) {
        myFree(th, infoMem, sizeof(TableHash));
        return NULL;
    }
    
    int i;
    for (i = 0; i < TAILLE_TABLE; i++) {
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
        if (monStrcmp(courant->mot, mot) == 0) {
            courant->occurences++;
            return;
        }
        courant = courant->suivant;
    }
    
    EntreeHash *nouvelle = (EntreeHash*)myMalloc(sizeof(EntreeHash), th->infoMem);
    int len = monStrlen(mot) + 1;
    nouvelle->mot = (char*)myMalloc(len, th->infoMem);
    monStrcpy(nouvelle->mot, mot);
    nouvelle->occurences = 1;
    nouvelle->suivant = th->table[index];
    th->table[index] = nouvelle;
    th->nb_mots++;
}

void libererTableHash(TableHash *th) {
    if (!th) return;
    
    int i;
    for (i = 0; i < TAILLE_TABLE; i++) {
        EntreeHash *courant = th->table[i];
        while (courant != NULL) {
            EntreeHash *suivant = courant->suivant;
            int len = monStrlen(courant->mot) + 1;
            myFree(courant->mot, th->infoMem, len);
            myFree(courant, th->infoMem, sizeof(EntreeHash));
            courant = suivant;
        }
    }
    
    myFree(th->table, th->infoMem, TAILLE_TABLE * sizeof(EntreeHash*));
    myFree(th, th->infoMem, sizeof(TableHash));
}

void extraireMotsHash(const char *fichier, TableHash *th) {
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
                ajouterMotHash(th, buffer);
                idx = 0;
            }
        }
    }
    
    if (idx > 0) {
        buffer[idx] = '\0';
        mettreEnMinuscules(buffer);
        ajouterMotHash(th, buffer);
    }
    
    fclose(f);
}

int comparerHash(const void *a, const void *b) {
    MotCompteur *m1 = (MotCompteur*)a;
    MotCompteur *m2 = (MotCompteur*)b;
    return m2->occurences - m1->occurences;
}

void afficherHash(TableHash *th, int nb_mots) {
    MotCompteur *tab = (MotCompteur*)myMalloc(th->nb_mots * sizeof(MotCompteur), th->infoMem);
    int idx = 0;
    
    int i;
    for (i = 0; i < TAILLE_TABLE; i++) {
        EntreeHash *courant = th->table[i];
        while (courant != NULL) {
            tab[idx].mot = courant->mot;
            tab[idx].occurences = courant->occurences;
            idx++;
            courant = courant->suivant;
        }
    }
    
    qsort(tab, th->nb_mots, sizeof(MotCompteur), comparerHash);
    
    int limite = nb_mots;
    if (limite == 0 || limite > th->nb_mots) {
        limite = th->nb_mots;
    }
    
    printf("\n=== RESULTATS ===\n");
    for (i = 0; i < limite; i++) {
        printf("%s : %d\n", tab[i].mot, tab[i].occurences);
    }
    printf("\nNombre total de mots differents : %d\n", th->nb_mots);
    
    myFree(tab, th->infoMem, th->nb_mots * sizeof(MotCompteur));
}