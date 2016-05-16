#include <stdint.h>

/*
 * This algorithm is taken from
 * "Math Toolkit for Real-Time Programming" by Jack Crenshaw.
 */

static int16_t _sin(int16_t y)
{
  const int16_t s1 = 0x6488;
  const int16_t s3 = 0x2958;
  const int16_t s5 = 0x51a;
  const int16_t s7 = 0x4d;

  int32_t z, prod, sum;
  z = ((int32_t)y * y) >> 12;
  prod = (z * s7) >> 16;
  sum = s5 - prod;
  prod = (z * sum) >> 16;
  sum = s3 - prod;
  prod = (z * sum) >> 16;
  sum = s1 - prod;

  return (int16_t)((y * sum) >> 13);
}

static int16_t _cos(int16_t y)
{
  const int16_t c0 = 0x7fff;
  const int16_t c2 = 0x4ef5;
  const int16_t c4 = 0x103e;
  const int16_t c6 = 0x156;
  int32_t z, prod, sum;
  z = ((int32_t)y * y) >> 12;
  prod = (z * c6) >> 16;
  sum = c4 - prod;
  prod = (z * sum) >> 16;
  sum = c2 - prod;

  prod = (z * sum) >> 15;

  return (int16_t)(c0 - prod);
}

int isin(int16_t x)
{
  int16_t n = 3 & (((x + 0x2000)) >> 14);
  x -= n << 14;
  switch (n) {
  case 0:
    return _sin(x);
  case 1:
    return _cos(x);
  case 2:
    return -_sin(x);
  case 3:
    return -_cos(x);
  }
}

int icos(int16_t x)
{
  return isin(x + 0x4000);
}
