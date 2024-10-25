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

#include "../inc/zng_memory.h"
#include "../inc/zng_sort_set.h"

inline zng_sort_set* allocate_empty_sort_set(void) {
  zng_sort_set* response;

  ALLOCATE(zng_sort_set, response);
  response->size = 0;
  response->root = NULL;

  return response;
}

inline bool is_null_or_empty_sort_set(const zng_sort_set*const set) {
  return set == NULL || (set->root == NULL && set->size == 0);
}

inline bool is_empty_sort_set(const zng_sort_set*const set) {
  return set != NULL && set->root == NULL && set->size == 0;
}

//inline void add_to_sort_set(zng_sort_set*const set, int value) { set; }

bool exist_in_sort_set(const zng_sort_set*const set, int target) {
  if (is_null_or_empty_sort_set(set)) {
    return false;
  }

  zng_sort_set_node* node = set->root;

  while (node != NULL) {
    if (node->value == target) {
      return true;
    } else if (node->value < target) {
      node = node->right;
    } else {
      node = node->left;
    }
  }

  return false;
}

void delete_nodes_recursive_sort_set(zng_sort_set_node* node) {
  if (node == NULL) {
    return;
  }

  delete_nodes_recursive_sort_set(node->left);  
  delete_nodes_recursive_sort_set(node->right);
  DEALLOCATE(node);  
}

void delete_all_elements_sort_set(zng_sort_set*const set) {
  if (is_null_or_empty_sort_set(set)) {
    return;
  }

  delete_nodes_recursive_sort_set(set->root);
  set->root = NULL;
  set->size = 0;
}

void deallocate_sort_set(zng_sort_set* set) {
  if (set == NULL) {
    return;
  }

  if (set->root != NULL) {
    delete_all_elements_sort_set(set);
  }

  DEALLOCATE(set);
}
