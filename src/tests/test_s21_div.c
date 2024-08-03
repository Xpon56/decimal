#include "test.h"

START_TEST(div_null_div_test_val2) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);

  val_1.bits[0] = 129345;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_NULL_DIV_ERROR);
}
END_TEST

START_TEST(div_null_div_test_val1) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);

  val_2.bits[0] = 1757593;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(div_one_div_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 120595034;
  val_2.bits[0] = 1;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(s21_is_equal(val_1, result), s21_TRUE);
}
END_TEST

START_TEST(div_one_div_test_decimal_2ints) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 120595034;
  val_1.bits[1] = 65478;
  val_2.bits[0] = 1;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(s21_is_equal(val_1, result), s21_TRUE);
}
END_TEST

START_TEST(div_one_div_test_decimal_3ints) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 120595034;
  val_1.bits[1] = 65478;
  val_1.bits[1] = 1238475;
  val_2.bits[0] = 1;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(s21_is_equal(val_1, result), s21_TRUE);
}
END_TEST

START_TEST(div_minus_one_div_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 120595034;
  val_2.bits[0] = 1;
  s21_decimal_set_bit(&val_2, 127, 1);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);
  s21_decimal_set_bit(&val_1, 127, 1);
  ck_assert_int_eq(s21_is_equal(val_1, result), s21_TRUE);
}
END_TEST

START_TEST(div_minus_to_minus_one_div_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 120595034;
  val_2.bits[0] = 1;
  s21_decimal_set_bit(&val_1, 127, 1);
  s21_decimal_set_bit(&val_2, 127, 1);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);
  s21_decimal_set_bit(&val_1, 127, 0);
  ck_assert_int_eq(s21_is_equal(val_1, result), s21_TRUE);
}
END_TEST

START_TEST(div_minus_one_div_test_val1) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 120595034;
  val_2.bits[0] = 1;
  s21_decimal_set_bit(&val_1, 127, 1);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(s21_is_equal(val_1, result), s21_TRUE);
}
END_TEST

START_TEST(div_4_div_2_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 4;
  val_2.bits[0] = 2;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(div_2_div_4_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 2;
  val_2.bits[0] = 4;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(s21_decimal_get_pow(result), 1);  // 0.5
}
END_TEST

START_TEST(div_self_div_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 12356612;
  val_2.bits[0] = 12356612;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);
  s21_decimal one;
  s21_decimal_null(&one);
  one.bits[0] = 1;
  ck_assert_int_eq(s21_is_equal(result, one), s21_TRUE);
}
END_TEST

START_TEST(div_self_div_test_2ints) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 12356612;
  val_1.bits[1] = 12356612;
  val_2.bits[0] = 12356612;
  val_2.bits[1] = 12356612;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);
  s21_decimal one;
  s21_decimal_null(&one);
  one.bits[0] = 1;
  ck_assert_int_eq(s21_is_equal(result, one), s21_TRUE);
}
END_TEST

START_TEST(div_self_div_test_3ints) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 12356612;
  val_1.bits[1] = 12356612;
  val_1.bits[2] = 12356612;
  val_2.bits[0] = 12356612;
  val_2.bits[1] = 12356612;
  val_2.bits[2] = 12356612;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);
  s21_decimal one;
  s21_decimal_null(&one);
  one.bits[0] = 1;
  ck_assert_int_eq(s21_is_equal(result, one), s21_TRUE);
}
END_TEST

START_TEST(div_minus_to_minus_self_div_test_3ints) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 12356612;
  val_1.bits[1] = 12356612;
  val_1.bits[2] = 12356612;
  val_2.bits[0] = 12356612;
  val_2.bits[1] = 12356612;
  val_2.bits[2] = 12356612;
  s21_decimal_set_bit(&val_1, 127, 1);
  s21_decimal_set_bit(&val_2, 127, 1);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);
  s21_decimal one;
  s21_decimal_null(&one);
  one.bits[0] = 1;
  ck_assert_int_eq(s21_is_equal(result, one), s21_TRUE);
}
END_TEST

START_TEST(div_minus_val1_self_div_test_3ints) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 12356612;
  val_1.bits[1] = 12356612;
  val_1.bits[2] = 12356612;
  val_2.bits[0] = 12356612;
  val_2.bits[1] = 12356612;
  val_2.bits[2] = 12356612;
  s21_decimal_set_bit(&val_1, 127, 1);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);
  s21_decimal minus_one;
  s21_decimal_null(&minus_one);
  minus_one.bits[0] = 1;
  s21_decimal_set_bit(&minus_one, 127, 1);
  ck_assert_int_eq(s21_is_equal(result, minus_one), s21_TRUE);
}
END_TEST

START_TEST(div_minus_val2_self_div_test_3ints) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 12356612;
  val_1.bits[1] = 12356612;
  val_1.bits[2] = 12356612;
  val_2.bits[0] = 12356612;
  val_2.bits[1] = 12356612;
  val_2.bits[2] = 12356612;
  s21_decimal_set_bit(&val_2, 127, 1);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);
  s21_decimal minus_one;
  s21_decimal_null(&minus_one);
  minus_one.bits[0] = 1;
  s21_decimal_set_bit(&minus_one, 127, 1);
  ck_assert_int_eq(s21_is_equal(result, minus_one), s21_TRUE);
}
END_TEST

START_TEST(div_100_div_2_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 100;
  val_2.bits[0] = 2;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 50);
}
END_TEST

