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

#include "../../inc/linked_list.h"
#include "../deps/zontest/test.h"

TEST(LinkedListAllocation, simple_allocation) {
  const int element = 15;
  linked_list* list = allocate_linked_list(element);

  EXPECT_DIFFERENT(list, NULL);
  EXPECT_DIFFERENT(list->head, NULL);
  EXPECT_DIFFERENT(list->tail, NULL);
  EXPECT_EQUAL(list->size, 1);
  EXPECT_EQUAL(list->head->value, element);

  deallocate_linked_list(list);
}

TEST(LinkedListAllocation, empty_allocation) {
  linked_list* list = allocate_empty_linked_list();

  EXPECT_DIFFERENT(list, NULL);
  EXPECT_EQUAL(list->size, 0);
  EXPECT_EQUAL(list->head, NULL);
  EXPECT_EQUAL(list->tail, NULL);

  deallocate_linked_list(list);
}

TEST(LinkedListAllocation, preset_allocation) {
  const size_t size = 100;
  const int value = 27;
  linked_list* list = allocate_preset_linked_list(size, value);

  EXPECT_DIFFERENT(list, NULL);
  EXPECT_DIFFERENT(list->head, NULL);
  EXPECT_DIFFERENT(list->tail, NULL);
  EXPECT_DIFFERENT(list->head, list->tail);
  EXPECT_EQUAL(list->size, size);

  for (linked_list_node* i = list->head; i != NULL; i = i->next) {
    EXPECT_EQUAL(i->value, value);
  }

  deallocate_linked_list(list);
}

TEST(LinkedListAllocation, copy_allocation) {
  const size_t size = 100;
  linked_list* original_list = allocate_preset_linked_list(size, 0);
  linked_list_node* original_node;

  EXPECT_DIFFERENT(original_list, NULL);
  EXPECT_DIFFERENT(original_list->head, NULL);
  EXPECT_DIFFERENT(original_list->tail, NULL);
  EXPECT_DIFFERENT(original_list->head, original_list->tail);
  EXPECT_EQUAL(original_list->size, size);

  original_node = original_list->head;

  for (size_t i = 0; i < size; ++i) {
    original_node->value = i * 10000;
    original_node = original_node->next;
  }

  linked_list* copy_list = allocate_copy_linked_list(original_list);
  linked_list_node* copy_node;

  EXPECT_DIFFERENT(copy_list, NULL);
  EXPECT_DIFFERENT(copy_list->head, NULL);
  EXPECT_DIFFERENT(copy_list->tail, NULL);
  EXPECT_DIFFERENT(copy_list->head, original_list->tail);
  EXPECT_EQUAL(copy_list->size, size);

  for (original_node = original_list->head, copy_node = copy_list->head;
      original_node != NULL && copy_node != NULL;
      original_node = original_node->next, copy_node = copy_node->next) {
    EXPECT_EQUAL(original_node->value, copy_node->value);
  }

  deallocate_linked_list(original_list);
  deallocate_linked_list(copy_list);
}

TEST(LinkedListAlgorithm, reverse_list) {
  const size_t size = 100;
  linked_list* list = allocate_preset_linked_list(size, 0);
  linked_list_node* node;

  node = list->head;

  for (int i = 0; i <  (int) size; ++i) {
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

  for (int i = size - 1; i >= 0; --i) {
    EXPECT_EQUAL(node->value, i);
    node = node->next;
  }

  deallocate_linked_list(list);
}

TEST(LinkedListTest, all_tests) {
  // length should not be >= INT_MAX.
  const size_t length = 5;
  const int first_element = 0;
  const int last_element = length - 1;
  linked_list* list = allocate_linked_list(first_element);

  for (int i = first_element + 1; i <= last_element; ++i) {
    add_to_linked_list(list, i);
  }

  EXPECT_TRUE(exist_in_linked_list(list, first_element + 2));
  EXPECT_FALSE(exist_in_linked_list(list, last_element + 1));
  EXPECT_EQUAL(list->size, length);

  linked_list* list_copy = allocate_copy_linked_list(list);

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

  linked_list_node* node;
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
