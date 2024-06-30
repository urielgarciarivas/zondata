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

#include "../../inc/sort_set.h"
#include "../deps/zontest/test.h"

TEST(SortSetAllocation, simple_allocation) {
  const int element = 15;
  sort_set* set = allocate_sort_set(element);

  EXPECT_DIFFERENT(set, NULL);
  EXPECT_DIFFERENT(set->root, NULL);
  EXPECT_EQUAL(set->size, 1);
  EXPECT_EQUAL(set->root->value, element);

  deallocate_sort_set(set);
}

TEST(SortSetAllocation, empty_allocation) {
  sort_set* set = allocate_empty_sort_set();

  EXPECT_DIFFERENT(set, NULL);
  EXPECT_EQUAL(set->size, 0);
  EXPECT_EQUAL(set->root, NULL);

  deallocate_sort_set(set);
}

TEST(SortSetTest, all_tests) {
  const size_t len = 15;
  const int last_element = (int) len - 1;
  const int first_element = 0;
  sort_set* set = allocate_sort_set(first_element);

  EXPECT_EQUAL(set->size, 1);
  EXPECT_TRUE(set->root != NULL);
  EXPECT_EQUAL(set->root->value, first_element);

  for (int i = first_element + 1; i <= last_element; ++i) {
    //add_to_sort_set(set, i);
  }

  deallocate_sort_set(set);
}

int main(void) {
  RUN_TESTS("SortSetTest");
  return TEST_RESULT();
}
