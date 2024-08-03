
#include "test.h"

START_TEST(test_1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_3) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_5) {
  // 52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_7) {
  // -52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_9) {
  // -5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_11) {
  // 1.0
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_13) {
  // -1.0
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_14) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_15) {
  // 0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_17) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_18) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_20) {
  // 1.0
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

START_TEST(test_21) {
  // 0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal1, decimal2));
}
END_TEST

Suite *s21_is_less_or_equal_suite(void) {
  Suite *s = suite_create("s21_is_less_or_equal");
  TCase *tc = tcase_create("s21_is_less_or_equal");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);
  tcase_add_test(tc, test_21);
  return s;
}
