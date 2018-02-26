#include "../src/base64.c"
#include "test.h"
#include <string.h>

int test_X(char *input, char *output)
{
  char encoded[80];
  char decoded[80];
  unsigned int input_len, output_len;
  unsigned int encoded_len, decoded_len;

  input_len = strlen(input);
  output_len = strlen(output);

  encoded_len = base64_encoded_length(input_len);
  if (assert_uint("base64_encoded_length", encoded_len, output_len) < 0) {
    return 1;
  }

  base64_encode(input, encoded, input_len);
  *(encoded + encoded_len) = 0;
  if (assert_string("base64_encode", encoded, output) < 0) {
    return 1;
  }

  decoded_len = base64_decode(encoded, decoded, encoded_len);
  *(decoded + decoded_len) = 0;
  if (assert_string("base64_decode", decoded, input) < 0) {
    return 1;
  }
  return 0;
}

int main(void)
{
  char *input;

  test_title("Testing BASE64");

  if (test_X("M", "TQ==") < 0) {
    return -1;
  }

  if (test_X("Ma", "TWE=") < 0) {
    return -1;
  }

  if (test_X("Man", "TWFu") < 0) {
    return -1;
  }

  return 0;
}
