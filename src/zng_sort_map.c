/*
 * MIT License
 *
 * Copyright (c) 2021-2025 Uriel García Rivas
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
#include "../inc/zng_sort_map.h"

inline zng_sort_map* allocate_empty_sort_map(void) {
  zng_sort_map* response;

  ALLOCATE(zng_sort_map, response);
  response->size = 0;
  response->root = NULL;

  return response;
}

inline bool is_null_or_empty_sort_map(const zng_sort_map*const map) {
  return map == NULL || (map->root == NULL && map->size == 0);
}

inline bool is_empty_sort_map(const zng_sort_map*const map) {
  return map != NULL && map->root == NULL && map->size == 0;
}

void delete_nodes_recursive_sort_map(zng_sort_map_node* node) {
  if (node == NULL) {
    return;
  }

  delete_nodes_recursive_sort_map(node->left);  
  delete_nodes_recursive_sort_map(node->right);
  DEALLOCATE(node);  
}

void delete_all_elements_sort_map(zng_sort_map*const map) {
  if (is_null_or_empty_sort_map(map)) {
    return;
  }

  delete_nodes_recursive_sort_map(map->root);
  map->root = NULL;
  map->size = 0;
}

void deallocate_sort_map(zng_sort_map* map) {
  if (map == NULL) {
    return;
  }

  if (map->root != NULL) {
    delete_all_elements_sort_map(map);
  }

  DEALLOCATE(map);
}
