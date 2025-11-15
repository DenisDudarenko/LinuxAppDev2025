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

#define _(STRING) gettext(STRING)

int main(void)
{
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    puts(_("Get a number from 1 to 100. I will guess it"));

    int a = 1, b = 100;
    char answer[16];

    while (a < b) {
        int mid = (a + b) / 2;

        printf(_("Is your number greater than %d? (Yes/No): "), mid);
        fflush(stdout);

        if (scanf("%15s", answer) != 1) {
            fprintf(stderr, "%s\n", _("Error. EOF"));
            return 1;
        }

        if (strcmp(answer, _("Yes")) == 0) { a = mid + 1; continue; }
        if (strcmp(answer, _("No"))  == 0)  { b = mid; continue; }

        fprintf(stderr, _("Invalid answer, type only 'Yes' or 'No'\n"));
    }

    printf(_("Your number is %d\n"), a);
    return 0;
}
