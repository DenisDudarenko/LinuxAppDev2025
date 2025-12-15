#include <check.h>
#include <string.h>
#include "numberlib.h"

static void copy_out(char *dst, size_t cap, const char *src)
{
    ck_assert_ptr_ne(src, NULL);
    ck_assert_int_lt((int)strlen(src), (int)cap);
    strcpy(dst, src);
}

/*
  Тут я предполагаю типичное поведение:
  - печатные ASCII (32..126) -> один символ строкой ("A", " ", "0", ...)
  - непечатные / вне диапазона -> "?" (или ".") — смени ожидаемое, если у тебя иначе.
*/
START_TEST(test_symbol_basic)
{
    char s[128];

    copy_out(s, sizeof(s), to_symbol(65));
    ck_assert_str_eq(s, "A");

    copy_out(s, sizeof(s), to_symbol(48));
    ck_assert_str_eq(s, "0");

    copy_out(s, sizeof(s), to_symbol(32));
    ck_assert_str_eq(s, " ");  /* пробел */

    copy_out(s, sizeof(s), to_symbol(126));
    ck_assert_str_eq(s, "~");
}
END_TEST

START_TEST(test_symbol_non_printable)
{
    char s[128];

    copy_out(s, sizeof(s), to_symbol(10));   /* \n */
    ck_assert(s[0] == '?' || s[0] == '.');

    copy_out(s, sizeof(s), to_symbol(-1));
    ck_assert(s[0] == '?' || s[0] == '.');

    copy_out(s, sizeof(s), to_symbol(1000));
    ck_assert(s[0] == '?' || s[0] == '.');
}
END_TEST

Suite *symbol_suite(void)
{
    Suite *s = suite_create("symbol");
    TCase *tc = tcase_create("core");
    tcase_add_test(tc, test_symbol_basic);
    tcase_add_test(tc, test_symbol_non_printable);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    SRunner *sr = srunner_create(symbol_suite());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed != 0;
}
