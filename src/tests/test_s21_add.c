#include "test.h"

START_TEST(test_add_1) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{200, 0, 0, 0x00000000}};
  s21_decimal check_res = {{300, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_2) {
  s21_decimal decimal1 = {{200, 0, 0, 0x80000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x00000000}};
  s21_decimal check_res = {{100, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_3) {
  s21_decimal decimal1 = {{200, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{100, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_4) {
  s21_decimal decimal1 = {{200, 0, 0, 0x80000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{300, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_5) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{0, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_6) {
  // 7.92281625142643375935439503
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 11.884224377139650639031592551
  s21_decimal check_res = {{0x66666667, 0x66666666, 0x26666666, 0x1B0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_add_8) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_add_9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  s21_decimal check_res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_10) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  s21_decimal check_res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 71305346262837903834189555302
  s21_decimal check_res = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_12) {
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_add_13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_16) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_add_17) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 79228162514264337593543950326
  s21_decimal check_res = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_18) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_19) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950333
  s21_decimal check_res = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_20) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_21) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

Suite *s21_add_suite(void) {
  Suite *s = suite_create("s21_add");
  TCase *tc = tcase_create("s21_add");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_add_1);
  tcase_add_test(tc, test_add_2);
  tcase_add_test(tc, test_add_3);
  tcase_add_test(tc, test_add_4);
  tcase_add_test(tc, test_add_5);
  tcase_add_test(tc, test_add_6);
  tcase_add_test(tc, test_add_7);
  tcase_add_test(tc, test_add_8);
  tcase_add_test(tc, test_add_9);
  tcase_add_test(tc, test_add_10);
  tcase_add_test(tc, test_add_11);
  tcase_add_test(tc, test_add_12);
  tcase_add_test(tc, test_add_13);
  tcase_add_test(tc, test_add_14);
  tcase_add_test(tc, test_add_15);
  tcase_add_test(tc, test_add_16);
  tcase_add_test(tc, test_add_17);
  tcase_add_test(tc, test_add_18);
  tcase_add_test(tc, test_add_19);
  tcase_add_test(tc, test_add_20);
  tcase_add_test(tc, test_add_21);
  return s;
}
