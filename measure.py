import sys
import math

actual = [int(l.split()[0]) for l in open("golden")]
expected = [32767 * math.sin(2 * math.pi * i / 65536) for i in range(2**16)]
assert len(expected) == len(actual)
errors = [abs(a - e) for (a, e) in zip(actual, expected)]
rms = math.sqrt(sum([e*e for e in errors]) / 65536.)
sys.stdout.write("Worst error %.3f  rms %.3f\n" %  (max(errors), rms))
