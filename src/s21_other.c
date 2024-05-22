#include "s21_additional.h"
#include "s21_decimal.h"

int s21_truncate(s21_decimal number, s21_decimal *result) {
  int sign = get_sign(number);
  int exp = get_exp(number);

  init_dec(sign, 0, 0, 0, 0, result);

  int flag = 0;

  if (exp > 28)
    flag = 1;
  else {
    if (exp == 0) *result = number;
    s21_decimal div_value = {0};
    init_dec(0, 0, 0, 0, 10, &div_value);

    while (exp != 0) {
      simple_div(number, div_value, result);
      number = *result;
      exp--;
    }
    set_exp(result, 0);
    set_sign(result, sign);
  }
  return flag;
}

int s21_negate(s21_decimal number, s21_decimal *result) {
  int flag = 1;
  if (get_sign(number) == 0) {
    set_sign(&number, 1);
    *result = number;
    flag = 0;
  } else {
    set_sign(&number, 0);
    *result = number;
    flag = 0;
  }
  return flag;
}

int s21_floor(s21_decimal number, s21_decimal *result) {
  int flag = 1;

  int exp = get_exp(number);
  if (exp < 28) {
    int sign = get_sign(number);
    s21_decimal div_value = {0};
    div_value.bits[0] = pow(10, exp);
    int mod = simple_fmod(number, div_value);
    s21_truncate(number, result);
    if (sign && mod > 0) result->bits[0] += 1;
    flag = 0;
  }
  return flag;
}

int s21_round(s21_decimal number, s21_decimal *result) {
  int flag = 1;

  int mod = 0;
  int exp = get_exp(number);
  int sign = get_sign(number);
  init_dec(sign, 0, 0, 0, 0, result);
  if (exp < 28) {
    if (exp > 0) {
      s21_decimal dec = {{10, 0, 0, 0}};
      for (int i = 0; i < exp; i++) {
        mod = simple_fmod(number, dec);
        simple_div(number, dec, &number);
      }
      *result = number;

      if (mod >= 5) result->bits[0] += 1;

    } else {
      *result = number;
    }
    set_exp(result, 0);
    set_sign(result, sign);
    flag = 0;
  }

  return flag;
}