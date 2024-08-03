#include "test.h"

START_TEST(test_round_1) {
  float exp_f = 2.0;
  float src_f = 2.1;
  s21_decimal expected;
  s21_decimal src;
  s21_decimal result;
  s21_from_float_to_decimal(exp_f, &expected);
  s21_from_float_to_decimal(src_f, &src);
  ck_assert_int_eq(s21_round(src, &result), s21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
}
END_TEST

START_TEST(test_round_2) {
  float exp_f = 10.0;
  float src_f = 9.999999;
  s21_decimal expected;
  s21_decimal src;
  s21_decimal result;
  s21_from_float_to_decimal(exp_f, &expected);
  s21_from_float_to_decimal(src_f, &src);
  ck_assert_int_eq(s21_round(src, &result), s21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
}
END_TEST

START_TEST(test_round_3) {
  float exp_f = -10.0;
  float src_f = -9.999999;
  s21_decimal expected;
  s21_decimal src;
  s21_decimal result;
  s21_from_float_to_decimal(exp_f, &expected);
  s21_from_float_to_decimal(src_f, &src);
  ck_assert_int_eq(s21_round(src, &result), s21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
}
END_TEST

START_TEST(test_round_4) {
  float exp_f = 0.0;
  float src_f = 0.001;
  s21_decimal expected;
  s21_decimal src;
  s21_decimal result;
  s21_from_float_to_decimal(exp_f, &expected);
  s21_from_float_to_decimal(src_f, &src);
  ck_assert_int_eq(s21_round(src, &result), s21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
}
END_TEST

START_TEST(test_round_5) {
  float exp_f = 0.0;
  float src_f = 0.0009;
  s21_decimal expected;
  s21_decimal src;
  s21_decimal result;
  s21_from_float_to_decimal(exp_f, &expected);
  s21_from_float_to_decimal(src_f, &src);
  ck_assert_int_eq(s21_round(src, &result), s21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
}
END_TEST

START_TEST(test_round_6) {
  float exp_f = 999.0;
  float src_f = 999.0005;
  s21_decimal expected;
  s21_decimal src;
  s21_decimal result;
  s21_from_float_to_decimal(exp_f, &expected);
  s21_from_float_to_decimal(src_f, &src);
  ck_assert_int_eq(s21_round(src, &result), s21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
}
END_TEST

START_TEST(test_round_7) {
  float exp_f = 10000.0;
  float src_f = 10000.0005;
  s21_decimal expected;
  s21_decimal src;
  s21_decimal result;
  s21_from_float_to_decimal(exp_f, &expected);
  s21_from_float_to_decimal(src_f, &src);
  ck_assert_int_eq(s21_round(src, &result), s21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
}
END_TEST

START_TEST(test_round_8) {
  float exp_f = 10000.0;
  float src_f = 10000.0;
  s21_decimal expected;
  s21_decimal src;
  s21_decimal result;
  s21_from_float_to_decimal(exp_f, &expected);
  s21_from_float_to_decimal(src_f, &src);
  ck_assert_int_eq(s21_round(src, &result), s21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
}
END_TEST

START_TEST(test_round_9) {
  float exp_f = 0.0;
  float src_f = 0.0;
  s21_decimal expected;
  s21_decimal src;
  s21_decimal result;
  s21_from_float_to_decimal(exp_f, &expected);
  s21_from_float_to_decimal(src_f, &src);
  ck_assert_int_eq(s21_round(src, &result), s21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), s21_TRUE);
}
END_TEST

START_TEST(test_round_10) {
  s21_decimal src = {{10, 0, 0, 0}};
  ck_assert_int_eq(s21_round(src, NULL), s21_CALCULATION_ERROR);
}
END_TEST

Suite *s21_round_suite(void) {
  Suite *s = suite_create("s21_round");
  TCase *tc = tcase_create("s21_round");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_round_1);
  tcase_add_test(tc, test_round_2);
  tcase_add_test(tc, test_round_3);
  tcase_add_test(tc, test_round_4);
  tcase_add_test(tc, test_round_5);
  tcase_add_test(tc, test_round_6);
  tcase_add_test(tc, test_round_7);
  tcase_add_test(tc, test_round_8);
  tcase_add_test(tc, test_round_9);
  tcase_add_test(tc, test_round_10);
  return s;
}