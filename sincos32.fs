\ This algorithm is taken from
\ "Math Toolkit for Real-Time Programming" by Jack Crenshaw.
\
\ These versions use the adjusted Chebyshev coefficients
\ on p.120.
\
\ isin and icos are integer sine and cosine functions.
\ The input angle is in Furmans. (A Furman is 1/65536 of a
\ circle. One degree is ~182 Furmans. One radian is ~10430
\ Furmans.)
\ The result is a 16-bit signed integer, scaled so that
\ -32767 represents -1.0 and +32767 represents +1.0.
\
\ This implementation is for a Forth with a cell size 32
\ bits or more.
\

hex
: s16 ( u - s )
    0ffff and
    dup 8000 and if
        10000 -
    then ;

: h* ( a b -- ab/65536 )    * 10 rshift s16 ;
: p* ( a b -- ab/32768 )    * 0f rshift s16 ;

 6487 constant s1
-2953 constant s3
 04f8 constant s5

 7fff constant c0
-4ee9 constant c2
 0fbd constant c4

: _sin ( y -- sin )
    2* 2* s16 dup dup h*    ( y z )
    dup s5 h* s3 +          ( y z sum )
    h* s1 +                 ( y sum )
    p*        
;

: _cos ( y -- cos )
    2* 2* dup h*            ( z )
    dup c4 h* c2 +          ( z sum )
    p*                      ( prod )
    c0 +
;

: isin
    dup 2000 + c000 and     ( x n )
    tuck -                  ( n x )
    over 4000 and if
        _cos
    else
        _sin
    then
    swap 8000 and if negate then
;

: icos  4000 + isin ;

decimal

\ START OF STANDALONE TEST

: x
    $10000 0 do
        i isin . cr
    loop
;
x bye
