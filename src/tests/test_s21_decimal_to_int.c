#include "test.h"

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal src = {{49135648, 0, 0, 0}};
  s21_decimal_set_bit(&src, 127, 1);
  s21_decimal_set_pow(&src, 1);
  int result;
  int expected = -4913564;
  int returned = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal src = {{49135648, 0, 0, 0}};
  s21_decimal_set_pow(&src, 1);
  int result;
  int expected = 4913564;
  int returned = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  s21_decimal src = {{0, 0, 0, 0}};
  s21_decimal_set_pow(&src, 1);
  int result;
  int expected = 0;
  int returned = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  s21_decimal src = {{0, 0, 0, 0}};
  s21_decimal_set_bit(&src, 127, 1);
  s21_decimal_set_pow(&src, 1);
  int result;
  int expected = -0;
  int returned = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_decimal_to_int_5) {
  s21_decimal src = {{0, 0, 0, 0}};
  int returned = s21_from_decimal_to_int(src, NULL);
  ck_assert_int_eq(returned, CONVERTATION_ERROR);
}
END_TEST

Suite *s21_decimal_to_int_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_from_decimal_to_int");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_from_decimal_to_int_1);
  tcase_add_test(tc_core, s21_from_decimal_to_int_2);
  tcase_add_test(tc_core, s21_from_decimal_to_int_3);
  tcase_add_test(tc_core, s21_from_decimal_to_int_4);
  tcase_add_test(tc_core, s21_from_decimal_to_int_5);
  suite_add_tcase(s, tc_core);
  return s;
}
