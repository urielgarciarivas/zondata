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

#include "../../inc/array.h"
#include "../deps/zontest/comparators.h"

int main(void) {
  START_TEST("array_test");

  const size_t length = 5;
  const int first_element = 0;
  const int last_element = length - 1;
  array* arr = allocate_array(first_element);
  EXPECT_EQUAL(arr->data[0], first_element);

  for (int i = first_element + 1; i <= last_element; ++i) {
    add_to_array(arr, i);
  }

  EXPECT_TRUE(exist_in_array(arr, first_element + 2));
  EXPECT_FALSE(exist_in_array(arr, last_element + 1));
  EXPECT_EQUAL(arr->size, length);

  array* arr_copy = allocate_copy_array(arr);
  EXPECT_FALSE(are_equal_array(arr_copy, NULL));
  EXPECT_TRUE(are_equal_array(arr, arr_copy));

/*
  reverse_linked_list(list);
  EXPECT_FALSE(equal_linked_list(list, list_copy));
  reverse_linked_list(list_copy);
  EXPECT_TRUE(equal_linked_list(list, list_copy));
  EXPECT_TRUE(equal_linked_list(list_copy, list_copy));

  erase_single_match_linked_list(list_copy, 3);
  EXPECT_FALSE(exist_in_linked_list(list_copy, 3));
  EXPECT_FALSE(equal_linked_list(list, list_copy));

  linked_list_node* node;
  int curr_element = last_element;

  for (node = list->head; node != NULL; node = node->next) {
    EXPECT_EQUAL(node->value, curr_element--);
  }

*/

  deallocate_array(arr);
  deallocate_array(arr_copy);

  FINISH_TEST();

  return test_result();
}
