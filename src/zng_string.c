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

#include <string.h>

#include "../inc/zng_memory.h"
#include "../inc/zng_string.h"

zng_string* allocate_empty_string(void) {
  zng_string* response;

  ALLOCATE(zng_string, response);
  response->data = NULL;
  response->size = 0;
  response->capacity = 0;

  return response;
}

zng_string* allocate_preset_string(size_t size, char value);
zng_string* allocate_copy_string(const zng_string*const string);

inline bool is_null_or_empty_string(const zng_string*const string) {
  return string == NULL || (string->data == NULL && string->size == 0);
}

inline bool is_empty_string(const zng_string*const string) {
  return string != NULL && string->data == NULL && string->size == 0;
}

bool exist_in_string(const zng_string*const string, char target) {
  for (size_t i = 0; i < string->size; ++i) {
    if (string->data[i] == target) {
        return true;
    }
  }

  return false;
}

bool are_equal_string(const zng_string*const lhs, const zng_string*const rhs) {
  if (lhs == NULL && rhs == NULL) {
    return true;
  } else if (is_empty_string(lhs) && is_empty_string(rhs)) { 
    return true;
  } else if (is_null_or_empty_string(lhs)
          || is_null_or_empty_string(rhs)
          || lhs->size != rhs->size) {
    return false;
  }

  for (size_t i = 0; i < lhs->size; ++i) {
    if (lhs->data[i] != rhs->data[i]) {
      return false;
    }
  }

  return true;
}

void add_to_string(zng_string*const string, char value);
void add_to_empty_string(zng_string*const string, char value);
void append_to_string(
    zng_string*const string, const zng_string*const append);
void append_from_raw_to_string(
    zng_string*const string, const char*const append, size_t size);

// TODO:
void reverse_string(zng_string*const string) {
  char aux;

  for (size_t i = 0, j = string->size - 1; i < j; ++i, --j) {
    aux = string->data[i];
    string->data[i] = string->data[j];
    string->data[j] = aux;
  }
}

void sort_string(zng_string*const string);

// TODO:
void delete_first_match_string(zng_string*const string);
void delete_last_element_string(zng_string*const string);
void delete_all_elements_string(zng_string*const string);
void deallocate_string(zng_string* string);
