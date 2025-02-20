#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdint.h>

void test_base32_decode(void);
void test_base32_encode(void);
void test_base64_decode(void);

int main(void) {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Base32TestSuite", 0, 0);
  CU_add_test(suite, "test of base32_decode", test_base32_decode);
  CU_add_test(suite, "test of base32_encode", test_base32_encode);
  suite = CU_add_suite("Base64TestSuite", 0, 0);
  CU_add_test(suite, "test of base64_decode", test_base64_decode);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return 0;
}
