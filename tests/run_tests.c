#include <cgreen/cgreen.h>

TestSuite *packing_tests();
TestSuite *db_writing_tests();

int main(int argc, char **argv) {
    TestSuite *suite = create_test_suite();
    add_suite(suite, packing_tests());
    add_suite(suite, db_writing_tests());
    return run_test_suite(suite, create_text_reporter());
}
