#include "../src/xor.c"
#include "../src/hex.c"
#include "test.h"

#include <string.h>
#include <stdio.h>

int main(void)
{
  char *textsrc1 = "1c0111001f010100061a024b53535009181c";
  char *textsrc2 = "686974207468652062756c6c277320657965";
  char *textdst1 = "746865206b696420646f6e277420706c6179";

  char src1[18];
  char src2[18];
  char dst1[19];
  char dst2[19];

  hex_decode(textsrc1, src1, 18);
  hex_decode(textsrc2, src2, 18);
  hex_decode(textdst1, dst1, 18);

  xor(src1, src2, dst2, 18);

  dst1[18] = 0;
  dst2[18] = 0;

  assert_string("XOR string", dst1, dst2);

  return 0;
}
