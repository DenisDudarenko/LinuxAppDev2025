#include <check.h>
#include "numberlib.h"

START_TEST(test_roman_basic)
{
    ck_assert_str_eq(to_roman(1), "I");
    ck_assert_str_eq(to_roman(4), "IV");
    ck_assert_str_eq(to_roman(9), "IX");
    ck_assert_str_eq(to_roman(42), "XLII");
    ck_assert_str_eq(to_roman(100), "C");
}
END_TEST

START_TEST(test_roman_invalid)
{
    ck_assert_ptr_eq(to_roman(0), NULL);
    ck_assert_ptr_eq(to_roman(-1), NULL);
    ck_assert_ptr_eq(to_roman(101), NULL);
}
END_TEST

Suite *roman_suite(void)
{
    Suite *s = suite_create("roman");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_roman_basic);
    tcase_add_test(tc, test_roman_invalid);

    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(roman_suite());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed != 0;
}
