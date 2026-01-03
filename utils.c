#include "utils.h"
#include "algo_tableau.h"
#include "algo_liste.h"
#include "algo_hash.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void normaliserMot(char *mot) {
    for (int i = 0; mot[i]; i++) {
        mot[i] = tolower(mot[i]);
    }
}

int estCaractereValide(char c) {
    return isalpha(c) || c == '-';
}

void extraireMots(const char *fichier, void *structure, int algo, InfoMem *infoMem) {
    FILE *f = fopen(fichier, "r");
    if (!f) {
        printf("Erreur: impossible d'ouvrir le fichier %s\n", fichier);
        return;
    }
    
    char buffer[256];
    int idx = 0;
    int c;
    
    while ((c = fgetc(f)) != EOF) {
        if (estCaractereValide(c)) {
            if (idx < 255) {
                buffer[idx++] = c;
            }
        } else {
            if (idx > 0) {
                buffer[idx] = '\0';
                normaliserMot(buffer);
                
                switch(algo) {
                    case 1:
                        ajouterMotTableau((TableauMots*)structure, buffer);
                        break;
                    case 2:
                        ajouterMotListe((ListeMots*)structure, buffer);
                        break;
                    case 3:
                        ajouterMotHash((TableHash*)structure, buffer);
                        break;
                }
                
                idx = 0;
            }
        }
    }
    
    if (idx > 0) {
        buffer[idx] = '\0';
        normaliserMot(buffer);
        
        switch(algo) {
            case 1:
                ajouterMotTableau((TableauMots*)structure, buffer);
                break;
            case 2:
                ajouterMotListe((ListeMots*)structure, buffer);
                break;
            case 3:
                ajouterMotHash((TableHash*)structure, buffer);
                break;
        }
    }
    
    fclose(f);
}

void afficherResultats(void *structure, int algo, int nb_mots_afficher, InfoMem *infoMem) {
    printf("\n=== Résultats ===\n");
    
    if (algo == 1) {
        TableauMots *tab = (TableauMots*)structure;
        trierTableau(tab);
        
        int limite = (nb_mots_afficher > 0 && nb_mots_afficher < tab->nb_mots) 
                     ? nb_mots_afficher : tab->nb_mots;
        
        for (int i = 0; i < limite; i++) {
            printf("%s : %d\n", tab->mots[i].mot, tab->mots[i].occurences);
        }
        
        printf("\nNombre total de mots différents : %d\n", tab->nb_mots);
        
    } else if (algo == 2) {
        ListeMots *liste = (ListeMots*)structure;
        NoeudMot *courant = liste->tete;
        int count = 0;
        
        while (courant != NULL && (nb_mots_afficher == 0 || count < nb_mots_afficher)) {
            printf("%s : %d\n", courant->mot, courant->occurences);
            courant = courant->suivant;
            count++;
        }
        
        printf("\nNombre total de mots différents : %d\n", liste->nb_mots);
        
    } else if (algo == 3) {
        TableHash *th = (TableHash*)structure;
        MotCompteur *tab = tableHashVersTableau(th);
        
        int limite = (nb_mots_afficher > 0 && nb_mots_afficher < th->nb_mots) 
                     ? nb_mots_afficher : th->nb_mots;
        
        for (int i = 0; i < limite; i++) {
            printf("%s : %d\n", tab[i].mot, tab[i].occurences);
        }
        
        printf("\nNombre total de mots différents : %d\n", th->nb_mots);
        
        myFree(tab, infoMem, th->nb_mots * sizeof(MotCompteur));
    }
    
    printf("\n=== Statistiques mémoire ===\n");
    printf("Mémoire allouée : %zu octets\n", infoMem->cumul_alloc);
    printf("Mémoire désallouée : %zu octets\n", infoMem->cumul_desalloc);
    printf("Pic d'allocation : %zu octets\n", infoMem->max_alloc);
    printf("Mémoire actuellement utilisée : %zu octets\n", 
           infoMem->cumul_alloc - infoMem->cumul_desalloc);
}