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

#include "../../inc/hash_set.h"
#include "../deps/zontest/test.h"

TEST(HashSetTest, all_tests) {
  const size_t size = 10;
  hash_set set;
  set.size = size;
  EXPECT_EQUAL(set.size, size);
}

int main(void) {
  RUN_TESTS("HashSetTest");
  return TEST_RESULT();
}
