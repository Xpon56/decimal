#ifndef _S21_DECIMAL_H_
#define _S21_DECIMAL_H_

#define s21_OK 0
#define s21_CALCULATION_ERROR 1

#define s21_LARGE_ERROR 1
#define s21_SMALL_ERROR 2
#define s21_NULL_DIV_ERROR 3

#define s21_FALSE 0
#define s21_TRUE 1

#define CONVERTATION_OK 0
#define CONVERTATION_ERROR 1

#define s21_MAX_DEC 2e96 - 1

#include <math.h>
#include <stdlib.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  int sign;
  int scale;
  unsigned int bits[6];
} s21_big_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // +
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // -
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // \ *
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // /

int s21_decimal_integer_mul(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);
int s21_decimal_float_mul(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result);
int s21_decimal_integer_div(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);
int s21_decimal_float_div(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result);

void s21_big_add(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result);
void s21_big_sub(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_get_bit(int number, int position);
void s21_set_bit(unsigned *number, int position, int value);
int s21_decimal_get_bit(s21_decimal decimal, int position);
void s21_decimal_set_bit(s21_decimal *decimal, int position, int value);
void s21_decimal_left_shift(s21_decimal *decimal, int shifts);
void s21_decimal_right_shift(s21_decimal *decimal, int shifts);

int s21_decimal_get_pow(s21_decimal value);
void s21_decimal_set_pow(s21_decimal *decimal, int pow);

int s21_decimal_first_mean_bit(s21_decimal decimal);
void s21_decimal_null(s21_decimal *decimal);
int s21_decimal_is_null(s21_decimal decimal);

void s21_decimal_binary_and(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);
void s21_decimal_binary_xor(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);

int s21_decimal_integer_mul(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);
int s21_decimal_float_mul(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result);
void s21_decimal_copy_value_of_decimal(s21_decimal src, s21_decimal *dest);

s21_big_decimal big_decimal(s21_decimal value);
void big_decimal_set_zero(s21_big_decimal *big_value);
void same_scale(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2);
void scale_up(s21_big_decimal *big_value, int dif);

int decimal_from_big(s21_big_decimal big_value, s21_decimal *value);
void bank_rounding(s21_big_decimal *big_value);
int divide_by_ten(s21_big_decimal *big_value, int count);
int big_decimal_is_null(s21_big_decimal big_value);
void s21_set_sign(s21_decimal *value, int sign);

s21_decimal s21_decimal_nulling_at_index(s21_decimal decimal, int index,
                                         int end_index);
s21_decimal s21_decimal_get_decimal_from_indexes(s21_decimal decimal, int index,
                                                 int end_index);
void s21_decimal_set_decimal_from_indexes(s21_decimal value,
                                          s21_decimal *target, int index,
                                          int end_index);
void s21_decimal_copy_value_of_decimal(s21_decimal src, s21_decimal *dest);
void s21_decimal_binary_inversion_by_index(s21_decimal *decimal, int index,
                                           int end_index);
void s21_decimal_indexes_sub(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result);

void s21_decimal_indexes_add(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result);
unsigned int s21_div_by_10(s21_decimal *number);

static const s21_decimal s21_decimal_ten_pows[29] = {
    [0] = {{0x1, 0x0, 0x0, 0x0}},
    [1] = {{0xA, 0x0, 0x0, 0x0}},
    [2] = {{0x64, 0x0, 0x0, 0x0}},
    [3] = {{0x3E8, 0x0, 0x0, 0x0}},
    [4] = {{0x2710, 0x0, 0x0, 0x0}},
    [5] = {{0x186A0, 0x0, 0x0, 0x0}},
    [6] = {{0xF4240, 0x0, 0x0, 0x0}},
    [7] = {{0x989680, 0x0, 0x0, 0x0}},
    [8] = {{0x5F5E100, 0x0, 0x0, 0x0}},
    [9] = {{0x3B9ACA00, 0x0, 0x0, 0x0}},
    [10] = {{0x540BE400, 0x2, 0x0, 0x0}},
    [11] = {{0x4876E800, 0x17, 0x0, 0x0}},
    [12] = {{0xD4A51000, 0xE8, 0x0, 0x0}},
    [13] = {{0x4E72A000, 0x918, 0x0, 0x0}},
    [14] = {{0x107A4000, 0x5AF3, 0x0, 0x0}},
    [15] = {{0xA4C68000, 0x38D7E, 0x0, 0x0}},
    [16] = {{0x6FC10000, 0x2386F2, 0x0, 0x0}},
    [17] = {{0x5D8A0000, 0x1634578, 0x0, 0x0}},
    [18] = {{0xA7640000, 0xDE0B6B3, 0x0, 0x0}},
    [19] = {{0x89E80000, 0x8AC72304, 0x0, 0x0}},
    [20] = {{0x63100000, 0x6BC75E2D, 0x5, 0x0}},
    [21] = {{0xDEA00000, 0x35C9ADC5, 0x36, 0x0}},
    [22] = {{0xB2400000, 0x19E0C9BA, 0x21E, 0x0}},
    [23] = {{0xF6800000, 0x2C7E14A, 0x152D, 0x0}},
    [24] = {{0xA1000000, 0x1BCECCED, 0xD3C2, 0x0}},
    [25] = {{0x4A000000, 0x16140148, 0x84595, 0x0}},
    [26] = {{0xE4000000, 0xDCC80CD2, 0x52B7D2, 0x0}},
    [27] = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x0}},
    [28] = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}},
};

#endif