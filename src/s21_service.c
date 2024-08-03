#include "s21_decimal.h"

int s21_get_bit(int number, int position) {
  int temp = (number & (1 << position)) >> position;
  return temp >= 0 ? temp : temp * -1;
}

void s21_set_bit(unsigned *number, int position, int value) {
  *number = s21_get_bit(*number, position) ? *number ^ (!value << position)
                                           : *number | (value << position);
}

int s21_decimal_get_bit(s21_decimal decimal, int position) {
  int result;
  if (position <= 31) {
    result = s21_get_bit(decimal.bits[0], position);
  } else if (position <= 63) {
    result = s21_get_bit(decimal.bits[1], position);
  } else if (position <= 95) {
    result = s21_get_bit(decimal.bits[2], position);
  } else if (position <= 127) {
    result = s21_get_bit(decimal.bits[3], position);
  }
  return (int)result;
}

void s21_decimal_set_bit(s21_decimal *decimal, int position, int value) {
  if (position <= 31) {
    s21_set_bit(&decimal->bits[0], position, value);
  } else if (position <= 63) {
    s21_set_bit(&decimal->bits[1], position, value);
  } else if (position <= 95) {
    s21_set_bit(&decimal->bits[2], position, value);
  } else if (position <= 127) {
    s21_set_bit(&decimal->bits[3], position, value);
  }
}

void s21_decimal_left_shift(s21_decimal *decimal, int shifts) {
  for (int i = 0; i < shifts; i++) {
    decimal->bits[2] = decimal->bits[2] << 1;
    if (s21_get_bit(decimal->bits[1], 31)) decimal->bits[2]++;
    decimal->bits[1] = decimal->bits[1] << 1;
    if (s21_get_bit(decimal->bits[0], 31)) decimal->bits[1]++;
    decimal->bits[0] = decimal->bits[0] << 1;
  }
}

void s21_decimal_right_shift(s21_decimal *decimal, int shifts) {
  for (int i = 0; i < shifts; i++) {
    decimal->bits[0] = decimal->bits[0] >> 1;
    if (s21_get_bit(decimal->bits[1], 0)) decimal->bits[0] += 2147483648U;
    decimal->bits[1] = decimal->bits[1] >> 1;
    if (s21_get_bit(decimal->bits[2], 0)) decimal->bits[1] += 2147483648U;
    decimal->bits[2] = decimal->bits[2] >> 1;
  }
}

int s21_decimal_get_pow(s21_decimal value) { return value.bits[3] << 8 >> 24; }

void s21_decimal_set_pow(s21_decimal *decimal, int pow) {
  decimal->bits[3] &= 0b10000000000000000000000000000000;
  decimal->bits[3] += (pow << 16);
}

int s21_decimal_first_mean_bit(s21_decimal decimal) {
  int i = 95;
  for (; i > 0 && !s21_decimal_get_bit(decimal, i); i--)
    ;
  if (i == 0 && !s21_decimal_get_bit(decimal, 0)) i = -1;
  return i;
}

void s21_decimal_null(s21_decimal *decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}

int s21_decimal_is_null(s21_decimal decimal) {
  int returned = 0;
  if (decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0)
    returned = 1;
  return returned;
}

void s21_decimal_binary_and(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result) {
  s21_decimal_null(result);
  result->bits[0] = value_1.bits[0] & value_2.bits[0];
  result->bits[1] = value_1.bits[1] & value_2.bits[1];
  result->bits[2] = value_1.bits[2] & value_2.bits[2];
  result->bits[3] = value_1.bits[3] & value_2.bits[3];
}
void s21_decimal_binary_xor(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result) {
  s21_decimal_null(result);
  result->bits[0] = value_1.bits[0] ^ value_2.bits[0];
  result->bits[1] = value_1.bits[1] ^ value_2.bits[1];
  result->bits[2] = value_1.bits[2] ^ value_2.bits[2];
  result->bits[3] = value_1.bits[3] ^ value_2.bits[3];
}

