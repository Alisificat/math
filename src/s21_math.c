#include "s21_math.h"
int s21_abs(int x) {
  // вычисляет абсолютное значение целого числа
  if (x < 0) {
    x = (-1) * x;
  }
  return x;
}

long double s21_acos(double x) {
  long double buf = s21_asin(x);
  buf = (s21_PI / 2) - buf;
  return buf;
}

long double s21_asin(double x) {
  int k = 450;
  long double buf = 0;
  int sign = x > 0 ? 1 : -1;
  long double local_x =
      (x * sign) < s21_SIN_QUAD ? (x * sign) : (s21_sqrt(1 - x * x));
  for (int i = 0; i < k; i++) {
    long double buf0 = 0;
    buf0 = s21_factorial(2 * i) / s21_integer_power(4, i);
    buf = buf + buf0 * s21_integer_power(local_x, 2 * i + 1) /
                    (s21_integer_power(s21_factorial(i), 2) * (2 * i + 1));
  }
  buf = (x * sign) < s21_SIN_QUAD ? buf : (s21_PI / 2) - buf;
  return buf * sign;
}

long double s21_atan(double x) {
  long double buf = x / s21_sqrt(1 + x * x);
  buf = s21_asin(buf);
  return buf;
}

long double s21_ceil(double x) {
  // возвращает ближайшее целое число, не меньшее заданного значения
  long long int x1;
  return (x < 0)                            ? (x1 = (long long int)x)
         : (x == 0)                         ? x
         : (x > 0 && (long long int)x == x) ? x1 = x
                                            : (x1 = (long long int)x + 1);
}

long double s21_cos(double x) {
  long double buf = s21_sin(x + s21_PI / 2);
  return buf;
}

long double s21_exp(double x) {
  long double buf = 0;
  if (x != 0) {
    long double x_local;
    x_local = x > 0 ? x : (-1 * x);
    for (int i = 0; i < 650; i++) {
      buf = buf + s21_integer_power(x_local, i) / s21_factorial(i);
    }
    buf = x > 0 ? buf : (1 / buf);
  } else {
    buf = 1;
  }
  return buf;
}

long double s21_fabs(double x) {
  //  вычисляет абсолютное значение числа с плавающей точкой
  if (x < 0) {
    x = (-1) * x;
  }
  return x;
}

long double s21_floor(double x) {
  //  возвращает ближайшее целое число, не превышающее заданное значение
  long long int x1, x2;
  long double r;
  x2 = x;
  x1 = s21_fabs(x);
  r = s21_fabs(x) - x1;
  return (x == (long long int)x2) ? x
         : (x < 0 && r > 0)       ? (long long int)x2 - 1
                                  : (long long int)x1;
}

long double s21_fmod(double x, double y) {
  //  остаток операции деления с плавающей точкой
  long double x1, y1, z, z1;
  x1 = s21_fabs(x);
  y1 = s21_fabs(y);
  if (y != 0) {
    long double fd = x1 / y1;
    long double g = s21_floor(fd);
    z = x1 - g * y1;
    z1 = (-1) * z;
  } else {
    z = s21_NAN;
    z1 = s21_NAN;
  }
  return ((x < 0 && y < 0) || (x < 0 && y > 0)) ? z1 : z;
}

long double s21_log(double x) {
  long double buf = 0;
  long double x_local = x;

  if (x > 0) {
    int counter = 0;
    while (x_local > 10) {
      x_local = x_local / 10;
      counter++;
    }
    while (x_local < 1) {
      x_local = x_local * 10;
      counter--;
    }
    long double z = (1 - x_local) / (1 + x_local);
    int k = 850;
    for (int i = 0; i < k; i++) {
      buf = buf + s21_integer_power(z, 2 * i + 1) / (2 * i + 1);
    }
    buf = -2 * buf;
    buf = buf + (counter) * (long double)s21_lN_10;
  } else if (x == 0) {
    buf = -s21_INF;
  } else {
    buf = -s21_NAN;
  }
  return buf;
}

long double s21_pow(double base, double ex) {
  double z = 1;
  if (base == 0 && ex == 0) {
  } else {
    z = s21_exp(ex * s21_log(base));
  }
  return z;
}

long double s21_sin(double x) {
  int k = 950;
  long double buf = 0;
  long double x_local = x - (s21_floor(x / s21_PI) * s21_PI);
  for (int i = 0; i < k; i++) {
    buf = buf + s21_integer_power(-1, i) *
                    s21_integer_power(x_local, 2 * i + 1) /
                    s21_factorial(2 * i + 1);
  }
  buf = ((int)s21_floor(x / s21_PI) % 2 == 0) ? buf : (-1 * buf);
  return buf;
}

long double s21_sqrt(double x) { return s21_pow(x, 0.5); }

long double s21_tan(double x) {
  long double buf = s21_sin(x) / s21_cos(x);
  return buf;
}

long double s21_factorial(int factorial) {
  long double buf = factorial > 0 ? factorial : 1;
  for (int i = factorial - 1; i > 0; i--) {
    buf = i * buf;
  }
  return buf;
}

long double s21_integer_power(long double x, int power) {
  long double buf = 1;
  for (int i = power; i > 0; i--) {
    buf = buf * x;
  }
  return buf;
}
