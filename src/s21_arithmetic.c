#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int returned = 0;
  int sign_1 = s21_get_bit(value_1.bits[3], 31);
  int sign_2 = s21_get_bit(value_2.bits[3], 31);

  if (sign_1 != sign_2) {
    if (sign_1) {
      s21_set_sign(&value_1, 0);
      returned = s21_sub(value_2, value_1, result);
    } else {
      s21_set_sign(&value_2, 0);
      returned = s21_sub(value_1, value_2, result);
    }
  } else {
    s21_big_decimal big_value_1 = big_decimal(value_1),
                    big_value_2 = big_decimal(value_2), big_result;
    big_decimal_set_zero(&big_result);
    s21_big_add(big_value_1, big_value_2, &big_result);
    if (big_value_1.sign == 1 && big_value_2.sign == 1) {
      big_result.sign = 1;
    }
    returned = decimal_from_big(big_result, result);
  }

  return returned;
}

void s21_big_add(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result) {
  same_scale(&big_value_1, &big_value_2);
  int temp = 0;
  for (int i = 0; i < 6; i++) {
    unsigned long long add =
        (unsigned long long)big_value_1.bits[i] + big_value_2.bits[i] + temp;
    big_result->bits[i] = add & 0b11111111111111111111111111111111;
    temp = add >> 32;
  }
  big_result->scale = big_value_1.scale;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int returned = 0;
  int sign_1 = s21_get_bit(value_1.bits[3], 31);
  int sign_2 = s21_get_bit(value_2.bits[3], 31);

  if (sign_1 != sign_2) {
    s21_set_sign(&value_2, sign_1);
    returned = s21_add(value_1, value_2, result);
  } else if (sign_1 == 1 && sign_2 == 1) {
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    returned = s21_sub(value_2, value_1, result);
  } else {
    s21_big_decimal big_value_1 = big_decimal(value_1),
                    big_value_2 = big_decimal(value_2), big_result;
    big_decimal_set_zero(&big_result);
    if (s21_is_greater_or_equal(value_1, value_2)) {
      s21_big_sub(big_value_1, big_value_2, &big_result);
    } else {
      s21_big_sub(big_value_2, big_value_1, &big_result);
      big_result.sign = 1;
    }
    returned = decimal_from_big(big_result, result);
  }

  return returned;
}

void s21_big_sub(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result) {
  same_scale(&big_value_1, &big_value_2);
  int borrowed_number = 0;
  for (int i = 0; i < 6; i++) {
    unsigned long long sub =
        big_value_1.bits[i] -
        ((unsigned long long)big_value_2.bits[i] + borrowed_number);
    if (big_value_1.bits[i] <
        ((unsigned long long)big_value_2.bits[i] + borrowed_number)) {
      sub = sub + (1ULL << 32);
      borrowed_number = 1;
    } else {
      borrowed_number = 0;
    }
    big_result->bits[i] = (unsigned int)sub;
  }
  big_result->scale = big_value_1.scale;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int returned = s21_OK;
  s21_decimal_null(result);
  if (s21_decimal_get_pow(value_1) == 0 && s21_decimal_get_pow(value_2) == 0) {
    returned = s21_decimal_integer_div(value_1, value_2, result);
  } else {
    returned = s21_decimal_float_div(value_1, value_2, result);
  }
  return returned;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int returned = s21_OK;
  s21_decimal_null(result);
  if (s21_decimal_get_pow(value_1) == 0 && s21_decimal_get_pow(value_2) == 0) {
    returned = s21_decimal_integer_mul(value_1, value_2, result);
  } else {
    returned = s21_decimal_float_mul(value_1, value_2, result);
  }
  return returned;
}

int s21_decimal_integer_mul(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result) {
  int returned = s21_OK;

  s21_decimal decimal_plus1;
  s21_decimal_null(&decimal_plus1);
  s21_decimal decimal_minus1;
  s21_decimal_null(&decimal_minus1);
  decimal_plus1.bits[0] = 1;
  decimal_minus1.bits[0] = 1;
  s21_decimal_set_bit(&decimal_minus1, 127, 1);

  if (s21_decimal_first_mean_bit(value_1) +
          s21_decimal_first_mean_bit(value_2) >
      95) {
    returned = s21_LARGE_ERROR;
  } else if (s21_decimal_is_null(value_1) || s21_decimal_is_null(value_2)) {
    s21_decimal_null(result);
    s21_decimal_set_pow(result, 0);

  } else if (s21_is_equal(value_1, decimal_plus1) ||
             s21_is_equal(value_1, decimal_minus1)) {
    s21_decimal_copy_value_of_decimal(value_2, result);
    s21_decimal_set_bit(result, 127,
                        (s21_decimal_get_bit(value_1, 127) ^
                         s21_decimal_get_bit(value_2, 127)));

  } else if (s21_is_equal(value_2, decimal_plus1) ||
             s21_is_equal(value_2, decimal_minus1)) {
    s21_decimal_copy_value_of_decimal(value_1, result);
    s21_decimal_set_bit(result, 127,
                        (s21_decimal_get_bit(value_1, 127) ^
                         s21_decimal_get_bit(value_2, 127)));

  } else {
    for (int i = 0; i <= s21_decimal_first_mean_bit(value_2); i++) {
      if (s21_decimal_get_bit(value_2, i) != 0) {
        s21_decimal temp = value_1;
        while (!s21_decimal_is_null(temp)) {
          s21_decimal remainder;
          s21_decimal_binary_and(*result, temp, &remainder);
          s21_decimal_left_shift(&remainder, 1);
          s21_decimal_binary_xor(*result, temp, result);
          temp = remainder;
        }
      }
      s21_decimal_left_shift(&value_1, 1);
    }
  }
  s21_decimal_set_bit(result, 127,
                      (s21_decimal_get_bit(value_1, 127) ^
                       s21_decimal_get_bit(value_2, 127)));  // Учет знака
  return returned;
}

