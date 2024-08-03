#include "test.h"

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal src = {{9, 0, 0, 0}};
  s21_decimal_set_bit(&src, 127, 1);
  s21_decimal_set_pow(&src, 1);
  float result;
  float expected = -0.9;
  int returned = s21_from_decimal_to_float(src, &result);
  ck_assert_float_eq(result, expected);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  s21_decimal src = {{1, 0, 0, 0}};
  s21_decimal_set_pow(&src, 1);
  float result;
  float expected = 0.1;
  int returned = s21_from_decimal_to_float(src, &result);
  ck_assert_float_eq(result, expected);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  s21_decimal src = {{1, 0, 0, 0}};
  s21_decimal_set_pow(&src, 5);
  float result;
  float expected = 0.00001;
  int returned = s21_from_decimal_to_float(src, &result);
  ck_assert_float_eq(result, expected);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal src = {{1, 0, 0, 0}};
  s21_decimal_set_pow(&src, 1);
  int returned = s21_from_decimal_to_float(src, NULL);
  ck_assert_int_eq(returned, CONVERTATION_ERROR);
}
END_TEST

Suite *s21_decimal_to_float_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_from_decimal_to_float");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_from_decimal_to_float_1);
  tcase_add_test(tc_core, s21_from_decimal_to_float_2);
  tcase_add_test(tc_core, s21_from_decimal_to_float_3);
  tcase_add_test(tc_core, s21_from_decimal_to_float_4);
  suite_add_tcase(s, tc_core);
  return s;
}
