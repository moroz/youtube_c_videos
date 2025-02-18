#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

unsigned char decode_base32_char(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A';
  }

  if (c >= '2' && c <= '7') {
    return 26 + c - '2';
  }

  return 0xFF;
}

int decode_base32(const char *src, unsigned char *dst) {
  bool end = false;
  int dsti = 0;
  int n = 0;

  while (*src != 0 && !end) {
    uint8_t dbuf[8];
    int dlen = 8;

    for (int j = 0; j < 8;) {
      if (*src == 0) {
        dlen = j;
        end = true;
        break;
      }

      char c = *src;
      src++;

      int len = strlen(src);
      if (c == '=' && j >= 2 && len < 8) {
        // We've reached the end of the string and there is padding
        if (len + j < 8 - 1) {
          // corrupt input, not enough padding
          return -1;
        }

        for (int k = 0; k < 8 - 1 - j; k++) {
          if (len > k && src[k] != '=') {
            // incorrect padding
            return -2;
          }
        }

        dlen = j;
        end = true;

        if (dlen == 1 || dlen == 3 || dlen == 6) {
          // incorrect length
          return -3;
        }
        break;
      }

      dbuf[j] = decode_base32_char(c);
      if (dbuf[j] == 0xFF) {
        // invalid character
        return -4;
      }
      j++;
    }

    switch (dlen) {
    case 8:
      dst[dsti + 4] = dbuf[6] << 5 | dbuf[7];
      n++;
      // fallthrough

    case 7:
      dst[dsti + 3] = dbuf[4] << 7 | dbuf[5] << 2 | dbuf[6] >> 3;
      n++;

    case 5:
      dst[dsti + 2] = dbuf[3] << 4 | dbuf[4] >> 1;
      n++;

    case 4:
      dst[dsti + 1] = dbuf[1] << 6 | dbuf[2] << 1 | dbuf[3] >> 4;
      n++;

    case 2:
      dst[dsti] = dbuf[0] << 3 | dbuf[1] >> 2;
      n++;
    }
    dsti += 5;
  }

  return n;
}

int main() {
  const char *secret = "4DIDVDK7NMU72R34TF5XNXWQBJYEI2RQ";
  unsigned char dst[80];
  int rc = decode_base32(secret, dst);

  for (int i = 0; i < rc; i++) {
    printf("%02X ", dst[i]);
    if (i != 0 && i % 10 == 9) {
      putchar('\n');
    }
  }

  return 0;
}
