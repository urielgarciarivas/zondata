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

#include "../../inc/zng_sort_map.h"
#include "../deps/zontest/test.h"

TEST(SortMapAllocation, empty_allocation) {
  zng_sort_map* map = allocate_empty_sort_map();

  EXPECT_DIFFERENT(map, NULL);
  EXPECT_EQUAL(map->size, 0);
  EXPECT_EQUAL(map->root, NULL);

  deallocate_sort_map(map);
}

int main(void) {
  RUN_TESTS("SortMapTest");
  return TEST_RESULT();
}
