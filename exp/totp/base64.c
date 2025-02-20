#include "base64.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

Base64Encoding NewBase64Encoding(const char *alphabet, char padding) {
  Base64Encoding result;

  result.padding = padding;
  memcpy(result.encodeMap, alphabet, 64);
  memset(result.decodeMap, 0xFF, 256);

  for (int i = 0; i < 64; i++) {
    result.decodeMap[BASE64_ALPHABET[i]] = i;
  }

  return result;
}

Base64Encoding StdEncoding() {
  return NewBase64Encoding(BASE64_ALPHABET, STD_PADDING);
}

Base64Encoding URLEncoding() {
  return NewBase64Encoding(BASE64_URL_ALPHABET, STD_PADDING);
}

int base64_decode(Base64Encoding *enc, const char *src, uint8_t *dst) {
  bool end = false;
  int dsti = 0;
  int n = 0;

  while (*src != 0 && !end) {
    uint8_t dbuf[4];
    int dlen = 4;

    for (int j = 0; j < 4;) {
      char c = *src;

      if (c == 0) {
        dlen = j;
        end = true;
        break;
      }

      src++;

      if (isspace(c)) {
        continue;
      }

      int len = strlen(src);
    }
  }
}
