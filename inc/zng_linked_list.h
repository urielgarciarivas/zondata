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

#ifndef __ZNG_LINKED_LIST_H__
#define __ZNG_LINKED_LIST_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct __zng_linked_list_node {
  int value;
  struct __zng_linked_list_node* next;
} zng_linked_list_node;

typedef struct __zng_linked_list {
  size_t size;
  zng_linked_list_node* head;
  zng_linked_list_node* tail;
} zng_linked_list;

// Every new linked list needs to be deleted using deallocate_linked_list(...).
extern zng_linked_list* allocate_empty_linked_list(void);
extern zng_linked_list* allocate_preset_linked_list(size_t size, int value);
extern zng_linked_list* allocate_copy_linked_list(
    const zng_linked_list*const list);
extern zng_linked_list* allocate_copy_from_raw_linked_list(
    const int*const pointer, size_t size);

extern bool is_null_or_empty_linked_list(const zng_linked_list*const list);
extern bool is_empty_linked_list(const zng_linked_list*const list);
extern bool exist_in_linked_list(const zng_linked_list*const list, int value);
extern bool are_equal_linked_list(
    const zng_linked_list*const lhs, const zng_linked_list*const rhs);

// Example output to screen: "list = {1}->{2}->{3}->{4}->{5}".
extern void print_linked_list(const zng_linked_list*const list);

extern void add_to_linked_list(zng_linked_list*const list, int value);
extern void add_to_empty_linked_list(zng_linked_list*const list, int value);
// TODO: Finish head and tail functions.
extern void add_as_head_linked_list(zng_linked_list*const list, int value);
extern void add_as_tail_linked_list(zng_linked_list*const list, int value);
extern void append_to_linked_list(
    zng_linked_list*const list, const zng_linked_list*const append);

// TODO:
extern void reverse_linked_list(zng_linked_list*const list);
extern void sort_linked_list(zng_linked_list*const list);

// TODO:
extern void delete_first_match_linked_list(
    zng_linked_list*const list, int target);
extern void delete_all_match_linked_list(
    zng_linked_list*const list, int target);
extern void delete_head_linked_list(zng_linked_list*const list);
extern void delete_tail_linked_list(zng_linked_list*const list);
extern void delete_all_elements_linked_list(zng_linked_list*const list);
extern void deallocate_linked_list(zng_linked_list* list);

#endif // __ZNG_LINKED_LIST_H__
