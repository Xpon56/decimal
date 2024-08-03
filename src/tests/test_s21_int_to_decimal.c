#include "test.h"

START_TEST(s21_from_int_to_decimal_1) {
  int src = 2147483647;
  s21_decimal expected = {{2147483647, 0, 0, 0}};
  s21_decimal result;
  int returned = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  int src = 0;
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result;
  int returned = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  int src = -1000;
  s21_decimal expected = {{1000, 0, 0, 0}};
  s21_decimal_set_bit(&expected, 127, 1);
  s21_decimal result;
  int returned = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

Suite *s21_int_to_decimal_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_from_int_to_decimal");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_from_int_to_decimal_1);
  tcase_add_test(tc_core, s21_from_int_to_decimal_2);
  tcase_add_test(tc_core, s21_from_int_to_decimal_3);
  suite_add_tcase(s, tc_core);
  return s;
}