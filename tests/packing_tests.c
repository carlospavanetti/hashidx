#include <cgreen/cgreen.h>
#include "lib/packing.h"

Describe(Packing);
BeforeEach(Packing) {}
AfterEach(Packing) {}

Ensure(Packing, packs_key_value) {
    char expected[] = "\x05" "HELLO" "\x05" "WORLD";
    char *got = pack_from_kv("HELLO", "WORLD");
    assert_that(got, is_not_null);
    assert_that(got, is_equal_to_string(expected));

    size_t pack_size = strlen(got);
    assert_that(pack_size, is_equal_to(strlen(expected)));
    assert_that(got[pack_size], is_equal_to('\0'));

    free(got);
}

TestSuite *packing_tests() {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, Packing, packs_key_value);
    return suite;
}
