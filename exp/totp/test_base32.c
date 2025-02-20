#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdint.h>
#include <string.h>

int base32_decode(const char *src, unsigned char *dst);
void base32_encode(const uint8_t *src, char *dst, size_t len);

void test_base32_decode(void) {
  const char *base32 = "4DIDVDK7NMU72R34TF5XNXWQBJYEI2RQ";
  const uint8_t expected[] = {0xE0, 0xD0, 0x3A, 0x8D, 0x5F, 0x6B, 0x29,
                              0xFD, 0x47, 0x7C, 0x99, 0x7B, 0x76, 0xDE,
                              0xD0, 0xA,  0x70, 0x44, 0x6A, 0x30};
  uint8_t dst[80];

  int rc = base32_decode(base32, dst);
  CU_ASSERT_EQUAL(rc, 20);

  for (int i = 0; i < 20; i++) {
    CU_ASSERT_EQUAL(dst[i], expected[i]);
  }
}

void test_base32_encode(void) {
  const uint8_t binary[] = {0xE0, 0xD0, 0x3A, 0x8D, 0x5F, 0x6B, 0x29,
                            0xFD, 0x47, 0x7C, 0x99, 0x7B, 0x76, 0xDE,
                            0xD0, 0xA,  0x70, 0x44, 0x6A, 0x30};
  const char *expected = "4DIDVDK7NMU72R34TF5XNXWQBJYEI2RQ";

  char dst[80];
  base32_encode(binary, dst, 20);

  for (int i = 0, n = strlen(expected); i < n; i++) {
    CU_ASSERT_EQUAL(dst[i], expected[i]);
  }
}
