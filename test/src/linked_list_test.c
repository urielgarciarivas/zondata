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

  EXPECT_TRUE(list != NULL);
  EXPECT_TRUE(list->head != NULL);
  EXPECT_TRUE(list->tail != NULL);
  EXPECT_EQUAL(list->size, 1);
  EXPECT_EQUAL(list->head->value, element);

  deallocate_linked_list(list);
}

TEST(LinkedListAllocation, empty_allocation) {
  linked_list* list = allocate_empty_linked_list();

  EXPECT_TRUE(list != NULL);
  EXPECT_EQUAL(list->size, 0);
  EXPECT_EQUAL(list->head, NULL);
  EXPECT_EQUAL(list->tail, NULL);

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
