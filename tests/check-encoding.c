#include <cgreen/cgreen.h>
#include "lib/packing.h"

Describe(Packing);
BeforeEach(Packing) {}
AfterEach(Packing) {}

Ensure(Packing, packs_key_value) {
    char expected[] = { 0x05, 0x48, 0x45, 0x4c, 0x4c, 0x4f,
                        0x05, 0x57, 0x4f, 0x52, 0x4c, 0x44 };
    char *got = pack_from_kv("HELLO", "WORLD");
    assert_that(got, is_not_null);
    assert_that(got, is_equal_to_string(expected));

    size_t pack_size = strlen(got);
    assert_that(pack_size, is_equal_to(strlen("_HELLO_WORLD")));
    assert_that(got[pack_size], is_equal_to('\0'));

    free(got);
}

int main(int argc, char **argv) {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, Packing, packs_key_value);
    return run_test_suite(suite, create_text_reporter());
}
