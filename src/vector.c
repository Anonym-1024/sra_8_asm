#include "vector.h"


enum vector_error vector_init(struct vector *v, int element_size) {
    v->element_size = element_size;
    v->capacity = 10;
    v->count = 0;
    v->ptr = malloc(element_size * v->capacity);
    
    if (v->ptr == NULL) {
        return VECTOR_ERR_MEM;
    }
    return VECTOR_SUCCESS;
}

enum vector_error vector_push(struct vector *v, const void *item) {
    if (v->ptr == NULL) {
        return VECTOR_ERR_UNINIT;
    }
    
    if (v->count >= v->capacity) {
        v->capacity *= 2;
        void *tmp = realloc(v->ptr, v->element_size * v->capacity);
        if (tmp == NULL) {
            return VECTOR_ERR_MEM;
        }
        v->ptr = tmp;
    }

    memcpy(v->ptr + v->element_size * v->count, item, v->element_size);
    v->count++;

    return VECTOR_SUCCESS;
}

enum vector_error vector_get(const struct vector *v, size_t index, void *item) {
    if (v->ptr == NULL) {
        return VECTOR_ERR_UNINIT;
    }

    if (index >= v->count) {
        return VECTOR_ERR_NOT_ALLOC;
    }

    memcpy(item, v->ptr + v->element_size * index, v->element_size);

    return VECTOR_SUCCESS;
}

void vector_copy_unsafe(const struct vector *v, void *dest) {
    memcpy(dest, v->ptr, v->count * v->element_size);
}

void vector_empty(struct vector *v) {
    v->count = 0;
}

void vector_deinit(struct vector *v) {
    free(v->ptr);
    v->ptr = NULL;
    v->capacity = 0;
    v->count = 0;
}

enum vector_iterator_result vector_iterate(struct vector *v, enum vector_iterator_result iterator(struct vector *v, int index, void *element)) {
    enum vector_iterator_result error = VECTOR_ITER_SUCCESS;
    for (int i = 0; i < v->count; i++) {
        error |= iterator(v, i, v->ptr + (i * v->element_size));
    }

    return error;
}
