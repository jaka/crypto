#include "../src/sha1.c"
#include "test.h"

int test_X(char *input, unsigned char *hash)
{
  unsigned char output[20];

  sha1(input, strlen(input), output);
  if (assert_int((unsigned char *)input, memcmp(hash, output, 20), 0) < 0) {
    return -1;
  }
  return 0;
}

int main(void)
{
  char *input1 = "abc";
  unsigned char hash1[20] = { 0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a, 0xba, 0x3e, 0x25, 0x71, 0x78, 0x50, 0xc2, 0x6c, 0x9c, 0xd0, 0xd8, 0x9d };

  char *input4 = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
  unsigned char hash4[20] = { 0xa4, 0x9b, 0x24, 0x46, 0xa0, 0x2c, 0x64, 0x5b, 0xf4, 0x19, 0xf9, 0x95, 0xb6, 0x70, 0x91, 0x25, 0x3a, 0x04, 0xa2, 0x59 };

  test_title("Testing SHA1");

  if (test_X(input1, hash1) < 0) {
    return -1;
  }

  if (test_X(input4, hash4) < 0) {
    return -1;
  }

  return 0;
}