s21_big_decimal big_decimal(s21_decimal value) {
  s21_big_decimal big_value;
  big_decimal_set_zero(&big_value);
  for (int i = 0; i < 3; i++) {
    big_value.bits[i] = value.bits[i];
  }
  big_value.sign = s21_get_bit(value.bits[3], 31);
  big_value.scale = s21_decimal_get_pow(value);
  return big_value;
}

void big_decimal_set_zero(s21_big_decimal *big_value) {
  big_value->sign = 0;
  big_value->scale = 0;
  for (int i = 0; i < 6; i++) {
    big_value->bits[i] = 0;
  }
}

void same_scale(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2) {
  if (big_value_1->scale > big_value_2->scale) {
    scale_up(big_value_2, (big_value_1->scale - big_value_2->scale));
    big_value_2->scale = big_value_1->scale;
  } else if (big_value_2->scale > big_value_1->scale) {
    scale_up(big_value_1, (big_value_2->scale - big_value_1->scale));
    big_value_1->scale = big_value_2->scale;
  }
}

void scale_up(s21_big_decimal *big_value, int dif) {
  if (dif > 0) {
    big_value->scale = big_value->scale + dif;
    int temp = 0;
    while (dif != 0) {
      temp = 0;
      for (int i = 0; i < 6; i++) {
        unsigned long long sum =
            (unsigned long long)big_value->bits[i] * 10 + temp;
        big_value->bits[i] = (int)(sum & 0b11111111111111111111111111111111);
        temp = (int)(sum >> 32);
      }
      dif--;
    }
  }
}

s21_decimal s21_decimal_nulling_at_index(s21_decimal decimal, int index,
                                         int end_index) {
  s21_decimal returned = decimal;
  for (int i = end_index; i <= index; i++) {
    s21_decimal_set_bit(&returned, i, 0);
  }
  return returned;
}

s21_decimal s21_decimal_get_decimal_from_indexes(s21_decimal decimal, int index,
                                                 int end_index) {
  s21_decimal result = decimal;
  result = s21_decimal_nulling_at_index(result, 127, index + 1);
  result = s21_decimal_nulling_at_index(result, end_index - 1, 0);
  s21_decimal_right_shift(&result, end_index);

  return result;
}

void s21_decimal_set_decimal_from_indexes(s21_decimal value,
                                          s21_decimal *target, int index,
                                          int end_index) {
  int length_value = s21_decimal_first_mean_bit(value);
  if (index >= end_index) {
    for (int i = index; i >= end_index; i--) {
      s21_decimal_set_bit(
          target, i, s21_decimal_get_bit(value, i - (index - length_value)));
    }
  }
}

void s21_decimal_copy_value_of_decimal(s21_decimal src, s21_decimal *dest) {
  dest->bits[0] = src.bits[0];
  dest->bits[1] = src.bits[1];
  dest->bits[2] = src.bits[2];
}

void s21_decimal_binary_inversion_by_index(s21_decimal *decimal, int index,
                                           int end_index) {
  for (int i = end_index; i <= index; i++) {
    s21_decimal_set_bit(decimal, i, s21_decimal_get_bit(*decimal, i) ^ 1);
  }
}

void s21_decimal_indexes_sub(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result) {
  int len_1 = s21_decimal_first_mean_bit(value_1);

  s21_decimal_binary_inversion_by_index(&value_1, len_1, 0);

  s21_decimal temp = value_2;
  s21_decimal_copy_value_of_decimal(value_1, result);
  while (!s21_decimal_is_null(temp)) {
    s21_decimal remainder;
    s21_decimal_binary_and(*result, temp, &remainder);
    s21_decimal_left_shift(&remainder, 1);
    s21_decimal_binary_xor(*result, temp, result);
    temp = remainder;
  }

  s21_decimal_binary_inversion_by_index(result, len_1, 0);
}

void s21_decimal_indexes_add(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result) {
  s21_decimal temp = value_2;
  s21_decimal_copy_value_of_decimal(value_1, result);
  while (!s21_decimal_is_null(temp)) {
    s21_decimal remainder;
    s21_decimal_binary_and(*result, temp, &remainder);
    s21_decimal_left_shift(&remainder, 1);
    s21_decimal_binary_xor(*result, temp, result);
    temp = remainder;
  }
}

