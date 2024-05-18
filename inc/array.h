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

typedef struct __zng_array {
  int* data;
  size_t size;
} array;

// Every new array needs to be deleted using deallocate_array(...).
extern array* allocate_array(int value);
extern array* allocate_preset_array(int size, int value);
extern array* allocate_empty_array();
// By making a copy, deleting that copy is also necessary.
extern array* allocate_copy_array(const array*const list);

extern bool is_null_or_empty_array(const array*const arr);
extern bool is_empty_array(const array*const arr);

extern void add_to_array(array*const arr, int value);
extern void add_to_empty_array(array*const arr, int value);

extern bool exist_in_array(const array*const arr, int target);

// TODO:
extern void delete_all_elements_array(array* arr);
extern void delete_last_element_array(array* arr);

// TODO
// Linear time.
extern void reverse_array(array*const list);
extern bool are_equal_array(const array*const lhs, const array*const rhs);
extern void sort_array(array*const list);

extern void deallocate_array(array* arr);

#endif // __ZNG_ARRAY_H__
