
/* Released under the 2-Clause BSD License. */

#ifndef LU_SHA1
#define LU_SHA1

#define SHA1_LENGTH 20

void sha1(const unsigned char *, unsigned int, unsigned char *);
void hmac_sha1(unsigned char *, unsigned int, const unsigned char *, unsigned char *);

#endif /* LU_SHA1 */
