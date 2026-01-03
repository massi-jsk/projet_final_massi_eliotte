#include "utils.h"

// Calculer la longueur d'une chaîne (remplace strlen)
int monStrlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

// Copier une chaîne (remplace strcpy)
void monStrcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Comparer deux chaînes (remplace strcmp)
// Retourne 0 si identiques, sinon différent de 0
int monStrcmp(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

// Vérifie si c'est une lettre ou un tiret
int estLettre(char c) {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           (c == '-');
}

// Met un mot en minuscules
void mettreEnMinuscules(char *mot) {
    int i;
    for (i = 0; mot[i] != '\0'; i++) {
        if (mot[i] >= 'A' && mot[i] <= 'Z') {
            mot[i] = mot[i] + 32;
        }
    }
}