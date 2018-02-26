#include "sha1.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define SHA1_K00 0x5a827999
#define SHA1_K20 0x6ed9eba1
#define SHA1_K40 0x8f1bbcdc
#define SHA1_K60 0xca62c1d6

#define SHA1_A 0x67452301
#define SHA1_B 0xefcdab89
#define SHA1_C 0x98badcfe
#define SHA1_D 0x10325476
#define SHA1_E 0xc3d2e1f0

typedef struct {
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;
  uint32_t e;
  uint32_t t;
} sha1_state_t;

typedef union {
  unsigned char c[64];
  uint32_t w[16];
} sha1_msg_t;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static uint32_t swap_uint32(uint32_t val)
{
  val = ((val << 8) & 0xff00ff00) | ((val >> 8) & 0xff00ff);
  return (val << 16) | (val >> 16);
}

static uint64_t swap_uint64(uint64_t val)
{
  val = ((val << 8) & 0xff00ff00ff00ff00ULL) | ((val >> 8) & 0x00ff00ff00ff00ffULL);
  val = ((val << 16) & 0xffff0000ffff0000ULL) | ((val >> 16) & 0x0000ffff0000ffffULL);
  return (val << 32) | (val >> 32);
}
#endif

static uint32_t _rotl(uint32_t i, uint32_t bits)
{
  return (i << bits) | (i >> (32 - bits));
}

static void _sha1_block(sha1_msg_t *msg, sha1_state_t *s)
{
  unsigned int i;
  sha1_state_t ls = *s;

  for (i = 0; i < 80; i++) {

    if (i >= 16) {
      ls.t = msg->w[(i+13) & 0xf] ^ msg->w[(i+8) & 0xf] ^ msg->w[(i+2) & 0xf] ^ msg->w[i & 0xf];
      msg->w[i & 0xf] = _rotl(ls.t, 1);
    }
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    else {
      msg->w[i] = swap_uint32(msg->w[i]);
    }
#endif

    if (i < 20)
      ls.t = ((ls.b & ls.c) | ((~ls.b) & ls.d)) + SHA1_K00;
    else if (i < 40)
      ls.t = (ls.b ^ ls.c ^ ls.d) + SHA1_K20;
    else if (i < 60)
      ls.t = ((ls.b & ls.c) | (ls.d & (ls.b | ls.c))) + SHA1_K40;
    else
      ls.t = (ls.b ^ ls.c ^ ls.d) + SHA1_K60;
    ls.t += _rotl(ls.a, 5) + ls.e + msg->w[i & 0xf];

    ls.e = ls.d;
    ls.d = ls.c;
    ls.c = _rotl(ls.b, 30);
    ls.b = ls.a;
    ls.a = ls.t;
  }

  s->a += ls.a;
  s->b += ls.b;
  s->c += ls.c;
  s->d += ls.d;
  s->e += ls.e;
}

int sha1(unsigned char *buf, unsigned int buflen, unsigned char *hash)
{
  sha1_msg_t msg;
  sha1_state_t s;
  size_t len;
  unsigned int i, bit_added = 0, size_added = 0;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  uint64_t BE_len = swap_uint64(8 * buflen);
#else
  uint64_t BE_len = (uint64_t)(8 * buflen);
#endif

  s.a = SHA1_A;
  s.b = SHA1_B;
  s.c = SHA1_C;
  s.d = SHA1_D;
  s.e = SHA1_E;

  do {

    if (buflen < sizeof(msg)) {
      len = buflen;
      buflen = 0;
      memset(msg.c + len, 0, sizeof(msg) - len);
    }
    else {
      len = sizeof(msg);
      buflen -= sizeof(msg);
    }
    memcpy(msg.c, buf, len);

    if (len < sizeof(msg) && !bit_added) {
      *(msg.c + len) = 0x80;
      bit_added++;
    }
    if (len < sizeof(msg) - 8 && !size_added) {
      memcpy(msg.c + 56, (unsigned char *)&BE_len, 8);
      size_added++;
    }
    _sha1_block(&msg, &s);
    buf += len;

  } while (!size_added || !bit_added);

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  for (i = 0; i < 5; i++) {
    *((uint32_t *)&s + i) = swap_uint32(*((uint32_t *)&s + i));
  }
#endif

  for (i = 0; i < 20; i++) {
    *(hash + i) = *((unsigned char *)&s + i);
  }

  return 0;
}
