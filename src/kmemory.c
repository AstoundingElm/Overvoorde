#include "kmemory.h"

 void * kallocate(long unsigned int size, memory_tag tag) {
    // TODO: Memory alignment
    void* block = malloc(size);
    memset(block, 0, size);
    return block;
}

 void kfree(void* block, long unsigned int size, memory_tag tag) {
    // TODO: Memory alignment
    free(block);
}

 void* kzero_memory(void* block, long unsigned int size) {
    return memset(block, 0, size);
}

 void* kcopy_memory(void* dest, const void* source, long unsigned int size) {
    return memcpy(dest, source, size);
}

 void* kset_memory(void* dest, int value, long unsigned int size) {
    return memset(dest, value, size);
}