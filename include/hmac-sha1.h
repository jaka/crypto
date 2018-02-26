
/* Released under the 2-Clause BSD License. */

#ifndef LU_HMAC_SHA1
#define LU_HMAC_SHA1

int hmac_sha1_append(unsigned char *, unsigned int, unsigned char *);
/* Plain text must be located in location of first argument + 64! */

int hmac_sha1_verify(unsigned char *, unsigned int, unsigned char *, unsigned char *);

#endif /* LU_HMAC_SHA1 */
