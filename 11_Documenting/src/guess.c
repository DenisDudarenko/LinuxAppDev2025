#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>

#ifndef LOCALEDIR
#define LOCALEDIR "."
#endif

#ifndef PACKAGE
#define PACKAGE "guess"
#endif

/** Translate a string using gettext() */
#define _(S) gettext(S)

/** Roman table size: indices 1..100 are valid */
#define NUM_OF_ROMANS 101

/**
 * Roman numerals table for values 0..100.
 *
 * Index 1..100 contains valid Roman numerals (I..C).
 */
static const char *roman[NUM_OF_ROMANS] = {
    "NULL",
    "I","II","III","IV","V","VI","VII","VIII","IX","X",
    "XI","XII","XIII","XIV","XV","XVI","XVII","XVIII","XIX","XX",
    "XXI","XXII","XXIII","XXIV","XXV","XXVI","XXVII","XXVIII","XXIX","XXX",
    "XXXI","XXXII","XXXIII","XXXIV","XXXV","XXXVI","XXXVII","XXXVIII","XXXIX","XL",
    "XLI","XLII","XLIII","XLIV","XLV","XLVI","XLVII","XLVIII","XLIX","L",
    "LI","LII","LIII","LIV","LV","LVI","LVII","LVIII","LIX","LX",
    "LXI","LXII","LXIII","LXIV","LXV","LXVI","LXVII","LXVIII","LXIX","LXX",
    "LXXI","LXXII","LXXIII","LXXIV","LXXV","LXXVI","LXXVII","LXXVIII","LXXIX","LXXX",
    "LXXXI","LXXXII","LXXXIII","LXXXIV","LXXXV","LXXXVI","LXXXVII","LXXXVIII","LXXXIX","XC",
    "XCI","XCII","XCIII","XCIV","XCV","XCVI","XCVII","XCVIII","XCIX","C"
};

/**
 * Convert an integer (n < 100) to a Roman string using a table.
 *
 *
 * @param n Number in range [1..100]
 * @return Roman digits string (e.g., "IV"), or NULL if failed
 */
static const char *int_to_roman(int n)
{
    if (n < 1 || n > 100) return NULL;
    return roman[n];
}

/**
 * Convert a Roman numeral string to an integer (1..100) using a table.
 *
 * @param s Roman numeral string
 * @return Integer in range [1..100], or 0 if not found.
 */
static int roman_to_int(const char *s)
{
    if (!s || !*s) return 0;
    for (int i = 1; i <= 100; i++) {
        if (strcmp(s, roman[i]) == 0) return i;
    }
    return 0;
}

static void print_help(const char *prog)
{
    printf(_("Usage: %s [-r]\n\n"), prog);

    printf(_("Options:\n"));
    printf(_("  -r      Use Roman digits\n"));
    printf(_("  -h      Show help message\n"));
    printf(_("  --help  Show help message\n\n"));

    printf(_("Game:\n"));
    printf(_("Think of a number from 1 to 100. I will guess it\n"));
    printf(_("Answer only: Yes or No\n\n"));
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    int roman_mode = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            roman_mode = 1;
            continue;
        }
        if (strcmp(argv[i], "-h") == 0 ||
            strcmp(argv[i], "--help") == 0 ||
            strcmp(argv[i], "--help-md") == 0) {
            print_help(argv[0]);
            return 0;
        }
        fprintf(stderr, "%s: %s\n", _("Unknow argument"), argv[i]);
        fprintf(stderr, "%s\n", _("For help use --help"));
        return 1;
    }

    if (roman_mode)
        puts(_("Get a number from I to C. I will guess it"));
    else
        puts(_("Get a number from 1 to 100. I will guess it"));

    int a = 1, b = 100;
    char answer[16];

    while (a < b) {
        int mid = (a + b) / 2;

        if (!roman_mode) {
            printf(_("Is your number greater than %d? (Yes/No): "), mid);
        } else {
            const char *rmid = int_to_roman(mid);
            printf(_("Is your number greater than %s? (Yes/No): "), rmid ? rmid : "?");
        }

        fflush(stdout);

        if (scanf("%15s", answer) != 1) {
            fprintf(stderr, "%s\n", _("Error. EOF"));
            return 1;
        }

        if (strcmp(answer, _("Yes")) == 0) { a = mid + 1; continue; }
        if (strcmp(answer, _("No"))  == 0) { b = mid;     continue; }

        fprintf(stderr, "%s", _("Invalid answer, type only 'Yes' or 'No'\n"));
    }

    if (!roman_mode) {
        printf(_("Your number is %d\n"), a);
    } else {
        const char *ra = int_to_roman(a);
        printf(_("Your number is %s\n"), ra ? ra : "?");
    }

    (void)roman_to_int;
    return 0;
}
