import sys
import numpy as np

def hmul(a, b, sr = 16):
    return ((a.astype(np.int32) * b) >> sr).astype(np.int16)

def _sin(y):
  s1 =  0x6487
  s3 = -0x2953
  s5 =  0x04f8

  z = hmul(y, y, 12)
  prod = hmul(z, s5)
  sum = s3 + prod
  prod = hmul(z, sum)
  sum = s1 + prod

  return hmul(y, sum, 13)

def _cos(y):
  c0 =  0x7fff;
  c2 = -0x4ee9;
  c4 =  0x0fbd;

  z = hmul(y, y, 12)
  prod = hmul(z, c4)
  sum = c2 + prod;
  prod = hmul(z, sum, 15)

  return c0 + prod

def isin(x):
  n = (x + 0x2000) & 0xc000
  x1 = (x - n).astype(np.int16)
  r = np.where(n & 0x4000, _cos(x1), _sin(x1))
  return np.where(n & 0x8000, -r, r)

def icos(x):
    return isin(x + 0x4000)

a = np.arange(0, 65536, 1)
sys.stdout.write("".join(["%d %d\n" % sc for sc in zip(isin(a), icos(a))]))
