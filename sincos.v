`timescale 1ns/1ps
`default_nettype none

// isin and icos are integer sine and cosine functions.
// The input angle is in Furmans. (A Furman is 1/65536 of a
// circle. One degree is ~182 Furmans. One radian is ~10430
// Furmans.)
// The result is a 16-bit signed integer, scaled so that
// -32767 represents -1.0 and +32767 represents +1.0.

// half multiply-add: p = ((a * b) >> 16) + c
module hmadd(
  input signed [15:0] a,
  input signed [15:0] b,
  input signed [15:0] c,
  output signed [15:0] p);
  wire [31:0] xx = a * b;
  assign p = xx[31:16] + c;
endmodule

module isin(
  input signed [15:0] x,
  output signed [15:0] s);

  wire signed [15:0] z, y, sums, sumc, sum1, cc;

  wire [2:0] n = x[15:13] + 3'd1;
  assign y = {x[13:0], 2'b00};

  hmadd _h0(.a(y), .b(y), .c(0), .p(z));
  hmadd _hc(.a(z), .b(16'sh0fbd), .c(-16'sh4ee9), .p(sumc));
  hmadd _hs(.a(z), .b(16'sh04f8), .c(-16'sh2953), .p(sums));
  hmadd _h2(.a(z), .b(sums), .c(16'sh6487), .p(sum1));

  reg signed [15:0] t0, t1, sa;
  always @*
    if (n[1]) begin                // cosine
      t0 = z;
      t1 = sumc;
      sa = cc + 16'sh7fff;
    end else begin                  // sine
      t0 = y;
      t1 = sum1;
      sa = cc;
    end
  wire [31:0] cc32 = t0 * t1;
  assign cc = cc32[30:15];

  assign s = n[2] ? -sa : sa;
endmodule

module icos(
  input signed [15:0] x,
  output signed [15:0] s);

  isin _isin(.x(x + 16'h4000), .s(s));

endmodule

// START OF STANDALONE TEST

module top();
  integer i;
  reg signed [15:0] x;
  wire signed [15:0] ss, sc;

  isin _isin(.x(x), .s(ss));
  icos _icos(.x(x), .s(sc));

  initial begin
    i = 0;
    for (i = 0; i < 65536; i = i + 1) begin
      x = i;
      #1;
      $display ("%d %d", ss, sc);
    end
  end
endmodule
