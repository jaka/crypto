static const char base64_encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned int base64_encoded_length(const unsigned int input_len)
{
  if (input_len == 0)
    return 0;
  return 4 * ((input_len - 1) / 3) + 4;
}

int base64_encode(char *output, char *input, const unsigned int input_len)
{
  unsigned int i = 0;
  char *p = input;
  char *s = output;
  while (input_len - i >= 3) {
    *s++ = base64_encoding_table[*p >> 2];
    *(s++) = base64_encoding_table[((*p & 0x3) << 4) | (*(p + 1) >> 4)];
    p++;
    *(s++) = base64_encoding_table[((*p & 0xf) << 2) | (*(p + 1) >> 6)];
    p++;
    *(s++) = base64_encoding_table[*(p++) & 0x3f];
    i += 3;
  }
  if (input_len - i != 0) {
    *s++ = base64_encoding_table[*p >> 2];
    if (input_len - i == 2) {
      *(s++) = base64_encoding_table[((*p & 0x3) << 4) | (*(p + 1) >> 4)];
      p++;
      *(s++) = base64_encoding_table[(*p & 0xf) << 2];
    }
    else {
      *(s++) = base64_encoding_table[(*p & 0x3) << 4];
      *(s++) = '=';
    }
    (*s++) = '=';
  }
  return 0;
}
