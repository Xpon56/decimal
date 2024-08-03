#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int returned = s21_FALSE;
  if ((value_1.bits[2] == value_2.bits[2]) &&
      (value_1.bits[1] == value_2.bits[1]) &&
      (value_1.bits[0] == value_2.bits[0]) &&
      (value_1.bits[3] == value_2.bits[3])) {
    returned = s21_TRUE;
  }
  return returned;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_big_is_greater(s21_big_decimal big_value_1,
                       s21_big_decimal big_value_2) {
  int returned = s21_FALSE;
  int sign_1 = big_value_1.sign, sign_2 = big_value_2.sign;
  if (sign_1 != sign_2) {
    returned = !sign_1;
  } else if (sign_1 == 1 && sign_2 == 1) {
    big_value_1.sign = 0;
    big_value_2.sign = 0;
    returned = s21_big_is_greater(big_value_2, big_value_1);
  } else {
    same_scale(&big_value_1, &big_value_2);
    int end = 0;
    for (int i = 5; i >= 0 && !end; i--) {
      if (big_value_1.bits[i] != big_value_2.bits[i]) {
        returned = big_value_1.bits[i] > big_value_2.bits[i];
        end = 1;
      }
    }
  }
  return returned;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_value_1 = big_decimal(value_1),
                  big_value_2 = big_decimal(value_2);
  return s21_big_is_greater(big_value_1, big_value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_equal(value_1, value_2) || s21_is_greater(value_1, value_2));
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_greater_or_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_greater(value_1, value_2);
}
