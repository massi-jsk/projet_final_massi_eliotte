#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gererMem.h"
#include "structures.h"
#include "algo_tableau.h"
#include "algo_liste.h"
#include "algo_hash.h"
#include "utils.h"

int main(void) {
    char fichier[256];
    int algo;
    int nb_mots_afficher;

    /* Saisie du fichier */
    printf("Entrez le nom du fichier : ");
    fgets(fichier, sizeof(fichier), stdin);
    /* Supprimer le \n */
    fichier[strcspn(fichier, "\n")] = '\0';

    /* Choix de l'algorithme */
    printf("\nChoisissez l'algorithme :\n");
    printf("  1 - Tableau non trie\n");
    printf("  2 - Liste chainee triee\n");
    printf("  3 - Table de hachage\n");
    printf("Votre choix : ");
    scanf("%d", &algo);

    if (algo < 1 || algo > 3) {
        printf("Erreur : algorithme invalide\n");
        return 1;
    }

    /* Nombre de mots à afficher */
    printf("Nombre de mots a afficher (0 = tous) : ");
    scanf("%d", &nb_mots_afficher);

    InfoMem infoMem = {0, 0, 0};
    void *structure = NULL;

    clock_t debut = clock();

    switch (algo) {
        case 1:
            structure = creerTableau(&infoMem);
            printf("\nAlgorithme : Tableau non trié\n");
            break;
        case 2:
            structure = creerListe(&infoMem);
            printf("\nAlgorithme : Liste chaînée triée\n");
            break;
        case 3:
            structure = creerTableHash(&infoMem);
            printf("\nAlgorithme : Table de hachage\n");
            break;
    }

    if (!structure) {
        printf("Erreur : impossible de créer la structure\n");
        return 1;
    }

    extraireMots(fichier, structure, algo, &infoMem);

    clock_t fin = clock();
    double temps = (double)(fin - debut) / CLOCKS_PER_SEC;

    afficherResultats(structure, algo, nb_mots_afficher, &infoMem);

    printf("\n=== Performance ===\n");
    printf("Temps d'exécution : %.6f secondes\n", temps);

    switch (algo) {
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
