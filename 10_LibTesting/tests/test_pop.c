#include <check.h>
#include "buf.h"

START_TEST(test_pop)
{
    float *a = 0;

    buf_push(a, 1.1f);
    buf_push(a, 1.2f);
    buf_push(a, 1.3f);
    buf_push(a, 1.4f);

    ck_assert_uint_eq(buf_size(a), 4);
    ck_assert(a[3] == (float)1.4f);

    ck_assert(a[--buf_ptr(a)->size] == (float)1.4f);
    buf_trunc(a, 3);

    ck_assert(a[--buf_ptr(a)->size] == (float)1.3f);
    ck_assert(a[--buf_ptr(a)->size] == (float)1.2f);
    ck_assert(a[--buf_ptr(a)->size] == (float)1.1f);

    ck_assert_uint_eq(buf_size(a), 0);

    buf_free(a);
}
END_TEST

Suite *suite_pop(void)
{
    Suite *s = suite_create("pop");
    TCase *tc = tcase_create("core");
    tcase_add_test(tc, test_pop);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(suite_pop());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed;
}
