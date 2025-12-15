#include "numberlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <locale.h>
#include <libintl.h>

#define _(S) gettext(S)

#ifndef LOCALEDIR
#define LOCALEDIR "."
#endif


static void print_table(int n)
{
    printf(_("Number : %d\n"), n);
    printf(_("Roman  : %s\n"), to_roman(n) ? to_roman(n) : "?");
    printf(_("Binary : %s\n"), to_binary(n));
    printf(_("Hex    : %s\n"), to_hex(n));
    printf(_("Symbol : %s\n"), to_symbol(n));
}

static void print_version(void)
{
    puts("numberstat 1.0");
}

static void print_help(const char *prog)
{
    printf(_("Usage:\n"));
    printf("  %s NUMBER\n", prog);
    printf("  %s [OPTION] NUMBER\n\n", prog);

    printf(_("Options:\n"));
    printf("  -r, --roman    %s\n", _("Print number in Roman numerals"));
    printf("  -b, --binary   %s\n", _("Print number in binary"));
    printf("  -x, --hex      %s\n", _("Print number in hexadecimal"));
    printf("  -s, --symbol   %s\n", _("Print number as ASCII symbol"));
    printf("  -h, --help     %s\n\n", _("Show this help and exit"));

    printf(_("Without options, a full table is printed.\n"));
}

int main(int argc, char **argv)
{
    const char *dir = getenv("LOCALEDIR");
    if (!dir || !*dir) dir = LOCALEDIR;

    setlocale(LC_ALL, "");
    bindtextdomain("numberstat", dir);
    textdomain("numberstat");

    int n;
    int mode = 0;

    if (argc < 2) {
        print_help(argv[0]);
        return 1;
    }

    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        print_help(argv[0]);
        return 0;
    }

    if (argc == 2 && !strcmp(argv[1], "--version")) {
        print_version();
        return 0;
    }

    if (argv[1][0] == '-') {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
            print_help(argv[0]);
            return 0;
        }
        if (argc < 3) return 1;
        n = atoi(argv[2]);

        if (!strcmp(argv[1], "-r") || !strcmp(argv[1], "--roman"))  mode = 'r';
        if (!strcmp(argv[1], "-b") || !strcmp(argv[1], "--binary")) mode = 'b';
        if (!strcmp(argv[1], "-x") || !strcmp(argv[1], "--hex"))    mode = 'x';
        if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--symbol")) mode = 's';
    } else {
        n = atoi(argv[1]);
    }

    if (mode == 0) {
        print_table(n);
        return 0;
    }

    switch (mode) {
        case 'r': printf("%s\n", to_roman(n));  break;
        case 'b': printf("%s\n", to_binary(n)); break;
        case 'x': printf("%s\n", to_hex(n));    break;
        case 's': printf("%s\n", to_symbol(n)); break;
    }

    return 0;
}
