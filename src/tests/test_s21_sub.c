#include "test.h"

START_TEST(test_sub_1) {
  s21_decimal decimal1 = {{200, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x00000000}};
  s21_decimal check_res = {{100, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_2) {
  s21_decimal decimal1 = {{200, 0, 0, 0x80000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x00000000}};
  s21_decimal check_res = {{300, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_3) {
  s21_decimal decimal1 = {{200, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{300, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_4) {
  s21_decimal decimal1 = {{200, 0, 0, 0x80000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{100, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_5) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{200, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_6) {
  // 7.92281625142643375935439503
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 3.9614081257132168796771975172
  s21_decimal check_res = {{0x4, 0x0, 0x80000000, 0x1C0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal check_res = {{0, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_8) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal check_res = {{0, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_10) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_12) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_13) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_14) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_17) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -79228162514264337593517540948
  s21_decimal check_res = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_18) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950333
  s21_decimal check_res = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_19) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_20) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_21) {
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

Suite *s21_sub_suite(void) {
  Suite *s = suite_create("s21_sub");
  TCase *tc = tcase_create("s21_sub");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_sub_1);
  tcase_add_test(tc, test_sub_2);
  tcase_add_test(tc, test_sub_3);
  tcase_add_test(tc, test_sub_4);
  tcase_add_test(tc, test_sub_5);
  tcase_add_test(tc, test_sub_6);
  tcase_add_test(tc, test_sub_7);
  tcase_add_test(tc, test_sub_8);
  tcase_add_test(tc, test_sub_9);
  tcase_add_test(tc, test_sub_10);
  tcase_add_test(tc, test_sub_11);
  tcase_add_test(tc, test_sub_12);
  tcase_add_test(tc, test_sub_13);
  tcase_add_test(tc, test_sub_14);
  tcase_add_test(tc, test_sub_15);
  tcase_add_test(tc, test_sub_16);
  tcase_add_test(tc, test_sub_17);
  tcase_add_test(tc, test_sub_18);
  tcase_add_test(tc, test_sub_19);
  tcase_add_test(tc, test_sub_20);
  tcase_add_test(tc, test_sub_21);
  return s;
}
