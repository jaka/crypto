#include "../src/base64.c"
#include "test.h"

int main(void)
{
  char *input;
  char output[80];
  unsigned int input_len;
  unsigned int output_len;

  test_title("Testing BASE64");

  input = "Man";
  input_len = 3;
  output_len = base64_encoded_length(input_len);
  if (assert_uint("base64_encoded_length", output_len, 4) < 0) {
    return 1;
  }
  base64_encode(output, input, input_len);
  *(output + output_len) = 0;
  if (assert_string("base64_encode", output, "TWFu") < 0) {
    return 1;
  }

  return 0;
}
