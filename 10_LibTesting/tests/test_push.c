#include <check.h>
#include "buf.h"

START_TEST(test_push)
{
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);

    ck_assert_uint_eq(buf_size(ai), 10000);

    int match = 0;
    for (int i = 0; i < 10000; i++)
        match += ai[i] == i;
        
    ck_assert_int_eq(match, 10000);
    buf_free(ai);
}
END_TEST

Suite *suite_push(void)
{
    Suite *s = suite_create("push");
    TCase *tc = tcase_create("core");
    tcase_add_test(tc, test_push);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(suite_push());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed;
}
