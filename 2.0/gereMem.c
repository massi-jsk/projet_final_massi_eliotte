#include "gererMem.h"
#include <stdlib.h>

void* myMalloc(size_t size, InfoMem *infoMem) {
    if (size == 0 || infoMem == NULL) {
        return NULL;
    }
    
    void *ptr = malloc(size);
    if (ptr == NULL) {
        return NULL;
    }
    
    infoMem->cumul_alloc += size;
    
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
    infoMem->cumul_desalloc += old_size;
}

void* myRealloc(void *ptr, size_t new_size, InfoMem *infoMem, size_t old_size) {
    if (infoMem == NULL) {
        return NULL;
    }
    
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
    
    if (new_ptr != ptr) {
        infoMem->cumul_alloc += new_size;
        infoMem->cumul_desalloc += old_size;
    } else {
        if (new_size > old_size) {
            infoMem->cumul_alloc += (new_size - old_size);
        } else if (new_size < old_size) {
            infoMem->cumul_desalloc += (old_size - new_size);
        }
    }
    
    size_t current_alloc = infoMem->cumul_alloc - infoMem->cumul_desalloc;
    if (current_alloc > infoMem->max_alloc) {
        infoMem->max_alloc = current_alloc;
    }
    
    return new_ptr;
}