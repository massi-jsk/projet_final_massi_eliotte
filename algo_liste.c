#include "algo_liste.h"
#include <string.h>
#include <stdlib.h>

ListeMots* creerListe(InfoMem *infoMem) {
    ListeMots *liste = myMalloc(sizeof(ListeMots), infoMem);
    if (!liste) return NULL;
    
    liste->tete = NULL;
    liste->nb_mots = 0;
    liste->infoMem = infoMem;
    return liste;
}

void ajouterMotListe(ListeMots *liste, const char *mot) {
    NoeudMot *courant = liste->tete;
    NoeudMot *precedent = NULL;
    
    // Recherche du mot
    while (courant != NULL) {
        if (strcmp(courant->mot, mot) == 0) {
            courant->occurences++;
            
            // Réorganiser pour maintenir l'ordre décroissant
            while (precedent != NULL && precedent->occurences < courant->occurences) {
                char *tmp_mot = precedent->mot;
                int tmp_occ = precedent->occurences;
                precedent->mot = courant->mot;
                precedent->occurences = courant->occurences;
                courant->mot = tmp_mot;
                courant->occurences = tmp_occ;
                
                courant = precedent;
                NoeudMot *temp = liste->tete;
                precedent = NULL;
                while (temp != NULL && temp->suivant != courant) {
                    precedent = temp;
                    temp = temp->suivant;
                }
            }
            return;
        }
        
        precedent = courant;
        courant = courant->suivant;
    }
    
    // Le mot n'existe pas, on l'ajoute
    NoeudMot *nouveau = myMalloc(sizeof(NoeudMot), liste->infoMem);
    int len = strlen(mot) + 1;
    nouveau->mot = myMalloc(len, liste->infoMem);
    strcpy(nouveau->mot, mot);
    nouveau->occurences = 1;
    nouveau->suivant = NULL;
    
    if (precedent == NULL) {
        liste->tete = nouveau;
    } else {
        precedent->suivant = nouveau;
    }
    
    liste->nb_mots++;
}

void libererListe(ListeMots *liste) {
    if (!liste) return;
    
    NoeudMot *courant = liste->tete;
    while (courant != NULL) {
        NoeudMot *suivant = courant->suivant;
        int len = strlen(courant->mot) + 1;
        myFree(courant->mot, liste->infoMem, len);
        myFree(courant, liste->infoMem, sizeof(NoeudMot));
        courant = suivant;
    }
    
    myFree(liste, liste->infoMem, sizeof(ListeMots));
}