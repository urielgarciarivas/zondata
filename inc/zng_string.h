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

#ifndef __ZNG_STRING_H__
#define __ZNG_STRING_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct __zng_string {
  char* data;
  size_t size;
  size_t capacity;
} zng_string;

// Every new string needs to be deleted using deallocate_string(...).
extern zng_string* allocate_string(const char*const sentence);
extern zng_string* allocate_empty_string(void);
extern zng_string* allocate_preset_string(size_t size, char value);
extern zng_string* allocate_copy_string(const zng_string*const sentence);

extern bool is_null_or_empty_string(const zng_string*const sentence);
extern bool is_empty_string(const zng_string*const sentence);
extern bool exist_in_string(const zng_string*const arr, char target);
extern bool are_equal_string(
    const zng_string*const lhs, const zng_string*const rhs);

extern void add_to_string(zng_string*const arr, char value);
extern void add_to_empty_string(zng_string*const arr, char value);
extern void append_to_string(zng_string*const arr, const char*const append);

// TODO:
extern void reverse_string(zng_string*const list);
extern void sort_string(zng_string*const list);

// TODO:
extern void delete_first_match_string(zng_string*const arr);
extern void delete_last_element_string(zng_string*const arr);
extern void delete_all_elements_string(zng_string*const arr);
extern void deallocate_string(zng_string* arr);

#endif // __ZNG_STRING_H__
