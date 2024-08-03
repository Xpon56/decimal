#include "test.h"

START_TEST(s21_mul_1) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal expected = {{4, 0, 0, 0}};
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal_set_bit(&x, 127, 1);
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal expected = {{4, 0, 0, 0}};
  s21_decimal_set_bit(&expected, 127, 1);
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal_set_bit(&y, 127, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal expected = {{4, 0, 0, 0}};
  s21_decimal_set_bit(&expected, 127, 1);
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_4) {
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal_set_bit(&x, 127, 1);
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal_set_bit(&y, 127, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal expected = {{4, 0, 0, 0}};
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal x = {{0, 2, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 4, 0, 0}};
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_6) {
  s21_decimal x = {{0, 0, 2, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 4, 0}};
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_7) {  // float * 0
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal_set_pow(&x, 2);
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_8) {  // float * 0
  s21_decimal x = {{2, 0, 0, 0}};
  s21_decimal_set_pow(&x, 2);
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};
  int returned = s21_mul(y, x, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_9) {  // 2 * 0.02
  int x_i = 2;
  float y_f = 0.02;
  float exp_f = 0.04;
  s21_decimal x;
  s21_decimal y;
  s21_decimal expected;
  s21_from_int_to_decimal(x_i, &x);
  s21_from_float_to_decimal(y_f, &y);
  s21_from_float_to_decimal(exp_f, &expected);
  s21_decimal result;
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_10) {  // 0.02 * 2
  int x_i = 2;
  float y_f = 0.02;
  float exp_f = 0.04;
  s21_decimal x;
  s21_decimal y;
  s21_decimal expected;
  s21_from_int_to_decimal(x_i, &x);
  s21_from_float_to_decimal(y_f, &y);
  s21_from_float_to_decimal(exp_f, &expected);
  s21_decimal result;
  int returned = s21_mul(y, x, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_11) {  // 0.009 * 1
  s21_decimal x = {{9, 0, 0, 0}};
  s21_decimal_set_pow(&x, 3);
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal expected = {{9, 0, 0, 0}};
  s21_decimal_set_pow(&expected, 3);
  s21_decimal result;
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_12) {  // 0.009 * -1
  s21_decimal x = {{9, 0, 0, 0}};
  s21_decimal_set_pow(&x, 3);
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal_set_bit(&y, 127, 1);
  s21_decimal expected = {{9, 0, 0, 0}};
  s21_decimal_set_bit(&expected, 127, 1);
  s21_decimal_set_pow(&expected, 3);
  s21_decimal result;
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_13) {  // -0.009 * 1
  s21_decimal x = {{9, 0, 0, 0}};
  s21_decimal_set_pow(&x, 3);
  s21_decimal_set_bit(&x, 127, 1);
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal expected = {{9, 0, 0, 0}};
  s21_decimal_set_bit(&expected, 127, 1);
  s21_decimal_set_pow(&expected, 3);
  s21_decimal result;
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_14) {  // -0.009 * -1
  s21_decimal x = {{9, 0, 0, 0}};
  s21_decimal_set_pow(&x, 3);
  s21_decimal_set_bit(&x, 127, 1);
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal_set_bit(&y, 127, 1);
  s21_decimal expected = {{9, 0, 0, 0}};
  s21_decimal_set_pow(&expected, 3);
  s21_decimal result;
  int returned = s21_mul(x, y, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_15) {  //   -1 * -0.009
  s21_decimal x = {{9, 0, 0, 0}};
  s21_decimal_set_pow(&x, 3);
  s21_decimal_set_bit(&x, 127, 1);
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal_set_bit(&y, 127, 1);
  s21_decimal expected = {{9, 0, 0, 0}};
  s21_decimal_set_pow(&expected, 3);
  s21_decimal result;
  int returned = s21_mul(y, x, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_mul_16) {
  s21_decimal x = {{9, 0, 0, 0}};
  s21_decimal_set_pow(&x, 28);
  s21_decimal_set_bit(&x, 127, 1);
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal result;
  int returned = s21_mul(y, x, &result);
  ck_assert_int_eq(returned, s21_SMALL_ERROR);
}
END_TEST

Suite *s21_mul_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_mul");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_mul_1);
  tcase_add_test(tc_core, s21_mul_2);
  tcase_add_test(tc_core, s21_mul_3);
  tcase_add_test(tc_core, s21_mul_4);
  tcase_add_test(tc_core, s21_mul_5);
  tcase_add_test(tc_core, s21_mul_6);
  tcase_add_test(tc_core, s21_mul_7);
  tcase_add_test(tc_core, s21_mul_8);
  tcase_add_test(tc_core, s21_mul_9);
  tcase_add_test(tc_core, s21_mul_10);
  tcase_add_test(tc_core, s21_mul_11);
  tcase_add_test(tc_core, s21_mul_12);
  tcase_add_test(tc_core, s21_mul_13);
  tcase_add_test(tc_core, s21_mul_14);
  tcase_add_test(tc_core, s21_mul_15);
  tcase_add_test(tc_core, s21_mul_16);
  suite_add_tcase(s, tc_core);
  return s;
}
