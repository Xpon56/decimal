#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int returned = s21_OK;
  if (!result) {
    returned = s21_CALCULATION_ERROR;
  } else {
    s21_decimal_null(result);
    s21_decimal temp = {0};
    s21_truncate(value, &temp);
    if (s21_get_bit(temp.bits[3], 31) == 1) {
      s21_decimal plus = {0};
      plus.bits[0] = 1;
      s21_decimal_set_bit(&plus, 127, 1);
      s21_add(temp, plus, &temp);
    }
    *result = temp;
  }
  return returned;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int returned = s21_OK;
  if (!result) {
    returned = s21_CALCULATION_ERROR;
  } else {
    int pow_value = s21_decimal_get_pow(value);
    int sign_value = s21_decimal_get_bit(value, 127);
    for (int i = 0; i < pow_value; i++) {
      if (i == pow_value - 1) {
        unsigned int div_remainder = s21_div_by_10(&value);
        if (div_remainder >= 5) {
          if (value.bits[0] + 1u < value.bits[0]) {
            if (value.bits[1] + 1u < value.bits[1]) {
              value.bits[2] += 1u;
            } else {
              value.bits[1] += 1u;
            }

          } else {
            value.bits[0] += 1u;
          }
        }
      } else {
        s21_div_by_10(&value);
      }
    }

    *result = value;

    s21_decimal_set_bit(result, 127, sign_value);
    s21_decimal_set_pow(result, 0);
  }

  return returned;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int returned = s21_OK;
  if (!result) {
    returned = s21_CALCULATION_ERROR;
  } else {
    s21_big_decimal big_value = big_decimal(value);
    int scale = big_value.scale;
    divide_by_ten(&big_value, scale);
    decimal_from_big(big_value, result);
  }
  return returned;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int returned = s21_OK;
  if (!result) {
    returned = s21_CALCULATION_ERROR;
  } else {
    s21_set_bit(&result->bits[3], 31, !s21_get_bit(value.bits[3], 31));
  }
  return returned;
}