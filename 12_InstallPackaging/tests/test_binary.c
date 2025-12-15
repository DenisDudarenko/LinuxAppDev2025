#include <check.h>
#include <string.h>
#include "numberlib.h"

static void copy_out(char *dst, size_t cap, const char *src)
{
    ck_assert_ptr_ne(src, NULL);
    ck_assert_int_lt((int)strlen(src), (int)cap);
    strcpy(dst, src);
}

START_TEST(test_binary_basic)
{
    char s[128];

    copy_out(s, sizeof(s), to_binary(0));
    ck_assert_str_eq(s, "0");

    copy_out(s, sizeof(s), to_binary(1));
    ck_assert_str_eq(s, "1");

    copy_out(s, sizeof(s), to_binary(2));
    ck_assert_str_eq(s, "10");

    copy_out(s, sizeof(s), to_binary(3));
    ck_assert_str_eq(s, "11");

    copy_out(s, sizeof(s), to_binary(4));
    ck_assert_str_eq(s, "100");

    copy_out(s, sizeof(s), to_binary(65));
    ck_assert_str_eq(s, "1000001");
}
END_TEST

START_TEST(test_binary_consistency)
{
    char a[128], b[128];
    copy_out(a, sizeof(a), to_binary(10));
    copy_out(b, sizeof(b), to_binary(10));
    ck_assert_str_eq(a, b);
}
END_TEST

Suite *binary_suite(void)
{
    Suite *s = suite_create("binary");
    TCase *tc = tcase_create("core");
    tcase_add_test(tc, test_binary_basic);
    tcase_add_test(tc, test_binary_consistency);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(binary_suite());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed != 0;
}
