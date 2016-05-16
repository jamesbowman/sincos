
import math

def _sin(y):
    s1 = math.pi
    s3 = math.pi**3 / math.factorial(3)
    s5 = math.pi**5 / math.factorial(5)
    s7 = math.pi**7 / math.factorial(7)
  
    z = y * y
    prod = (z * s7)
    sum = s5 - prod
    prod = (z * sum)
    sum = s3 - prod
    prod = (z * sum)
    sum = s1 - prod
  
    return y * sum

if __name__ == '__main__':
    errors = []
    for l in open("results.txt"):
        (angle, sine) = [int(f) for f in l.split()]
        th = angle * 2 * math.pi / 0x10000
        expected = 32767.0 * math.sin(th)
        # print angle, sine, expected
        errors.append((abs(sine - expected), angle, sine, expected))
    print len(errors), 'values tested'
    print 'max error %f for angle=%d: actual=%d expected=%f' % max(errors)
    print 'rms error', math.sqrt(sum([e[0]**2 for e in errors]) / len(errors))
