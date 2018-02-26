#include "sha1.h"
#include <string.h>
#include <stdlib.h>

#define SHA1_LENGTH 20
#define HMAC_KEY_LENGTH 64
#define HMAC_IPAD 0x36
#define HMAC_OPAD 0x5c

int hmac_sha1_append(unsigned char *buf, unsigned int msg_len, unsigned char *key)
{
  unsigned int i;

  /* Copy key. */
  memcpy(buf, key, 64);

  /* XOR key with ipad. */
  for (i = 0; i < 64; i++) {
    *(buf + i) ^= 0x36;
  }

  /* Backup first 20 bytes that will be overwriten by first SHA1 value. */
  memcpy(buf + 64 + 492, buf + 64, 20);

  /* First HMAC pass. */
  sha1(buf, 64 + msg_len, buf + 64);

  /* Copy key */
  memcpy(buf, key, 64);

  /* XOR key with opad. */
  for (i = 0; i < 64; i++) {
    *(buf + i) ^= 0x5c;
  }

  /* Second HMAC pass. */
  sha1(buf, 84, buf);

  /* Restore first 20 bytes. */
  memcpy(buf + 64, buf + 64 + 492, 20);

  /* Append HMAC */
  memcpy(buf + 64 + msg_len, buf, 20);

  return 0;
}

int hmac_sha1_verify(unsigned char *buf, unsigned int buflen, unsigned char *key, unsigned char *hmac)
{
  unsigned char *tmpbuf;
  unsigned int i;
  size_t len;
  int rv;

  len = buflen + HMAC_KEY_LENGTH;
  tmpbuf = malloc(len * sizeof(unsigned char));
  if (!tmpbuf) {
    return -1;
  }

  memcpy(tmpbuf, key, HMAC_KEY_LENGTH);
  memcpy(tmpbuf + HMAC_KEY_LENGTH, buf, buflen);

  for (i = 0; i < HMAC_KEY_LENGTH; i++) {
    *(tmpbuf + i) ^= HMAC_IPAD;
  }

  sha1(tmpbuf, len, tmpbuf + HMAC_KEY_LENGTH);

  memcpy(tmpbuf, key, HMAC_KEY_LENGTH);
  for (i = 0; i < HMAC_KEY_LENGTH; i++) {
    *(tmpbuf + i) ^= HMAC_OPAD;
  }

  sha1(tmpbuf, HMAC_KEY_LENGTH + SHA1_LENGTH, tmpbuf);

  rv = memcmp(tmpbuf, hmac, SHA1_LENGTH);
  free(tmpbuf);

  return !rv ? 0 : -1;
}
