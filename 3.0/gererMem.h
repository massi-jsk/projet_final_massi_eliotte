#ifndef GERER_MEM_H
#define GERER_MEM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long cumul_alloc;      // Total alloué
    unsigned long cumul_desalloc;   // Total libéré
    unsigned long max_alloc;        // Pic d'utilisation
} InfoMem;

// Nos fonctions de gestion mémoire
void* myMalloc(unsigned long size, InfoMem *infoMem);
void* myRealloc(void *ptr, unsigned long new_size, InfoMem *infoMem, unsigned long old_size);
void myFree(void *ptr, InfoMem *infoMem, unsigned long old_size);

#endif

