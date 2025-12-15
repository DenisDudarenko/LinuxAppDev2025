#include "numberlib.h"
#include <stdio.h>
#include <ctype.h>

static const char *roman_table[] = {
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

const char *to_roman(int n)
{
    if (n < 1 || n > 100) return NULL;
    return roman_table[n];
}

const char *to_binary(int n)
{
    static char buf[33];
    int i = 32;
    buf[i] = '\0';

    if (n == 0) {
        buf[--i] = '0';
        return &buf[i];
    }

    while (n > 0) {
        buf[--i] = (n & 1) ? '1' : '0';
        n >>= 1;
    }
    return &buf[i];
}

const char *to_hex(int n)
{
    static char buf[16];
    snprintf(buf, sizeof(buf), "0x%x", n);
    return buf;
}

const char *to_symbol(int n)
{
    static char buf[2];
    if (isprint(n)) {
        buf[0] = (char)n;
        buf[1] = '\0';
        return buf;
    }
    return "?";
}