int s21_decimal_float_mul(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result) {
  int returned = s21_OK;

  int res_pow = s21_decimal_get_pow(value_1) + s21_decimal_get_pow(value_2);
  if (res_pow >= 28) {
    returned = s21_SMALL_ERROR;
  } else {
    s21_decimal_set_pow(&value_1, 0);
    s21_decimal_set_pow(&value_2, 0);
    s21_decimal_set_pow(result, res_pow);
    s21_decimal_integer_mul(value_1, value_2, result);
  }
  return returned;
}

int s21_decimal_integer_div(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result) {
  int returned = s21_OK;

  s21_decimal decimal_plus1;
  s21_decimal_null(&decimal_plus1);
  s21_decimal decimal_minus1;
  s21_decimal_null(&decimal_minus1);
  decimal_plus1.bits[0] = 1;
  decimal_minus1.bits[0] = 1;
  s21_decimal_set_bit(&decimal_minus1, 127, 1);

  if (s21_decimal_is_null(value_2)) {
    returned = s21_NULL_DIV_ERROR;

  } else if (s21_is_equal(value_2, decimal_plus1) ||
             s21_is_equal(value_2, decimal_minus1)) {
    s21_decimal_copy_value_of_decimal(value_1, result);
    s21_decimal_set_bit(result, 127,
                        (s21_decimal_get_bit(value_1, 127) ^
                         s21_decimal_get_bit(value_2, 127)));

  } else if (value_1.bits[0] == value_2.bits[0] &&
             value_1.bits[1] == value_2.bits[1] &&
             value_1.bits[2] == value_2.bits[2]) {
    result->bits[0] = 1;
    s21_decimal_set_bit(result, 127,
                        (s21_decimal_get_bit(value_1, 127) ^
                         s21_decimal_get_bit(value_2, 127)));

  } else if (s21_decimal_is_null(value_1)) {
    s21_decimal_null(result);

  } else {
    s21_decimal temp_val1;
    s21_decimal_null(&temp_val1);
    s21_decimal_copy_value_of_decimal(value_1, &temp_val1);
    while (s21_decimal_first_mean_bit(temp_val1) <
           s21_decimal_first_mean_bit(value_2)) {
      s21_decimal_integer_mul(temp_val1, s21_decimal_ten_pows[1], &temp_val1);
      s21_decimal_set_pow(result, s21_decimal_get_pow(*result) + 1);
    }

    int len_1 = s21_decimal_first_mean_bit(temp_val1);
    int len_2 = s21_decimal_first_mean_bit(value_2);

    s21_decimal_left_shift(&value_2, len_1 - len_2);
    int overflow = 0;
    s21_decimal remainder;
    int remainder_len = 0;
    s21_decimal_null(&remainder);
    for (int i = 0; i <= len_1 - len_2; i++) {
      s21_decimal cutout_1 = s21_decimal_get_decimal_from_indexes(
          temp_val1, len_1 - i + overflow + remainder_len, len_1 - len_2 - i);
      s21_decimal cutout_2 = s21_decimal_get_decimal_from_indexes(
          value_2, len_1 - i, len_1 - len_2 - i);
      if (s21_is_less(cutout_1, cutout_2)) {
        s21_decimal_left_shift(result, 1);
        s21_decimal_set_bit(result, 0, 0);
        overflow++;
      } else {
        s21_decimal_left_shift(result, 1);
        s21_decimal_set_bit(result, 0, 1);
        s21_decimal_indexes_sub(cutout_1, cutout_2, &remainder);

        remainder_len = (s21_decimal_first_mean_bit(remainder) == -1
                             ? 0
                             : s21_decimal_first_mean_bit(remainder));
        int paste_index = len_1 - len_2 - i + remainder_len;
        s21_decimal_set_decimal_from_indexes(remainder, &temp_val1, paste_index,
                                             len_1 - len_2 - i);
        temp_val1 =
            s21_decimal_nulling_at_index(temp_val1, 95, paste_index + 1);

        overflow = 0;
      }
      s21_decimal_right_shift(&value_2, 1);
    }
    s21_decimal_set_bit(result, 127,
                        (s21_decimal_get_bit(value_1, 127) ^
                         s21_decimal_get_bit(value_2, 127)));
  }
  return returned;
}

int s21_decimal_float_div(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result) {
  int returned = s21_OK;

  int pow_1 = s21_decimal_get_pow(value_1);
  int pow_2 = s21_decimal_get_pow(value_2);

  s21_decimal_set_pow(&value_1, 0);
  s21_decimal_set_pow(&value_2, 0);

  returned = s21_decimal_integer_div(value_1, value_2, result);

  int result_pow = s21_decimal_get_pow(*result) + pow_1 - pow_2;
  s21_decimal_set_pow(result, 0);

  if (result_pow < 0) {
    s21_mul(*result, s21_decimal_ten_pows[result_pow * (-1)], result);
    result_pow = 0;
  }

  s21_decimal_set_pow(result, result_pow);
  return returned;
}
