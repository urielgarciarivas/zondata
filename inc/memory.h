/*
 * MIT License
 *
 * Copyright (c) 2024 Uriel García Rivas
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * https://github.com/zoningorg/zondata/blob/main/LICENSE
 */

#ifndef __ZNG_MEMORY_H__
#define __ZNG_MEMORY_H__

#include <stdio.h>
#include <stdlib.h>

#define ALLOCATE(__ZNG_TYPE, __ZNG_POINTER)                    \
do {                                                           \
  (__ZNG_POINTER) = (__ZNG_TYPE *) malloc(sizeof(__ZNG_TYPE)); \
  if ((__ZNG_POINTER) == NULL) {                               \
    fprintf(stderr, "[__ZNG_MEMORY_H__:ALLOCATE] "             \
                    "ERROR: "                                  \
                    "Error allocating memory. "                \
                    "Could not allocate memory of type '"      \
                    #__ZNG_TYPE                                \
                    "' for the variable '"                     \
                    #__ZNG_POINTER                             \
                    "' using malloc.\n");                      \
  }                                                            \
} while (0)

#define COALLOCATE(__ZNG_TYPE, __ZNG_POINTER, __ZNG_SIZE)                    \
do {                                                                         \
  (__ZNG_POINTER) = (__ZNG_TYPE *) calloc((__ZNG_SIZE), sizeof(__ZNG_TYPE)); \
  if ((__ZNG_POINTER) == NULL) {                                             \
    fprintf(stderr, "[__ZNG_MEMORY_H__:COALLOCATE] "                         \
                    "ERROR: "                                                \
                    "Error allocating memory. "                              \
                    "Could not allocate memory of type '"                    \
                    #__ZNG_TYPE                                              \
                    "' for the variable '"                                   \
                    #__ZNG_POINTER                                           \
                    "' that required a size of '"                            \
                    "%d"                                                     \
                    "' using calloc.\n", (int) (__ZNG_SIZE));                \
  }                                                                          \
} while (0)

#define REALLOCATE(__ZNG_TYPE, __ZNG_POINTER, __ZNG_SIZE)        \
do {                                                             \
  __ZNG_TYPE* __zng_temp_ptr =                                   \
      (__ZNG_TYPE *) realloc((__ZNG_POINTER),                    \
                             (__ZNG_SIZE) * sizeof(__ZNG_TYPE)); \
  if (__zng_temp_ptr == NULL) {                                  \
    fprintf(stderr, "[__ZNG_MEMORY_H__:REALLOCATE] "             \
                    "ERROR: "                                    \
                    "Error reallocating memory. "                \
                    "Could not reallocate memory of type '"      \
                    #__ZNG_TYPE                                  \
                    "' for the variable '"                       \
                    #__ZNG_POINTER                               \
                    "' that required a new size of '"            \
                    "%d"                                         \
                    "' using realloc.\n", (int) (__ZNG_SIZE));   \
  } else {                                                       \
    __ZNG_POINTER = __zng_temp_ptr;                              \
  }                                                              \
} while (0)

#define DEALLOCATE(__ZNG_POINTER) \
do {                              \
  if ((__ZNG_POINTER) != NULL) {  \
    free((__ZNG_POINTER));        \
    (__ZNG_POINTER) = NULL;       \
  }                               \
} while (0)

#endif // __ZNG_MEMORY_H__
