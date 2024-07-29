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

zng_string* allocate_string(const char*const sentence) {
  zng_string* response;
  const size_t size = strlen(sentence);

  ALLOCATE(zng_string, response);
  response->size = size + 1;
  response->capacity = size * 3;
  COALLOCATE(char, response->data, response->capacity);

  for (size_t i = 0; i < response->capacity; ++i) {
    response->data[i] = (i < size ? sentence[i] : '\0');
  }

  return response;
}

zng_string* allocate_empty_string(void) {
  zng_string* response;

  ALLOCATE(zng_string, response);
  response->size = 0;
  response->capacity = 0;
  response->data = NULL;

  return response;
}

zng_string* allocate_preset_string(size_t size, char value);
zng_string* allocate_copy_string(const zng_string*const list);

inline bool is_null_or_empty_string(const zng_string*const sentence) {
  return sentence == NULL || (sentence->data == NULL && sentence->size == 0);
}

inline bool is_empty_string(const zng_string*const sentence) {
  return sentence != NULL && sentence->data == NULL && sentence->size == 0;
}

bool exist_in_string(const zng_string*const sentence, char target) {
  for (size_t i = 0; i < sentence->size; ++i) {
    if (sentence->data[i] == target) {
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

void add_to_string(zng_string*const arr, char value);
void add_to_empty_string(zng_string*const arr, char value);
void append_to_string(zng_string*const arr, const char*const append);

// TODO:
void reverse_string(zng_string*const list);
void sort_string(zng_string*const list);

// TODO:
void delete_first_match_string(zng_string*const arr);
void delete_last_element_string(zng_string*const arr);
void delete_all_elements_string(zng_string*const arr);
void deallocate_string(zng_string* arr);
