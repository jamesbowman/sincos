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
\ This implementation is for a Forth with 32- and 64-bit cells.
\

: s16
    $ffff and
    dup $8000 and if
        $10000 -
    then ;

: h* ( a b -- ab/65536 )    * 16 rshift s16 ;
: r- ( a b -- b-a )         swap - ;
: p* ( a b -- ab/32768 )    * 15 rshift s16 ;

$6487 constant s1
$2953 constant s3
$04f8 constant s5

: _sin ( y -- sin )
    2* 2* s16 dup dup h*    ( y z )
    dup s5 h* s3 r-         ( y z sum )
    h* s1 r-                ( y sum )
    p*        
;

$7fff constant c0
$4ee9 constant c2
$0fbd constant c4

: _cos ( y -- cos )
    2* 2* dup h*            ( z )
    dup c4 h* c2 r-         ( z sum )
    p*                      ( prod )
    c0 r-
;

: isin
    dup $2000 + $c000 and   ( x n )
    tuck -                  ( n x )
    over $4000 and if
        _cos
    else
        _sin
    then
    swap $8000 and if negate then
;

: icos  $4000 + isin ;

\ : x
\     $10000 0 do
\         cr i . i isin .
\     $200 +loop
\ ;
\ cr x cr bye
