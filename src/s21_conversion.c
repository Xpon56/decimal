#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int returned = CONVERTATION_OK;
  if (abs(src) > s21_MAX_DEC) {
    returned = CONVERTATION_ERROR;
  }
  s21_decimal_null(dst);
  if (src < 0) {
    src = -1 * src;
    s21_set_bit(&dst->bits[3], 31, 1);
  }
  dst->bits[0] = src;
  return returned;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int returned = CONVERTATION_OK;
  if (dst) {
    if (s21_get_bit(src.bits[3], 31) == 1) {
      *dst = -1 * (int)(src.bits[0] / pow(10, s21_decimal_get_pow(src)));
    } else {
      *dst = (int)(src.bits[0] / pow(10, s21_decimal_get_pow(src)));
    }
  } else {
    returned = CONVERTATION_ERROR;
  }
  return returned;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int returned = CONVERTATION_OK;
  if (isnan(src) || isinf(src)) {
    returned = CONVERTATION_ERROR;
  }
  if (dst != NULL && !returned) {
    s21_decimal_null(dst);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = -1 * src;
    }
    int ipart = (int)src;
    int exp = 0;
    while (src - ((float)ipart / (int)(pow(10, exp))) != 0) {
      exp++;
      ipart = src * (int)(pow(10, exp));
    }
    s21_from_int_to_decimal(ipart, dst);
    if (sign) {
      s21_negate(*dst, dst);
    }
    s21_decimal_set_pow(dst, exp);
  } else {
    returned = CONVERTATION_ERROR;
  }
  return returned;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int returned = CONVERTATION_OK;
  if (dst == NULL) {
    returned = CONVERTATION_ERROR;
  } else {
    *dst = 0;
    for (int i = 0; i < 96; i++) {
      if (s21_decimal_get_bit(src, i)) {
        *dst += pow(2, i);
      }
    }
    *dst = *dst * pow(10, -s21_decimal_get_pow(src));
    if (s21_get_bit(src.bits[3], 31) == 1) {
      *dst = -*dst;
    }
  }
  return returned;
}
