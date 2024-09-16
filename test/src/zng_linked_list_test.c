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

#include "../../inc/zng_linked_list.h"
#include "../deps/zontest/test.h"

TEST(LinkedListAllocation, simple_allocation) {
  const int element = 15;
  zng_linked_list* list = allocate_linked_list(element);

  EXPECT_DIFFERENT(list, NULL);
  EXPECT_DIFFERENT(list->head, NULL);
  EXPECT_DIFFERENT(list->tail, NULL);
  EXPECT_EQUAL(list->head->value, element);
  EXPECT_EQUAL(list->head, list->tail);
  EXPECT_EQUAL(list->size, 1);

  deallocate_linked_list(list);
}

TEST(LinkedListAllocation, empty_allocation) {
  zng_linked_list* list = allocate_empty_linked_list();

  EXPECT_DIFFERENT(list, NULL);
  EXPECT_EQUAL(list->size, 0);
  EXPECT_EQUAL(list->head, NULL);
  EXPECT_EQUAL(list->tail, NULL);

  deallocate_linked_list(list);
}

TEST(LinkedListAllocation, preset_allocation) {
  const size_t size = 100;
  const int value = 27;
  zng_linked_list* list = allocate_preset_linked_list(size, value);

  EXPECT_DIFFERENT(list, NULL);
  EXPECT_DIFFERENT(list->head, NULL);
  EXPECT_DIFFERENT(list->tail, NULL);
  EXPECT_DIFFERENT(list->head, list->tail);
  EXPECT_EQUAL(list->size, size);

  for (zng_linked_list_node* i = list->head; i != NULL; i = i->next) {
    EXPECT_EQUAL(i->value, value);
  }

  deallocate_linked_list(list);
}

TEST(LinkedListAllocation, copy_allocation) {
  const size_t size = 100;
  zng_linked_list* original_list = allocate_preset_linked_list(size, 0);
  zng_linked_list_node* original_node = original_list->head;

  for (size_t i = 0; i < size; ++i) {
    original_node->value = (int) i * 1000;
    original_node = original_node->next;
  }

  zng_linked_list* copy_list = allocate_copy_linked_list(original_list);
  zng_linked_list_node* copy_node;

  EXPECT_DIFFERENT(copy_list, NULL);
  EXPECT_DIFFERENT(copy_list->head, NULL);
  EXPECT_DIFFERENT(copy_list->tail, NULL);
  EXPECT_DIFFERENT(copy_list->head, copy_list->tail);
  EXPECT_DIFFERENT(original_list->head, copy_list->head);
  EXPECT_DIFFERENT(original_list->tail, copy_list->tail);
  EXPECT_EQUAL(copy_list->size, size);

  for (original_node = original_list->head, copy_node = copy_list->head;
      original_node != NULL && copy_node != NULL;
      original_node = original_node->next, copy_node = copy_node->next) {
    EXPECT_EQUAL(original_node->value, copy_node->value);
  }

  EXPECT_EQUAL(original_node, NULL);
  EXPECT_EQUAL(original_node, copy_node);

  deallocate_linked_list(original_list);
  deallocate_linked_list(copy_list);
}

TEST(LinkedListAlgorithm, reverse_list) {
  const size_t size = 100;
  zng_linked_list* list = allocate_preset_linked_list(size, 0);
  zng_linked_list_node* node = list->head;

  for (int i = 0; i < (int) size; ++i) {
    node->value = i;
    node = node->next;
  }

  reverse_linked_list(list);
  EXPECT_DIFFERENT(list, NULL);
  EXPECT_DIFFERENT(list->head, NULL);
  EXPECT_DIFFERENT(list->tail, NULL);
  EXPECT_DIFFERENT(list->head, list->tail);
  EXPECT_EQUAL(list->size, size);

  node = list->head;

  for (int i = (int) size - 1; i >= 0; --i) {
    EXPECT_EQUAL(node->value, i);
    node = node->next;
  }

  deallocate_linked_list(list);
}

TEST(LinkedListTest, all_tests) {
  // length should not be >= INT_MAX.
  const size_t length = 5;
  const int first_element = 0;
  const int last_element = (int) length - 1;
  zng_linked_list* list = allocate_linked_list(first_element);

  for (int i = first_element + 1; i <= last_element; ++i) {
    add_to_linked_list(list, i);
  }

  EXPECT_TRUE(exist_in_linked_list(list, first_element + 2));
  EXPECT_FALSE(exist_in_linked_list(list, last_element + 1));
  EXPECT_EQUAL(list->size, length);

  zng_linked_list* list_copy = allocate_copy_linked_list(list);

  EXPECT_TRUE(are_equal_linked_list(list, list));
  EXPECT_TRUE(are_equal_linked_list(list, list_copy));
  reverse_linked_list(list);
  EXPECT_FALSE(are_equal_linked_list(list, list_copy));
  reverse_linked_list(list_copy);
  EXPECT_TRUE(are_equal_linked_list(list, list_copy));
  EXPECT_TRUE(are_equal_linked_list(list_copy, list_copy));

  delete_first_match_linked_list(list_copy, 3);
  EXPECT_FALSE(exist_in_linked_list(list_copy, 3));
  EXPECT_FALSE(are_equal_linked_list(list, list_copy));

  zng_linked_list_node* node;
  int curr_element = last_element;

  for (node = list->head; node != NULL; node = node->next) {
    EXPECT_EQUAL(node->value, curr_element--);
  }

  deallocate_linked_list(list);
  deallocate_linked_list(list_copy);
}

int main(void) {
  RUN_TESTS("LinkedListTest");
  return TEST_RESULT();
}
