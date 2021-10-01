#include <cgreen/cgreen.h>
#include "lib/hashidx.h"

HashIdxConnection *database;

Describe(WriteToDB);
BeforeEach(WriteToDB) {
    database = hashidx_open();
}
AfterEach(WriteToDB) {
    hashidx_close(database);
}

Ensure(WriteToDB, writes_one_pack) {
    hashidx_write(database, "hello", "world");

    char expected[] = "\x05" "hello" "\x05" "world";
    char *got = latest_segment_content(database);

    assert_that(got, is_equal_to_string(expected));
    free(got);
}

Ensure(WriteToDB, append_new_pack) {
    hashidx_write(database, "key:1", "value_1");
    hashidx_write(database, "key:2", "value_2");

    char expected[] = "\x05" "key:1" "\x07" "value_1"
                      "\x05" "key:2" "\x07" "value_2";
    char *got = latest_segment_content(database);

    assert_that(got, is_equal_to_string(expected));
    free(got);
}

Ensure(WriteToDB, append_pack_with_same_key) {
    hashidx_write(database, "hello", "world");
    hashidx_write(database, "hello", "everybody");

    char expected[] = "\x05" "hello" "\x05" "world"
                      "\x05" "hello" "\x09" "everybody";
    char *got = latest_segment_content(database);

    assert_that(got, is_equal_to_string(expected));
    free(got);
}

TestSuite *db_writing_tests() {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, WriteToDB, writes_one_pack);
    add_test_with_context(suite, WriteToDB, append_new_pack);
    add_test_with_context(suite, WriteToDB, append_pack_with_same_key);
    return suite;
}
