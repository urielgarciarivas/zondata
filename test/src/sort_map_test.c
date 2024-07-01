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

#include "../../inc/sort_map.h"
#include "../deps/zontest/test.h"

TEST(SortMapTest, all_tests) {
  const size_t size = 10;
  sort_map map;
  map.size = 10;
  EXPECT_EQUAL(map.size, size);
}

int main(void) {
  RUN_TESTS("SortMapTest");
  return TEST_RESULT();
}
