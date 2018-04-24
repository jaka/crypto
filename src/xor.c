#include "common.h"

EXPORT void xor(unsigned char *sbuf1, unsigned char *sbuf2, unsigned char *dbuf, unsigned int buflen)
{
  unsigned int i;
  unsigned char *d, *s1, *s2;

  for (i = buflen, s1 = sbuf1, s2 = sbuf2, d = dbuf; i; i--) {
    *d = *s1 ^ *s2;
    d++;
    s1++;
    s2++; 
  }

}