START_TEST(div_minus_100_div_2_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 100;
  val_2.bits[0] = 2;

  s21_decimal_set_bit(&val_1, 127, 1);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(s21_decimal_get_bit(result, 127), 1);
}
END_TEST

START_TEST(div_100_div_minus_2_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 100;
  val_2.bits[0] = 2;

  s21_decimal_set_bit(&val_2, 127, 1);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(s21_decimal_get_bit(result, 127), 1);
}
END_TEST

START_TEST(div_2_div_100_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 2;
  val_2.bits[0] = 100;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(s21_decimal_get_pow(result), 2);
}
END_TEST

START_TEST(div_2_div_1000_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 2;
  val_2.bits[0] = 1000;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(s21_decimal_get_pow(result), 3);
}
END_TEST

START_TEST(div_2_div_10000_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 2;
  val_2.bits[0] = 10000;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(s21_decimal_get_pow(result), 4);
}
END_TEST

START_TEST(div_100_div_10_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 100;
  val_2.bits[0] = 10;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(s21_decimal_get_pow(result), 0);
}
END_TEST

START_TEST(div_1000_div_10_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 1000;
  val_2.bits[0] = 10;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(s21_decimal_get_pow(result), 0);
}
END_TEST

START_TEST(div_10_div_100_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 10;
  val_2.bits[0] = 100;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_decimal_get_pow(result), 1);
}
END_TEST

START_TEST(div_10_div_1000_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 10;
  val_2.bits[0] = 1000;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_decimal_get_pow(result), 2);
}
END_TEST

START_TEST(div_4_div_3_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 4;
  val_2.bits[0] = 3;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_decimal_get_pow(result), 0);
}
END_TEST

START_TEST(div_40_div_3_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 40;
  val_2.bits[0] = 3;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 13);
  ck_assert_int_eq(s21_decimal_get_pow(result), 0);
}
END_TEST

START_TEST(div_400_div_3_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 400;
  val_2.bits[0] = 3;

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 133);
  ck_assert_int_eq(s21_decimal_get_pow(result), 0);
}
END_TEST

START_TEST(div_5_3_div_2_3_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 5;
  val_2.bits[0] = 2;

  s21_decimal_set_pow(&val_1, 3);
  s21_decimal_set_pow(&val_2, 3);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(s21_decimal_get_pow(result), 0);
}
END_TEST

START_TEST(div_5_3_div_2_6_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 5;
  val_2.bits[0] = 2;

  s21_decimal_set_pow(&val_1, 3);
  s21_decimal_set_pow(&val_2, 6);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 2000);
  ck_assert_int_eq(s21_decimal_get_pow(result), 0);
}
END_TEST

START_TEST(div_5_3_div_2_0_test) {
  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal result;

  s21_decimal_null(&val_1);
  s21_decimal_null(&val_2);
  s21_decimal_null(&result);
  val_1.bits[0] = 5;
  val_2.bits[0] = 2;

  s21_decimal_set_pow(&val_1, 3);
  s21_decimal_set_pow(&val_2, 0);

  int returned = s21_div(val_1, val_2, &result);

  ck_assert_int_eq(returned, s21_OK);

  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(s21_decimal_get_pow(result), 3);
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s = suite_create("S21_DIV_TESTS");
  TCase *tc = tcase_create("S21_DIV_CASE");

  tcase_add_test(tc, div_null_div_test_val2);
  tcase_add_test(tc, div_null_div_test_val1);
  tcase_add_test(tc, div_one_div_test);
  tcase_add_test(tc, div_one_div_test_decimal_2ints);
  tcase_add_test(tc, div_one_div_test_decimal_3ints);
  tcase_add_test(tc, div_minus_one_div_test);
  tcase_add_test(tc, div_minus_to_minus_one_div_test);
  tcase_add_test(tc, div_minus_one_div_test_val1);
  tcase_add_test(tc, div_4_div_2_test);
  tcase_add_test(tc, div_2_div_4_test);
  tcase_add_test(tc, div_self_div_test);
  tcase_add_test(tc, div_self_div_test_2ints);
  tcase_add_test(tc, div_self_div_test_3ints);
  tcase_add_test(tc, div_minus_to_minus_self_div_test_3ints);
  tcase_add_test(tc, div_minus_val1_self_div_test_3ints);
  tcase_add_test(tc, div_minus_val2_self_div_test_3ints);
  tcase_add_test(tc, div_100_div_2_test);
  tcase_add_test(tc, div_minus_100_div_2_test);
  tcase_add_test(tc, div_100_div_minus_2_test);
  tcase_add_test(tc, div_2_div_100_test);
  tcase_add_test(tc, div_2_div_1000_test);
  tcase_add_test(tc, div_2_div_10000_test);
  tcase_add_test(tc, div_100_div_10_test);
  tcase_add_test(tc, div_1000_div_10_test);
  tcase_add_test(tc, div_10_div_100_test);
  tcase_add_test(tc, div_10_div_1000_test);
  tcase_add_test(tc, div_4_div_3_test);
  tcase_add_test(tc, div_40_div_3_test);
  tcase_add_test(tc, div_400_div_3_test);
  tcase_add_test(tc, div_5_3_div_2_3_test);
  tcase_add_test(tc, div_5_3_div_2_6_test);
  tcase_add_test(tc, div_5_3_div_2_0_test);

  suite_add_tcase(s, tc);

  return s;
}
