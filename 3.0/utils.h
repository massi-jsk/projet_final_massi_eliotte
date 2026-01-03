#ifndef UTILS_H
#define UTILS_H

#include "structures.h"

int monStrlen(const char *s);
void monStrcpy(char *dest, const char *src);
int monStrcmp(const char *s1, const char *s2);

// Fonctions utilitaires
int estLettre(char c);
void mettreEnMinuscules(char *mot);

#endif