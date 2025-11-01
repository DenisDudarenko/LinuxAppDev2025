#include "rhash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#ifdef HAVE_READLINE
#  include <readline/readline.h>
#endif

static unsigned getHash(const char *name)
{
    if (!name || !*name) return 0;
    if (strcmp(name, "md5") == 0)  return RHASH_MD5;
    if (strcmp(name, "sha1") == 0) return RHASH_SHA1;
    if (strcmp(name, "tth") == 0)  return RHASH_TTH;
    return 0;
}

static ssize_t read_line(char **buf)
{
    free(*buf);
#ifdef HAVE_READLINE
    *buf = readline(NULL);
    return (ssize_t)strlen(*buf);
#else
    size_t _;
    return getline(buf, &_, stdin);
#endif
}

int main(void)
{
    rhash_library_init();

    char *line = NULL;

    while (1) {
        ssize_t n = read_line(&line);
        if (n < 0) break;

        if (n > 0 && line[n - 1] == '\n')
            line[n - 1] = '\0';

        char *save = NULL;
        char *algo = strtok_r(line, " \t\r\n", &save);
        char *arg  = strtok_r(NULL, " \t\r\n", &save);
        if (!algo || !arg) continue;

        char algo_lc[32];
        size_t i = 0;
        for (; i + 1 < sizeof(algo_lc) && algo[i]; i++)
            algo_lc[i] = (char)tolower((unsigned char)algo[i]);
        algo_lc[i] = '\0';

        unsigned id = getHash(algo_lc);
        if (!id) {
            fprintf(stderr, "Not known hash\n");
            continue;
        }

        unsigned char digest[64];
        int rc;

        if (arg[0] == '"') {
            char *s = arg + 1;
            size_t len = strlen(s);
            if (len > 0 && s[len - 1] == '"') {
                s[len - 1] = '\0';
                len--;
            }
            rc = rhash_msg(id, s, len, digest);
            if (rc < 0) {
                fprintf(stderr, "Failed to get hash\n");
                continue;
            }
        } else {
            rc = rhash_file(id, arg, digest);
            if (rc < 0) {
                fprintf(stderr, "Failed to open file: %s\n", strerror(errno));
                continue;
            }
        }

        char out[256];
        int flags = (algo && *algo && islower((unsigned char)algo[0])) ? RHPR_BASE64 : RHPR_HEX;
        size_t out_len = rhash_print_bytes(out, digest, rhash_get_digest_size(id), flags);
        out[out_len] = '\0';

        printf("%s\n", out);
    }

    free(line);
    return 0;
}
