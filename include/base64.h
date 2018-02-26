
/* Released under the 2-Clause BSD License. */

#ifndef LU_BASE64_H
#define LU_BASE64_H

unsigned int base64_encoded_length(const unsigned int);
int base64_encode(const char *, char *, const unsigned int);

void base64_free_decoding_table(void);

unsigned int base64_decoded_length(const unsigned int);
unsigned int base64_decode(const char *, char *, unsigned int);

#endif
