#include <stdint.h>

/*
 * This algorithm is taken from
 * "Math Toolkit for Real-Time Programming" by Jack Crenshaw.
 *
 * These versions use the adjusted Chebyshev coefficients
 * on p.120.
 */

static int16_t _sin(int16_t y)
{
  const int16_t s1 =  0x6487;
  const int16_t s3 = -0x2953;
  const int16_t s5 =  0x04f8;

  int32_t z, prod, sum;
  z = ((int32_t)y * y) >> 12;
  prod = (z * s5) >> 16;
  sum = s3 + prod;
  prod = (z * sum) >> 16;
  sum = s1 + prod;

  return (int16_t)((y * sum) >> 13);
}

static int16_t _cos(int16_t y)
{
  const int16_t c0 =  0x7fff;
  const int16_t c2 = -0x4ee9;
  const int16_t c4 =  0x0fbd;

  int32_t z, prod, sum;
  z = ((int32_t)y * y) >> 12;
  prod = (z * c4) >> 16;
  sum = c2 + prod;

  prod = (z * sum) >> 15;

  return (int16_t)(c0 + prod);
}

/*
 isin() and icos() are integer sine and cosine functions. The input
 angle is in Furmans. (A Furman is 1/65536 of a circle. One degree
 is ~182 Furmans. One radian is ~10430 Furmans.)
 The result is a 16-bit signed integer, scaled so that -32767 represents
 -1.0 and +32767 represents +1.0.
*/

int isin(int16_t x)
{
  int16_t n = 3 & (((x + 0x2000)) >> 14);
  x -= n << 14;
  int16_t r = (n & 1) ? _cos(x) : _sin(x);
  return (n & 2) ? -r : r;
}

int icos(int16_t x)
{
  return isin(x + 0x4000);
}

// START OF STANDALONE TEST

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i;
  for (i = 0; i < 0x10000; i++)
    printf("%d\n", isin(i));
  exit(0);
}
