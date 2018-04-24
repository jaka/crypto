#include "common.h"

EXPORT int hex_decoded_length(const unsigned int input_len)
{
  if (input_len & 0x1) {
    return -1;
  }
  return input_len / 2;
}

static int _hex2sc(const char c, unsigned char *d)
{
  if ('0' <= c && c <= '9')
    *d = c - '0';
  else if ('A' <= c && c <= 'F')
    *d = 10 + c - 'A';
  else if ('a' <= c && c <= 'f')
    *d = 10 + c - 'a';
  else
    return 1;
  return 0;
}

static int _hex2c(const char *s, unsigned char *d)
{
  unsigned char e;

  *d = 0;
  if (_hex2sc(*s, d)) {
    return 1;
  }
  s++;
  *d *= 16;
  if (_hex2sc(*s, &e)) {
    return 1;
  }
  *d += e;
  return 0;
}

EXPORT int hex_decode(const char *input, unsigned char *output, unsigned int input_len)
{
  unsigned int i;
  const char *s;
  unsigned char *d;

  for (i = input_len, s = input, d = output; *input && i; i--) {
      if (_hex2c(s, d)) {
        return 1;
      }
      else {
        s += 2;
        d++;
      }
  }
  return 0;
}