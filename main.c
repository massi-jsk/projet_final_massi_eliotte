#include <stdio.h>
#include <stdlib.h>
#include<string.h>
 // prendre en argument un ficheir
 int prend_f(FILE*fichier){
  FILE*f=fichier;
  f=fopen("fichier","r");
  if(f==NULL){ printf("fichier invalide \n");
  return -1;
 }
 return 0;
 fclose(f);
 }

 int nombre_occurence( char*fichier,char* mot){
    FILE *f = fopen(fichier, "r");

    if (!f) return -1;

    int cpt = 0;
    char buffer[256];

    while (fscanf(f, "%255s", buffer) == 1) {
        if (strcmp(buffer, mot) == 0)
            cpt++;
    }

    fclose(f);
    return cpt;
}
void affichage(char*fichier){
 FILE*f=fopen(fichier,"r");
if (!f) return;
int nb;
char cart[256];
char mots[1000][50];   // max 1000 mots, chaque mot max 50 chars
int nbMots = 0;
    while (fgets(cart, sizeof(cart), f)) {
        char *mot = strtok(cart, " \t\n");
        while (mot != NULL) {

        if(f!=NULL){
        char cart[256];
            int dejaVu = 0;
            for (int i = 0; i < nbMots; i++) {
                if (strcmp(mot, mots[i]) == 0) {
                    dejaVu = 1;
             break;
                }
            }

            if (!dejaVu) {
                nb=nombre_occurence(fichier,mot);
                printf("Mot : %s nombre d'occurence:%d\n", mot,nb);
                strcpy(mots[nbMots++], mot);
            }

            mot = strtok(NULL, " \t\n");
        }
    }
 fclose(f);
 }
}
void choix(char*fichier,int x){
printf("Entrer le nombre de mots a afficher svp \n");
scanf("%d",&x);
FILE*f=fopen(fichier,"r");
if (!f) return;
char cart[256];
char mots[1000][50];   // max 1000 mots, chaque mot max 50 chars
int nbMots = 0;
    while (fgets(cart, sizeof(cart), f) && nbMots<x) {
        char *mot = strtok(cart, " \t\n");
        while (mot != NULL && nbMots<x) {
        if(f!=NULL){
        char cart[256];
            int dejaVu = 0;
            for (int i = 0; i < nbMots; i++) {
                if (strcmp(mot, mots[i]) == 0) {
                    dejaVu = 1;
             break;
                }
            }

            if (!dejaVu) {
                printf("Mot : %s \n", mot);
                strcpy(mots[nbMots++], mot);
            }

            mot = strtok(NULL, " \t\n");
        }
    }
 fclose(f);
 }

}
int main()

{  choix("exemple.txt",2);
   // int m=nombre_occurence("exemple.txt","akka");
    //printf("%d\n",m);
    return 0;
}
