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

#include "../inc/zng_array.h"
#include "../inc/zng_memory.h"

// Forward declarations to follow zng_array.h's order.
void delete_all_elements_array(zng_array*const arr);
void add_to_empty_array(zng_array*const arr, int value);

inline zng_array* allocate_array(int value) {
  zng_array* response;

  ALLOCATE(zng_array, response);
  ALLOCATE(int, response->data);
  response->size = 1;
  *(response->data) = value;

  return response;
}

inline zng_array* allocate_empty_array(void) {
  zng_array* response;

  ALLOCATE(zng_array, response);
  response->size = 0;
  response->data = NULL;

  return response;
}

inline zng_array* allocate_preset_array(size_t size, int value) {
  if (size == 0) {
    return allocate_empty_array();
  }

  zng_array* response;

  ALLOCATE(zng_array, response);
  COALLOCATE(int, response->data, size);
  response->size = size;

  for (size_t i = 0; i < response->size; ++i) {
    response->data[i] = value;
  }

  return response;
}

zng_array* allocate_copy_array(const zng_array*const arr) {
  if (arr == NULL) {
    return NULL;
  } else if (is_empty_array(arr)) {
    return allocate_empty_array();
  }

  zng_array* copy = allocate_preset_array(arr->size, 0);

  for (size_t i = 0; i < copy->size; ++i) {
    copy->data[i] = arr->data[i];
  }

  return copy;
}

inline bool is_null_or_empty_array(const zng_array*const arr) {
  return arr == NULL || (arr->data == NULL && arr->size == 0);
}

inline bool is_empty_array(const zng_array*const arr) {
  return arr != NULL && arr->data == NULL && arr->size == 0;
}

bool exist_in_array(const zng_array*const arr, int target) {
  if (is_null_or_empty_array(arr)) {
    return false;
  }

  for (size_t i = 0; i < arr->size; ++i) {
    if (arr->data[i] == target) {
      return true;
    }
  }

  return false;
}

bool are_equal_array(const zng_array*const lhs, const zng_array*const rhs) {
  if (lhs == NULL && rhs == NULL) {
    return true;
  } else if (is_empty_array(lhs) && is_empty_array(rhs)) { 
    return true;
  } else if (is_null_or_empty_array(lhs)
          || is_null_or_empty_array(rhs)
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

inline void add_to_array(zng_array*const arr, int value) {
  if (arr == NULL) {
    return;
  } else if (is_empty_array(arr)) {
    add_to_empty_array(arr, value);
    return;
  }

  arr->size++;
  REALLOCATE(int, arr->data, arr->size);
  arr->data[arr->size - 1] = value;
}

inline void add_to_empty_array(zng_array*const arr, int value) {
  if (arr == NULL) {
    return;
  }

  ALLOCATE(int, arr->data);
  arr->size = 1;
  *(arr->data) = value;
}

//extern void reverse_array(zng_array*const list);

//extern void sort_array(zng_array*const list);

inline void delete_last_element_array(zng_array*const arr) {
  if (is_null_or_empty_array(arr)) {
    return;
  } else if (arr->size == 1) {
    delete_all_elements_array(arr);
    return;
  }

  arr->size--;
  REALLOCATE(int, arr->data, arr->size);
}

inline void delete_all_elements_array(zng_array*const arr) {
  if (is_null_or_empty_array(arr)) {
    return;
  }

  if (arr->data != NULL) {
    DEALLOCATE(arr->data);
  }

  arr->size = 0;
}

inline void deallocate_array(zng_array* arr) {
  if (arr == NULL) {
    return;
  }

  delete_all_elements_array(arr);
  DEALLOCATE(arr);
}
