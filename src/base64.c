#include "common.h"

#include <stdlib.h>

static const char base64_encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char *base64_decoding_table = NULL;

static void _build_decoding_table(void)
{
  char i;

  base64_decoding_table = malloc(256 * sizeof(char));
  for (i = 0; i < 64; i++) {
    *(base64_decoding_table + *(base64_encoding_table + i)) = i;
  }
}

EXPORT void base64_free_decoding_table(void)
{
  if (base64_decoding_table) {
    free(base64_decoding_table);
    base64_decoding_table = NULL;
  }
}

EXPORT unsigned int base64_encoded_length(const unsigned int input_len)
{
  if (input_len == 0) {
    return 0;
  }
  return 4 * ((input_len - 1) / 3) + 4;
}

EXPORT int base64_encode(const char *input, char *output, const unsigned int input_len)
{
  char *p = (char *)input;
  char *s = output;
  unsigned int i = 0;

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

EXPORT unsigned int base64_decoded_length(const unsigned int input_len)
{
  if (input_len == 0) {
    return 0;
  }
  return 3 * ((input_len + 3) / 4);
}

EXPORT unsigned int base64_decode(const char *input, char *output, unsigned int input_len)
{
  char *s = (char *)input;
  char *d = output;
  int len;
  char value;

  if (!base64_decoding_table) {
    _build_decoding_table();
  }

  while (input_len && *(input + input_len - 1) == '=') {
    input_len--;
  }

  while (input_len) {
    value = *(base64_decoding_table + *s);
    s++;
    input_len--;
    *d = (value << 2) & 0xff;

    value = *(base64_decoding_table + *s);
    s++;
    *d |= value >> 4;
    input_len--;
    if (!input_len) {
      break;
    }
    d++;
    *d = (value << 4) & 0xff;

    value = *(base64_decoding_table + *s);
    s++;
    input_len--;
    *d |= value >> 2;
    if (!input_len) {
      break;
    }
    d++;
    *d = (value << 6) & 0xff;

    value = *(base64_decoding_table + *s);
    s++;
    input_len--;
    *d |= value;
  }
  len = d - output + 1;

  return len;
}

