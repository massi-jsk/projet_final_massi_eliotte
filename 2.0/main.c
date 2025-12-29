#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gererMem.h"
#include "structures.h"
#include "algo_tableau.h"
#include "algo_liste.h"
#include "algo_hash.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <fichier> <algorithme> [nb_mots]\n", argv[0]);
        printf("Algorithmes:\n");
        printf("  1 - Tableau non trié\n");
        printf("  2 - Liste chaînée triée\n");
        printf("  3 - Table de hachage\n");
        return 1;
    }
    
    const char *fichier = argv[1];
    int algo = atoi(argv[2]);
    int nb_mots_afficher = (argc > 3) ? atoi(argv[3]) : 0;
    
    if (algo < 1 || algo > 3) {
        printf("Erreur: algorithme doit être 1, 2 ou 3\n");
        return 1;
    }
    
    InfoMem infoMem = {0, 0, 0};
    void *structure = NULL;
    
    clock_t debut = clock();
    
    switch(algo) {
        case 1:
            structure = creerTableau(&infoMem);
            printf("Algorithme: Tableau non trié\n");
            break;
        case 2:
            structure = creerListe(&infoMem);
            printf("Algorithme: Liste chaînée triée\n");
            break;
        case 3:
            structure = creerTableHash(&infoMem);
            printf("Algorithme: Table de hachage\n");
            break;
    }
    
    if (!structure) {
        printf("Erreur: impossible de créer la structure\n");
        return 1;
    }
    
    extraireMots(fichier, structure, algo, &infoMem);
    
    clock_t fin = clock();
    double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
    
    afficherResultats(structure, algo, nb_mots_afficher, &infoMem);
    
    printf("\n=== Performance ===\n");
    printf("Temps d'exécution : %.6f secondes\n", temps);
    
    switch(algo) {
        case 1:
            libererTableau((TableauMots*)structure);
            break;
        case 2:
            libererListe((ListeMots*)structure);
            break;
        case 3:
            libererTableHash((TableHash*)structure);
            break;
    }
    
    return 0;
}