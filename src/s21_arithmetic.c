#include "s21_additional.h"
#include "s21_decimal.h"

int s21_add(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  long_dec number_longdec_1, number_longdec_2, number_longdec_3;
  converting_decimal_to_longdec(number_1, &number_longdec_1);
  converting_decimal_to_longdec(number_2, &number_longdec_2);
  normalize_long(&number_longdec_1, &number_longdec_2);
  add(number_longdec_1, number_longdec_2, &number_longdec_3);
  longdec_to_dec(number_longdec_3, result);
  int result_1 = get_bit(*result, 96) * (get_sign(*result) + 1);
  return result_1;
}

int s21_sub(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  long_dec number_longdec_1, number_longdec_2, number_longdec_3;
  converting_decimal_to_longdec(number_1, &number_longdec_1);
  converting_decimal_to_longdec(number_2, &number_longdec_2);
  normalize_long(&number_longdec_1, &number_longdec_2);
  sub(number_longdec_1, number_longdec_2, &number_longdec_3);
  longdec_to_dec(number_longdec_3, result);
  int result_1 = get_bit(*result, 96) * (get_sign(*result) + 1);
  return result_1;
}

int s21_mul(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  long_dec number_longdec_1, number_longdec_2, number_longdec_3;
  converting_decimal_to_longdec(number_1, &number_longdec_1);
  converting_decimal_to_longdec(number_2, &number_longdec_2);
  mul(number_longdec_1, number_longdec_2, &number_longdec_3);
  longdec_to_dec(number_longdec_3, result);
  int result_1 = get_bit(*result, 96) * (get_sign(*result) + 1);
  return result_1;
}

int s21_mod(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  long_dec number_longdec_1, number_longdec_2, number_longdec_3;
  converting_decimal_to_longdec(number_1, &number_longdec_1);
  converting_decimal_to_longdec(number_2, &number_longdec_2);
  normalize_long(&number_longdec_1, &number_longdec_2);
  mod(number_longdec_1, number_longdec_2, &number_longdec_3);
  longdec_to_dec(number_longdec_3, result);
  if (get_bit(*result, 96))
    init_dec(get_sign(*result), get_exp(*result), 0, 0, 0, result);

  int result_1 = get_bit(*result, 96) * (get_sign(*result) + 1);
  return (mantissa_is_zero(number_longdec_2) ? 3 : result_1);
}

int s21_div(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  long_dec number_longdec_1, number_longdec_2, number_longdec_3;
  converting_decimal_to_longdec(number_1, &number_longdec_1);
  converting_decimal_to_longdec(number_2, &number_longdec_2);
  div_dec(number_longdec_1, number_longdec_2, &number_longdec_3);
  longdec_to_dec(number_longdec_3, result);
  int result_1 = get_bit(*result, 96) * (get_sign(*result) + 1);
  return (mantissa_is_zero(number_longdec_2) ? 3 : result_1);
}
