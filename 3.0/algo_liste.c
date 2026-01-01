#include "algo_liste.h"

ListeMots* creerListe(InfoMem *infoMem) {
    ListeMots *liste = (ListeMots*)myMalloc(sizeof(ListeMots), infoMem);
    if (!liste) return NULL;
    
    liste->tete = NULL;
    liste->nb_mots = 0;
    liste->infoMem = infoMem;
    return liste;
}

void ajouterMotListe(ListeMots *liste, const char *mot) {
    NoeudMot *courant = liste->tete;
    NoeudMot *precedent = NULL;
    
    while (courant != NULL) {
        if (monStrcmp(courant->mot, mot) == 0) {
            courant->occurences++;
            
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
    
    NoeudMot *nouveau = (NoeudMot*)myMalloc(sizeof(NoeudMot), liste->infoMem);
    int len = monStrlen(mot) + 1;
    nouveau->mot = (char*)myMalloc(len, liste->infoMem);
    monStrcpy(nouveau->mot, mot);
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
        int len = monStrlen(courant->mot) + 1;
        myFree(courant->mot, liste->infoMem, len);
        myFree(courant, liste->infoMem, sizeof(NoeudMot));
        courant = suivant;
    }
    
    myFree(liste, liste->infoMem, sizeof(ListeMots));
}

void extraireMotsListe(const char *fichier, ListeMots *liste) {
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
                ajouterMotListe(liste, buffer);
                idx = 0;
            }
        }
    }
    
    if (idx > 0) {
        buffer[idx] = '\0';
        mettreEnMinuscules(buffer);
        ajouterMotListe(liste, buffer);
    }
    
    fclose(f);
}

void afficherListe(ListeMots *liste, int nb_mots) {
    printf("\n=== RESULTATS ===\n");
    
    NoeudMot *courant = liste->tete;
    int count = 0;
    
    while (courant != NULL && (nb_mots == 0 || count < nb_mots)) {
        printf("%s : %d\n", courant->mot, courant->occurences);
        courant = courant->suivant;
        count++;
    }
    
    printf("\nNombre total de mots differents : %d\n", liste->nb_mots);
}
