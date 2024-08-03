#include "test.h"

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_decimal expected = {{9, 0, 0, 0}};
  s21_decimal_set_bit(&expected, 127, 1);
  s21_decimal_set_pow(&expected, 1);
  float src = -0.9;
  int returned = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(s21_is_equal(expected, dst), s21_TRUE);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_decimal_set_pow(&expected, 1);
  float src = 0.1;
  int returned = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(s21_is_equal(expected, dst), s21_TRUE);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 0}};
  s21_decimal_set_pow(&expected, 5);
  float src = 0.00005;
  int returned = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(s21_is_equal(expected, dst), s21_TRUE);
  ck_assert_int_eq(returned, CONVERTATION_OK);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 0}};
  s21_decimal_set_pow(&expected, 5);
  float src = 0.5;
  s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(s21_is_equal(expected, dst), s21_FALSE);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  float src = 0.5;
  int returned = s21_from_float_to_decimal(src, NULL);
  ck_assert_int_eq(returned, CONVERTATION_ERROR);
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  s21_decimal dst = {{0, 0, 0, 0}};
  int returned = s21_from_float_to_decimal((float)NAN, &dst);
  ck_assert_int_eq(returned, CONVERTATION_ERROR);
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
  s21_decimal dst = {{0, 0, 0, 0}};
  int returned = s21_from_float_to_decimal((float)INFINITY, &dst);
  ck_assert_int_eq(returned, CONVERTATION_ERROR);
}
END_TEST

Suite *s21_float_to_decimal_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_from_float_to_decimal");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_from_float_to_decimal_1);
  tcase_add_test(tc_core, s21_from_float_to_decimal_2);
  tcase_add_test(tc_core, s21_from_float_to_decimal_3);
  tcase_add_test(tc_core, s21_from_float_to_decimal_4);
  tcase_add_test(tc_core, s21_from_float_to_decimal_5);
  tcase_add_test(tc_core, s21_from_float_to_decimal_6);
  tcase_add_test(tc_core, s21_from_float_to_decimal_7);
  suite_add_tcase(s, tc_core);
  return s;
}
