#include "../src/base64.c"
#include "test.h"

int main(void)
{
  char *input;
  char output[80];
  unsigned int input_len;
  unsigned int output_len;

  printf(ANSI_COLOR_YELLOW "Testing BASE64:\n" ANSI_COLOR_RESET);

  printf("Test 1\n");
  input = "Man";
  input_len = 0;
  output_len = base64_encoded_length(input_len);
  if (output_len != 4) {
    printf("base64_encoded_length FAIL\nExpected %d, got %d.\n", 4, output_len);
    return 1;
  }
  else {
    printf("base64_encoded_length OK\n");
  }
  base64_encode(output, input, input_len);
  *(output + 4) = 0;
  printf("%s\n", output);

  return 0;
}
