#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>

#define BASE64_ALPHABET                                                        \
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

#define BASE64_URL_ALPHABET                                                    \
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"

#define STD_PADDING '='
#define NO_PADDING 0xFF

typedef struct {
  char encodeMap[64];
  char decodeMap[256];
  char padding;
} Base64Encoding;

Base64Encoding NewBase64Encoding(const char *alphabet, char padding);
Base64Encoding StdEncoding();
Base64Encoding URLEncoding();
int base64_decode(Base64Encoding *enc, const char *src, uint8_t *dst);

#endif
