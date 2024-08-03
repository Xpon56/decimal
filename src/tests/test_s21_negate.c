#include "test.h"

START_TEST(s21_negate_1) {
  s21_decimal result = {{1, 0, 0, 0}};
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_decimal_set_bit(&expected, 127, 1);
  int returned = s21_negate(result, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal result = {{1, 0, 0, 0}};
  s21_decimal_set_bit(&result, 127, 1);
  s21_decimal expected = {{1, 0, 0, 0}};
  int returned = s21_negate(result, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_decimal result;
  s21_decimal_null(&result);
  int returned = s21_negate(result, NULL);
  ck_assert_int_eq(returned, s21_CALCULATION_ERROR);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_FALSE);
}
END_TEST

START_TEST(s21_negate_4) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal_set_bit(&result, 127, 1);
  s21_decimal expected = {{0, 0, 0, 0}};
  int returned = s21_negate(result, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

START_TEST(s21_negate_5) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal_set_bit(&expected, 127, 1);
  int returned = s21_negate(result, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
  ck_assert_int_eq(returned, s21_OK);
}
END_TEST

Suite *s21_negate_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_negate");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_negate_1);
  tcase_add_test(tc_core, s21_negate_2);
  tcase_add_test(tc_core, s21_negate_3);
  tcase_add_test(tc_core, s21_negate_4);
  tcase_add_test(tc_core, s21_negate_5);
  suite_add_tcase(s, tc_core);
  return s;
}
