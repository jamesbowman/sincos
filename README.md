# sincos

Efficient implementations of the transcendental functions

This algorithm is taken from
"Math Toolkit for Real-Time Programming" by Jack Crenshaw.

These versions use the adjusted Chebyshev coefficients
on p.120.

isin() and icos() are integer sine and cosine functions. The input
angle is in Furmans. (A Furman is 1/65536 of a circle. One degree
is ~182 Furmans. One radian is ~10430 Furmans.)
The result is a 16-bit signed integer, scaled so that -32767 represents
-1.0 and +32767 represents +1.0.

Each implementation is followed by a stand alone test case that outputs
sin(x) for all x. These should all match the reference in `golden`.
Script `testall` builds and confirms all implementations.

Currently there are implementaions for:

 * plain C (`sincos.c`)
 * ANS Forth with 32-bit or 64-bit cells (`forth32.fs`)
 * Verilog (`sincos.v`)
