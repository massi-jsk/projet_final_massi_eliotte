typedef struct {
    size_t cumul_alloc;    // cumul de l'espace mémoire alloué
    size_t cumul_desalloc; // cumul de l'espace mémoire désalloué
    size_t max_alloc;      // pic d'allocation (diff max des deux cumuls)
} InfoMem;

// Prototypes
void myFree(void *ptr, InfoMem *infoMem, size_t old_size);

void *myMalloc(size_t size, InfoMem *infoMem) {
    if (size == 0 || infoMem == NULL) {
        return NULL;
    }
    
    void *ptr = malloc(size);
    if (ptr == NULL) {
        return NULL;
    }
    
    // Mise à jour des statistiques
    infoMem->cumul_alloc += size;
    
    // Calcul et mise à jour du pic d'allocation
    size_t current_alloc = infoMem->cumul_alloc - infoMem->cumul_desalloc;
    if (current_alloc > infoMem->max_alloc) {
        infoMem->max_alloc = current_alloc;
    }
    
    return ptr;
}

void myFree(void *ptr, InfoMem *infoMem, size_t old_size) {
    if (ptr == NULL || infoMem == NULL) {
        return;
    }
    
    free(ptr);
    
    // Mise à jour des statistiques
    infoMem->cumul_desalloc += old_size;
}

void *myRealloc(void *ptr, size_t new_size, InfoMem *infoMem, size_t old_size) {
    if (infoMem == NULL) {
        return NULL;
    }
    
    // Cas spéciaux
    if (ptr == NULL) {
        return myMalloc(new_size, infoMem);
    }
    
    if (new_size == 0) {
        myFree(ptr, infoMem, old_size);
        return NULL;
    }
    
    void *new_ptr = realloc(ptr, new_size);
    if (new_ptr == NULL) {
        return NULL;
    }
    
    // Si le pointeur a changé, cela compte comme un malloc + free complets
    if (new_ptr != ptr) {
        infoMem->cumul_alloc += new_size;
        infoMem->cumul_desalloc += old_size;
    } else {
        // Sinon, mise à jour selon la différence de taille
        if (new_size > old_size) {
            // Agrandissement : on alloue la différence
            infoMem->cumul_alloc += (new_size - old_size);
        } else if (new_size < old_size) {
            // Rétrécissement : on désalloue la différence
            infoMem->cumul_desalloc += (old_size - new_size);
        }
    }
    
    // Mise à jour du pic d'allocation
    size_t current_alloc = infoMem->cumul_alloc - infoMem->cumul_desalloc;
    if (current_alloc > infoMem->max_alloc) {
        infoMem->max_alloc = current_alloc;
    }
    
    return new_ptr;
}