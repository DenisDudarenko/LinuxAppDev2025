#include <check.h>
#include "buf.h"

START_TEST(test_grow)
{
    int *ai = 0;

    buf_grow(ai, 1000);
    ck_assert_uint_eq(buf_capacity(ai), 1000);
    ck_assert_uint_eq(buf_size(ai), 0);

    buf_trunc(ai, 100);
    ck_assert_uint_eq(buf_capacity(ai), 100);
    buf_free(ai);
}
END_TEST

Suite *suite_grow(void)
{
    Suite *s = suite_create("grow");
    TCase *tc = tcase_create("core");
    tcase_add_test(tc, test_grow);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(suite_grow());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed;
}
