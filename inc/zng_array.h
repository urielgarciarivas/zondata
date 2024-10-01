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

#ifndef __ZNG_ARRAY_H__
#define __ZNG_ARRAY_H__

#include <stdbool.h>
#include <stddef.h>

extern const size_t __zng_start_array_capacity;

typedef struct __zng_array {
  int* data;
  size_t size;
  size_t capacity;
} zng_array;

// Every new array needs to be deleted using deallocate_array(...).
extern zng_array* allocate_array(int value);
extern zng_array* allocate_empty_array(void);
extern zng_array* allocate_preset_array(size_t size, int value);
extern zng_array* allocate_copy_array(const zng_array*const list);
extern zng_array* allocate_move_from_raw_array(int* array, size_t size);
extern zng_array* allocate_copy_from_raw_array(
    const int*const array, size_t size);

extern bool is_null_or_empty_array(const zng_array*const array);
extern bool is_empty_array(const zng_array*const array);
extern bool exist_in_array(const zng_array*const array, int target);
extern bool are_equal_array(
    const zng_array*const lhs, const zng_array*const rhs);

extern void add_to_array(zng_array*const array, int value);
extern void add_to_empty_array(zng_array*const array, int value);
extern void add_capacity_array(zng_array*const array, int value);
extern void append_to_array(
    zng_array*const array, const zng_array*const append);

// TODO:
extern void reverse_array(zng_array*const list);
extern void sort_array(zng_array*const list);

// TODO:
extern void delete_first_match_array(zng_array*const array);
extern void delete_last_element_array(zng_array*const array);
extern void delete_all_elements_array(zng_array*const array);
extern void deallocate_array(zng_array* array);

#endif // __ZNG_ARRAY_H__
