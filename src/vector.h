#ifndef VECTOR_HEADER
#define VECTOR_HEADER


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief A growable array type
 * @
 */
struct vector {
    
    void *ptr;
    size_t element_size;
    size_t capacity;
    size_t count;
};

/**
 * @brief Vector operation error
 * 
 */
enum vector_error {
    VECTOR_SUCCESS = 0,
    VECTOR_ERR_EMPTY,
    VECTOR_ERR_MEM,
    VECTOR_ERR_UNINIT,
    VECTOR_ERR_NOT_ALLOC
};


enum vector_iterator_result {
    VECTOR_ITER_SUCCESS = 0,
    VECTOR_ITER_ERR
};

/**
 * @brief Initialise an empty vector.
 * 
 * @param v Vector to be initialised.
 * @param element_size Size of one element
 * @return enum vector_error Returns VECTOR_SUCCESS if successful.
 */
enum vector_error vector_init(struct vector *v, int element_size);

/**
 * @brief Push an element at the end of the vector.
 * 
 * @param v Vector to be modified.
 * @param item Element to be pushed.
 * @return enum vector_error Returns VECTOR_SUCCESS if successful.
 */
enum vector_error vector_push(struct vector *v, const void *item);

/**
 * @brief Get an element at in index and copy it to a given location
 * 
 * @param v Vector to read from.
 * @param index Index to read at.
 * @param item Location where found element is copied.
 * @return enum vector_error Returns VECTOR_SUCCESS if successful.
 */
enum vector_error vector_get(const struct vector *v, size_t index, void *item);



/**
 * @brief Copy contents of a vector to a given address.
 * @warning Unsafe function.
 * 
 * @param v Vector to be copied from.
 * @param dest Address to copy to.
 */
void vector_copy_unsafe(const struct vector *v, void *dest);

/**
 * @brief Empties the vector.
 *
 * @par Sets count to zero, but leaves the same capacity.
 * @warning Does not free any memory.
 * @param v Vector to be emptied
 * @return enum vector_error Returns VECTOR_SUCCESS if successful.
 */
void vector_empty(struct vector *v);

/**
 * @brief Deinitialises a vector.
 * 
 * @param v Vector to be destroyed.
 */
void vector_deinit(struct vector *v);


/**
 * @brief Iterate through all elements and perform the given funtion on each one.
 * 
 * @param v Vector to iterate through
 * @param iterator Function that is triggered for each element.
 * @return enum vector_iterator_result Returns VECTOR_ITER_SUCCESS if all functions return so.
 */
enum vector_iterator_result vector_iterate(struct vector *v, enum vector_iterator_result iterator(struct vector *v, int index, void *element));


#endif