#include "../src/hex.c"
#include "test.h"

#include <string.h>

int main(void)
{
  int rv;
  unsigned char d;
  unsigned int len;
  char *input;
  unsigned char output[19];

  test_title("Testing HEX");

  rv = _hex2c("00", &d);
  assert_int("Return value", rv, 0);
  assert_u8("Decoded value", d, 0);

  rv = _hex2c("fF", &d);
  assert_int("Return value", rv, 0);
  assert_u8("Decoded value", d, 255);

  input = "746865206b696420646f6e277420706c6179";

  len = hex_decoded_length(strlen(input));
  assert_int("Decoded length", (signed int)len, 18);

  hex_decode(input, output, 18);
  output[18] = 0;
  assert_string("Decoded string", output, "the kid don't play");

  return 0;
}