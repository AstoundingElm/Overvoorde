#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "defines.h"
#include "kmemory.h"
#include "logger.h"

#define debugBreak() __builtin_trap()

 #define KASSERT(expr)                                                \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            debugBreak();                                            \
        }                                                            \
    }

// Checks the given expression's return value against VK_SUCCESS.
#define VK_CHECK(expr)               \
    {                                \
        KASSERT(expr == VK_SUCCESS); \
    }

    #define KASSERT_MSG(expr, message)                                        \
    {                                                                     \
        if (expr) {                                                       \
        } else {                                                          \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            debugBreak();                                                 \
        }                                                                 \
    }

void* _darray_create(long unsigned int length, __UINT64_TYPE__ stride);
void _darray_destroy(void* array);

long unsigned int _darray_field_get(void* array, long unsigned int field);
void _darray_field_set(void* array, long unsigned int field, long unsigned int value);

void* _darray_resize(void* array);

void* _darray_push(void* array, const void* value_ptr);
void _darray_pop(void* array, void* dest);

void* _darray_pop_at(void* array, long unsigned int index, void* dest);
void* _darray_insert_at(void* array, long unsigned int index, void* value_ptr);

#define DARRAY_DEFAULT_CAPACITY 1
#define DARRAY_RESIZE_FACTOR 2

#define darray_create(type) \
    _darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type))

#define darray_reserve(type, capacity) \
    _darray_create(capacity, sizeof(type))

#define darray_destroy(array) _darray_destroy(array);

#define darray_push(array, value)           \
    {                                       \
        typeof(value) temp = value;         \
        array = _darray_push(array, &temp); \
    }
// NOTE: could use __auto_type for temp above, but intellisense
// for VSCode flags it as an unknown type. typeof() seems to
// work just fine, though. Both are GNU extensions.

#define darray_pop(array, value_ptr) \
    _darray_pop(array, value_ptr)

#define darray_insert_at(array, index, value)           \
    {                                                   \
        typeof(value) temp = value;                     \
        array = _darray_insert_at(array, index, &temp); \
    }

#define darray_pop_at(array, index, value_ptr) \
    _darray_pop_at(array, index, value_ptr)

#define darray_clear(array) \
    _darray_field_set(array, DARRAY_LENGTH, 0)

#define darray_capacity(array) \
    _darray_field_get(array, DARRAY_CAPACITY)

#define darray_length(array) \
    _darray_field_get(array, DARRAY_LENGTH)

#define darray_stride(array) \
    _darray_field_get(array, DARRAY_STRIDE)

#define darray_length_set(array, value) \
    _darray_field_set(array, DARRAY_LENGTH, value)
    
