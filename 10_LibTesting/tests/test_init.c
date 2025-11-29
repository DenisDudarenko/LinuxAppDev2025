#include <check.h>
#include <stdlib.h>
#include "buf.h"

START_TEST(test_init)
{
    float *a = 0;

    ck_assert_uint_eq(buf_capacity(a), 0);
    ck_assert_uint_eq(buf_size(a), 0);

    buf_push(a, 1.3f);
    ck_assert_uint_eq(buf_size(a), 1);
    ck_assert(a != 0);
    ck_assert(a[0] == (float)1.3f);

    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert(a != 0);

    buf_free(a);
    ck_assert_ptr_eq(a, 0);
}
END_TEST

Suite *suite_init(void)
{
    Suite *s = suite_create("init");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_init);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(suite_init());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed ? 1 : 0;
}
