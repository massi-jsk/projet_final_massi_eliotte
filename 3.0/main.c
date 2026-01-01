#include <stdio.h>
#include <stdlib.h>
#include "gererMem.h"
#include "structures.h"
#include "algo_tableau.h"
#include "algo_liste.h"
#include "algo_hash.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <fichier> <algorithme> [nb_mots]\n", argv[0]);
        printf("\nAlgorithmes:\n");
        printf("  1 - Tableau dynamique\n");
        printf("  2 - Liste chainee triee\n");
        printf("  3 - Table de hachage\n");
        return 1;
    }
    
    char *fichier = argv[1];
    int algo = atoi(argv[2]);
    int nb_mots = 0;
    if (argc > 3) {
        nb_mots = atoi(argv[3]);
    }
    
    if (algo < 1 || algo > 3) {
        printf("ERREUR: L'algorithme doit etre 1, 2 ou 3\n");
        return 1;
    }
    
    InfoMem infoMem;
    infoMem.cumul_alloc = 0;
    infoMem.cumul_desalloc = 0;
    infoMem.max_alloc = 0;
    
    printf("\n=== DEBUT ===\n");
    printf("Fichier: %s\n", fichier);
    printf("Algorithme: %d\n", algo);
    
    if (algo == 1) {
        TableauMots *tab = creerTableau(&infoMem);
        extraireMotsTableau(fichier, tab);
        afficherTableau(tab, nb_mots);
        libererTableau(tab);
    } 
    else if (algo == 2) {
        ListeMots *liste = creerListe(&infoMem);
        extraireMotsListe(fichier, liste);
        afficherListe(liste, nb_mots);
        libererListe(liste);
    }
    else if (algo == 3) {
        TableHash *th = creerTableHash(&infoMem);
        extraireMotsHash(fichier, th);
        afficherHash(th, nb_mots);
        libererTableHash(th);
    }
    
    printf("\n=== MEMOIRE ===\n");
    printf("Allouee    : %lu octets\n", infoMem.cumul_alloc);
    printf("Liberee    : %lu octets\n", infoMem.cumul_desalloc);
    printf("Pic        : %lu octets\n", infoMem.max_alloc);
    
    return 0;
}