void s21_set_sign(s21_decimal *value, int sign) {
  value->bits[3] &= 0x7FFFFFFF;
  value->bits[3] |= sign << 31;
}

int decimal_from_big(s21_big_decimal big_value, s21_decimal *value) {
  int return_code = 0;
  bank_rounding(&big_value);
  if (big_value.bits[5] || big_value.bits[4] || big_value.bits[3]) {
    if (big_value.sign) {
      return_code = 2;
    } else {
      return_code = 1;
    }
  }
  if (big_value.scale > 28) {
    big_value.scale = 0;  // check!!
  }

  if (return_code == 0) {
    s21_decimal_null(value);
    for (int i = 0; i < 3; i++) {
      value->bits[i] = big_value.bits[i];
    }
    s21_decimal_set_pow(value, big_value.scale);
    s21_set_sign(value, big_value.sign);
  }

  return return_code;
}

void bank_rounding(s21_big_decimal *big_value) {
  s21_big_decimal big_copy;
  for (int i = 0; i < 6; i++) {
    big_copy.bits[i] = big_value->bits[i];
  }
  big_copy.sign = big_value->sign;
  big_copy.scale = big_value->scale;
  divide_by_ten(&big_copy, 1);
  while (((big_value->bits[3] || big_value->bits[4] || big_value->bits[5]) &&
          big_value->scale) ||
         (big_value->scale > 28 && !big_decimal_is_null(*big_value))) {
    int bank_round_flag = 0;
    int last_digit = divide_by_ten(big_value, 1);
    int next_digit = divide_by_ten(&big_copy, 1);
    if (last_digit > 5) {
      bank_round_flag = 1;
    } else if (last_digit == 5) {
      if (next_digit % 2 == 1) {
        bank_round_flag = 1;
      }
    }
    if (bank_round_flag) {
      int j = 0;
      while (++big_value->bits[j] == 0) {
        j++;
      }
    }
  }
}

int divide_by_ten(s21_big_decimal *big_value, int count) {
  int last_digit = 0;
  if (count > 0) {
    big_value->scale = big_value->scale - count;
    if (big_value->scale < 0) {
      big_value->scale = 0;
    }
    while (count--) {
      last_digit = 0;
      for (int i = 5; i >= 0; i--) {
        unsigned long long dividend =
            ((unsigned long long)last_digit << 32) | big_value->bits[i];
        big_value->bits[i] = (unsigned int)(dividend / 10);
        last_digit = (int)(dividend % 10);
      }
    }
  }
  return last_digit;
}

int big_decimal_is_null(s21_big_decimal big_value) {
  return (big_value.bits[0] == 0 && big_value.bits[1] == 0 &&
          big_value.bits[2] == 0 && big_value.bits[3] == 0 &&
          big_value.bits[4] == 0 && big_value.bits[5] == 0);
}

unsigned int s21_div_by_10(s21_decimal *number) {
  unsigned int remainder = 0;
  int pow_value = s21_decimal_get_pow(*number);
  s21_decimal result = {{0, 0, 0, 0}};
  int the_biggest_bit = s21_decimal_first_mean_bit(*number);
  for (int i = 0; i < the_biggest_bit + 2; i++) {
    if (remainder >= 10) {
      s21_decimal_left_shift(&result, 1);
      s21_set_bit(&result.bits[0], 0, 1);

      remainder = remainder - 10u;

      int bit = s21_decimal_get_bit(*number, the_biggest_bit - i);
      remainder = remainder << 1;
      s21_set_bit(&remainder, 0, bit);
    } else {
      s21_decimal_left_shift(&result, 1);
      s21_set_bit(&result.bits[0], 0, 0);

      int bit = s21_decimal_get_bit(*number, the_biggest_bit - i);
      remainder = remainder << 1;
      s21_set_bit(&remainder, 0, bit);
    }
  }
  remainder = remainder >> 1;
  *number = result;
  s21_decimal_set_pow(number, pow_value);

  return remainder;
}