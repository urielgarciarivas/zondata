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

#ifndef __ZNG_SORT_MAP_H__
#define __ZNG_SORT_MAP_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct __zng_sort_map_node {
  int key;
  int value;
  struct __zng_sort_map_node* left;
  struct __zng_sort_map_node* right;
} zng_sort_map_node;

typedef struct __zng_sort_map {
  size_t size;
  zng_sort_map_node* root;
} zng_sort_map;

// Every new map needs to be deleted using deallocate_sort_map(...).
extern zng_sort_map* allocate_empty_sort_map(void);
//extern zng_sort_map* allocate_preset_sort_map(
//    size_t size, int start, int increment);
extern zng_sort_map* allocate_copy_sort_map(const zng_sort_map*const map);
//extern zng_sort_map* allocate_copy_from_raw_sort_map(
//    const int*const array, size_t size);

extern bool is_null_or_empty_sort_map(const zng_sort_map*const map);
extern bool is_empty_sort_map(const zng_sort_map*const map);

extern void add_to_sort_map(zng_sort_map*const map, int value);
extern void add_to_empty_sort_map(zng_sort_map*const map, int value);

// Time: O(log(n))
// Space: O(1)
extern bool exist_in_sort_map(const zng_sort_map*const map, int target);

// TODO:
extern void delete_nodes_recursive_sort_map(zng_sort_map_node* node);
extern void delete_all_elements_sort_map(zng_sort_map*const node);
extern void deallocate_sort_map(zng_sort_map* map);

#endif // __ZNG_SORT_MAP_H__
