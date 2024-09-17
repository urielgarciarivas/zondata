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

#include "../../inc/zng_array.h"
#include "../deps/zontest/test.h"

TEST(ArrayAllocation, simple_allocation) {
  const int value = 15;
  zng_array* arr = allocate_array(value);

  EXPECT_DIFFERENT(arr, NULL);
  EXPECT_DIFFERENT(arr->data, NULL);
  EXPECT_EQUAL(arr->size, 1);
  EXPECT_EQUAL(*(arr->data), value);

  deallocate_array(arr);
}

TEST(ArrayAllocation, preset_allocation) {
  const size_t size = 100;
  const int value = 27;
  zng_array* arr = allocate_preset_array(size, value);

  EXPECT_DIFFERENT(arr, NULL);
  EXPECT_DIFFERENT(arr->data, NULL);
  EXPECT_EQUAL(arr->size, size);

  for (size_t i = 0; i < arr->size; ++i) {
    EXPECT_EQUAL(arr->data[i], value);
  }

  deallocate_array(arr);
}

TEST(ArrayAllocation, empty_allocation) {
  zng_array* arr = allocate_empty_array();

  EXPECT_DIFFERENT(arr, NULL);
  EXPECT_EQUAL(arr->data, NULL);
  EXPECT_EQUAL(arr->size, 0);

  deallocate_array(arr);
}

TEST(ArrayAllocation, copy_allocation) {
  const size_t size = 100;
  const int value = 46;
  zng_array* arr = allocate_preset_array(size, value);
  zng_array* arr_copy = allocate_copy_array(arr);

  EXPECT_DIFFERENT(arr_copy, NULL);
  EXPECT_DIFFERENT(arr_copy->data, NULL);
  EXPECT_EQUAL(arr_copy->size, arr->size);

  for (size_t i = 0; i < arr->size; ++i) {
    EXPECT_EQUAL(arr->data[i], arr_copy->data[i]);
  }

  deallocate_array(arr);
  deallocate_array(arr_copy);
}

TEST(ArrayManipulation, adding_elements) {
  const int size = 100;
  zng_array* arr = allocate_empty_array();

  for (int i = 0; i < size; ++i) {
    add_to_array(arr, i);
  }

  EXPECT_DIFFERENT(arr->data, NULL);
  EXPECT_EQUAL(arr->size, (size_t) size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQUAL(arr->data[i], i);
  }

  deallocate_array(arr);
}

TEST(ArrayManipulation, delete_all) {
  const size_t size = 100;
  const int value = 59;
  zng_array* arr = allocate_preset_array(size, value);

  EXPECT_DIFFERENT(arr, NULL);
  EXPECT_DIFFERENT(arr->data, NULL);
  EXPECT_EQUAL(arr->size, size);

  delete_all_elements_array(arr);

  EXPECT_DIFFERENT(arr, NULL);
  EXPECT_EQUAL(arr->data, NULL);
  EXPECT_EQUAL(arr->size, 0);

  deallocate_array(arr);
}

TEST(ArrayVerification, check_if_exists) {
  const int size = 200;
  zng_array* arr = allocate_preset_array((size_t) size, 0);

  for (int i = 0; i < size; ++i) {
    arr->data[i] = i;
  }

  EXPECT_TRUE(exist_in_array(arr, 0));
  EXPECT_TRUE(exist_in_array(arr, size / 2));
  EXPECT_TRUE(exist_in_array(arr, size - 1));
  EXPECT_FALSE(exist_in_array(arr, size));
  EXPECT_FALSE(exist_in_array(arr, 10000));
  EXPECT_FALSE(exist_in_array(arr, -10000));

  deallocate_array(arr);
}

TEST(ArrayVerification, check_equal) {
  zng_array* arr = allocate_preset_array(200, 0);
  zng_array* arr_copy = allocate_copy_array(arr);

  EXPECT_TRUE(are_equal_array(arr, arr));
  EXPECT_TRUE(are_equal_array(arr, arr_copy));
  EXPECT_TRUE(are_equal_array(arr_copy, arr_copy));

  add_to_array(arr, 1);
  EXPECT_FALSE(are_equal_array(arr, arr_copy));
  add_to_array(arr_copy, 1);
  EXPECT_TRUE(are_equal_array(arr, arr_copy));

  arr->data[10] = 1919;
  EXPECT_FALSE(are_equal_array(arr, arr_copy));
  arr_copy->data[10] = 1919;
  EXPECT_TRUE(are_equal_array(arr, arr_copy));

  delete_all_elements_array(arr);
  EXPECT_FALSE(are_equal_array(arr, arr_copy));
  delete_all_elements_array(arr_copy);
  EXPECT_TRUE(are_equal_array(arr, arr_copy));

  add_to_array(arr, 1919);
  EXPECT_FALSE(are_equal_array(arr, arr_copy));
  add_to_array(arr_copy, 1919);
  EXPECT_TRUE(are_equal_array(arr, arr_copy));

  deallocate_array(arr);
  deallocate_array(arr_copy);
}

int main(void) {
  RUN_TESTS("ArrayTest");
  return TEST_RESULT();
}
