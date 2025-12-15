#include <check.h>
#include <string.h>
#include "numberlib.h"
#include <ctype.h>


static void copy_out(char *dst, size_t cap, const char *src)
{
    ck_assert_ptr_ne(src, NULL);
    ck_assert_int_lt((int)strlen(src), (int)cap);
    strcpy(dst, src);
}

static void to_upper(char *s)
{
    for (; *s; ++s)
        *s = (char)toupper((unsigned char)*s);
}


START_TEST(test_hex_basic)
{
    char s[128];

    copy_out(s, sizeof(s), to_hex(0));
    to_upper(s);
    ck_assert_str_eq(s, "0X0");

    copy_out(s, sizeof(s), to_hex(10));
    to_upper(s);
    ck_assert_str_eq(s, "0XA");

    copy_out(s, sizeof(s), to_hex(15));
    to_upper(s);
    ck_assert_str_eq(s, "0XF");

    copy_out(s, sizeof(s), to_hex(31));
    to_upper(s);
    ck_assert_str_eq(s, "0X1F");

    copy_out(s, sizeof(s), to_hex(255));
    to_upper(s);
    ck_assert_str_eq(s, "0XFF");

    copy_out(s, sizeof(s), to_hex(65));
    to_upper(s);
    ck_assert_str_eq(s, "0X41");


}
END_TEST

START_TEST(test_hex_consistency)
{
    char a[128], b[128];
    copy_out(a, sizeof(a), to_hex(1234));
    copy_out(b, sizeof(b), to_hex(1234));
    ck_assert_str_eq(a, b);
}
END_TEST

Suite *hex_suite(void)
{
    Suite *s = suite_create("hex");
    TCase *tc = tcase_create("core");
    tcase_add_test(tc, test_hex_basic);
    tcase_add_test(tc, test_hex_consistency);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(hex_suite());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed != 0;
}
