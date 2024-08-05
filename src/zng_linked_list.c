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

#include <stdio.h>

#include "../inc/zng_linked_list.h"
#include "../inc/zng_memory.h"

inline zng_linked_list* allocate_linked_list(int value) {
  zng_linked_list* response;

  ALLOCATE(zng_linked_list, response);
  ALLOCATE(zng_linked_list_node, response->head);
  response->size = 1;
  response->head->value = value;
  response->head->next = NULL;
  response->tail = response->head;

  return response;
}

inline zng_linked_list* allocate_empty_linked_list(void) {
  zng_linked_list* response;

  ALLOCATE(zng_linked_list, response);
  response->size = 0;
  response->head = NULL;
  response->tail = NULL;

  return response;
}

zng_linked_list* allocate_preset_linked_list(size_t size, int value) {
  zng_linked_list* response = allocate_empty_linked_list();

  while (size--) {
    add_to_linked_list(response, value);
  }

  return response;
}

zng_linked_list* allocate_copy_linked_list(
    const zng_linked_list*const original) {
  if (original == NULL) {
    return NULL;
  } else if (is_empty_linked_list(original)) {
    return allocate_empty_linked_list();
  }

  zng_linked_list* copy = allocate_preset_linked_list(original->size, 0);
  zng_linked_list_node* original_node = original->head;
  zng_linked_list_node* copy_node = copy->head;

  while (original_node != NULL) {
    copy_node->value = original_node->value;
    original_node = original_node->next;
    copy_node = copy_node->next;
  }

  return copy;
}

inline bool is_null_or_empty_linked_list(const zng_linked_list*const list) {
  return list == NULL
      || (list->head == NULL
       && list->tail == NULL
       && list->size == 0);
}

inline bool is_empty_linked_list(const zng_linked_list*const list) {
  return list != NULL
      && list->head == NULL
      && list->tail == NULL
      && list->size == 0;
}

bool exist_in_linked_list(const zng_linked_list*const list, int value) {
  if (is_null_or_empty_linked_list(list)) {
    return false;
  }

  zng_linked_list_node* head = list->head;

  while (head != NULL) {
    if (head->value == value) {
      return true;
    }

    head = head->next;
  }

  return false;
}

bool are_equal_linked_list(
    const zng_linked_list*const lhs, const zng_linked_list*const rhs) {
  if (lhs == NULL && rhs == NULL) {
    return true;
  } else if (is_empty_linked_list(lhs) && is_empty_linked_list(rhs)) {
    return true;
  } else if (is_null_or_empty_linked_list(lhs)
          || is_null_or_empty_linked_list(rhs)
          || lhs->size != rhs->size) {
    return false;
  }

  zng_linked_list_node* lhs_node = lhs->head;
  zng_linked_list_node* rhs_node = rhs->head;

  while (lhs_node != NULL && rhs_node != NULL) {
    if (lhs_node->value != rhs_node->value) {
      return false;
    }

    lhs_node = lhs_node->next;
    rhs_node = rhs_node->next;
  }

  return lhs_node == NULL && rhs_node == NULL;
}

void print_linked_list(const zng_linked_list*const list) {
  if (list == NULL) {
    printf("list = NULL\n");
    return;
  } else if (is_empty_linked_list(list)) {
    printf("list = {}\n");
    return;
  }

  zng_linked_list_node* head = list->head;
  printf("list = {");

  while (head != NULL) {
    printf("%d", head->value);
    head = head->next;
    printf("}->{");
  }

  printf("}\n");
}

inline void add_to_empty_linked_list(zng_linked_list*const list, int value) {
  if (list == NULL || !is_empty_linked_list(list)) {
    return;
  }

  ALLOCATE(zng_linked_list_node, list->head);
  list->size = 1;
  list->head->value = value;
  list->head->next = NULL;
  list->tail = list->head;
}

inline void add_to_linked_list(zng_linked_list*const list, int value) {
  if (list == NULL) {
    return;
  } else if (is_empty_linked_list(list)) {
    add_to_empty_linked_list(list, value);
    return;
  }

  ALLOCATE(zng_linked_list_node, list->tail->next);
  list->tail = list->tail->next;
  list->tail->value = value;
  list->tail->next = NULL;
  list->size++;
}

//void erase_all_match_linked_list(zng_linked_list* list, int target) {}

void reverse_linked_list(zng_linked_list*const list) {
  if (is_null_or_empty_linked_list(list)) {
    return;
  }

  zng_linked_list_node* current = list->head;
  zng_linked_list_node* previous = NULL;       
  zng_linked_list_node* next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  current = list->head;
  list->head = list->tail;
  list->tail = current;
}

//void sort_linked_list(zng_linked_list*const list) {}

void delete_first_match_linked_list(zng_linked_list*const list, int target) {
  if (is_null_or_empty_linked_list(list)) {
    return;
  }

  zng_linked_list_node* node = list->head;

  if (node->value == target) {
    if (list->size == 1) {
      deallocate_linked_list(list);
      return;
    }

    list->head = node->next;
    DEALLOCATE(node);
    list->size--;
    return;
  }

  while (node->next != NULL) {
    if (node->next->value == target) {
      if (node->next == list->tail) {
        list->tail = node;
      }

      zng_linked_list_node* aux;
      aux = node->next;
      node->next = node->next->next;
      DEALLOCATE(aux);
      list->size--;
      return;
    }

    node = node->next;
  }
}

void delete_all_elements_linked_list(zng_linked_list*const list) {
  if (is_null_or_empty_linked_list(list)) {
    return;
  }

  zng_linked_list_node* node;
  zng_linked_list_node* next;

  for (node = list->head; node != NULL; node = next) {
    next = node->next;
    DEALLOCATE(node);
  }

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

inline void deallocate_linked_list(zng_linked_list* list) {
  if (list == NULL) {
    return;
  }

  delete_all_elements_linked_list(list);
  DEALLOCATE(list);
}
