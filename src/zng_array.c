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

// Forward declarations to follow header's order.
bool is_empty_array(const zng_array*const array);
void add_to_empty_array(zng_array*const array, int value);
void add_capacity_array(zng_array*const array, int value);
void delete_all_elements_array(zng_array*const array);

inline zng_array* allocate_empty_array(void) {
  zng_array* response;

  ALLOCATE(zng_array, response);
  response->data = NULL;
  response->size = 0;
  response->capacity = 0;

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
  response->capacity = size;

  for (size_t i = 0; i < response->size; ++i) {
    response->data[i] = value;
  }

  return response;
}

zng_array* allocate_copy_array(const zng_array*const array) {
  if (array == NULL) {
    return NULL;
  } else if (is_empty_array(array)) {
    return allocate_empty_array();
  }

  zng_array* copy;

  ALLOCATE(zng_array, copy);
  COALLOCATE(int, copy->data, array->size);
  copy->size = array->size;
  copy->capacity = copy->size;

  for (size_t i = 0; i < copy->size; ++i) {
    copy->data[i] = array->data[i];
  }

  return copy;
}

inline zng_array* allocate_move_from_raw_array(int* array, size_t size) {
  zng_array* response;

  ALLOCATE(zng_array, response);
  response->size = size;
  response->capacity = response->size;
  response->data = array;

  return response;
}

//zng_array* allocate_copy_from_raw_array(const int*const array, size_t size);

inline bool is_null_or_empty_array(const zng_array*const array) {
  return array == NULL || array->size == 0;
}

inline bool is_empty_array(const zng_array*const array) {
  return array != NULL && array->size == 0;
}

bool exist_in_array(const zng_array*const array, int target) {
  if (is_null_or_empty_array(array)) {
    return false;
  }

  for (size_t i = 0; i < array->size; ++i) {
    if (array->data[i] == target) {
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

// TODO: There is a memory leak here. If the user allocates an array, then calls
// delete_last_element_array or delete_all_elements_array, and then calls
// add_to_array, the previous allocated memory will not be freed.
inline void add_to_array(zng_array*const array, int value) {
  if (is_null_or_empty_array(array)) {
    if (is_empty_array(array)) {
      add_to_empty_array(array, value);
    }
  } else if (array->size == array->capacity) {
    add_capacity_array(array, value);
  } else {
    array->data[array->size++] = value;
  }
}

inline void add_to_empty_array(zng_array*const array, int value) {
  if (array == NULL) {
    return;
  } else if (array->data != NULL && array->capacity > array->size) {
    array->data[array->size++] = value;
  } else {
    ALLOCATE(int, array->data);
    array->size = 1;
    array->capacity = 1;
    *(array->data) = value;
  }
}

void add_capacity_array(zng_array*const array, int value) {
  if (array == NULL) {
    return;
  } else if (is_empty_array(array)) {
    add_to_empty_array(array, value);
    return;
  }

  array->capacity *= 2;
  REALLOCATE(int, array->data, array->capacity);
  array->data[array->size++] = value;
}

//void reverse_array(zng_array*const list);

//void sort_array(zng_array*const list);

inline void delete_last_element_array(zng_array*const array) {
  if (is_null_or_empty_array(array)) {
    return;
  } else if (array->size == 1) {
    delete_all_elements_array(array);
    return;
  }

  array->size--;
}

inline void delete_all_elements_array(zng_array*const array) {
  if (is_null_or_empty_array(array)) {
    return;
  }

  array->size = 0;
}

inline void deallocate_data_only_array(zng_array*const array) {
  if (array == NULL) {
    return;
  }

  if (array->data != NULL) {
    DEALLOCATE(array->data);
  }

  array->size = 0;
  array->capacity = 0;
}

inline void deallocate_array(zng_array* array) {
  if (array == NULL) {
    return;
  }

  if (array->data != NULL) {
    DEALLOCATE(array->data);
  }

  array->size = 0;
  array->capacity = 0;

  DEALLOCATE(array);
}
