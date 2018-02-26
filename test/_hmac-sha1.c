#include "../src/sha1.c"
#include "hmac.h"
#include "test.h"
#include <string.h>

static int test_X(const char *input, const unsigned char *key, unsigned char *hash)
{
  unsigned char output[SHA1_LENGTH];

  hmac_sha1((unsigned char *)input, strlen(input), key, output);

  if (assert_int(input, memcmp(hash, output, SHA1_LENGTH), 0) < 0) {
    return -1;
  }
  return 0;
}

int main(void)
{
  char input3[51];
  unsigned char key[HMAC_KEY_LENGTH];
  unsigned char hash1[SHA1_LENGTH] = { 0xb6, 0x17, 0x31, 0x86, 0x55, 0x05, 0x72, 0x64, 0xe2, 0x8b, 0xc0, 0xb6, 0xfb, 0x37, 0x8c, 0x8e, 0xf1, 0x46, 0xbe, 0x00 };
  unsigned char hash2[SHA1_LENGTH] = { 0xef, 0xfc, 0xdf, 0x6a, 0xe5, 0xeb, 0x2f, 0xa2, 0xd2, 0x74, 0x16, 0xd5, 0xf1, 0x84, 0xdf, 0x9c, 0x25, 0x9a, 0x7c, 0x79 };
  unsigned char hash3[SHA1_LENGTH] = { 0x12, 0x5d, 0x73, 0x42, 0xb9, 0xac, 0x11, 0xcd, 0x91, 0xa3, 0x9a, 0xf4, 0x8a, 0xa1, 0x7b, 0x4f, 0x63, 0xf1, 0x75, 0xd3 };
 
  test_title("Testing HMAC-SHA1");

  memset(key, 0x0b, 20);
  memset(key + 20, 0, HMAC_KEY_LENGTH - 20);
  if (test_X("Hi There", key, hash1) < 0) {
    return 1;
  }

  memcpy(key, "Jefe", 4);
  memset(key + 4, 0, HMAC_KEY_LENGTH - 4);
  if (test_X("what do ya want for nothing?", key, hash2) < 0) {
    return 1;
  }

  memset(key, 0xaa, 20);
  memset(key + 20, 0, HMAC_KEY_LENGTH - 20);
  memset(input3, 0xdd, 50);
  *(input3 + 50) = 0;
  if (test_X(input3, key, hash3) < 0) {
    return 1;
  }

  return 0;
}

