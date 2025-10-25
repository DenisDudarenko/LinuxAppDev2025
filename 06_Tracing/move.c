#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, ("Incorrect number of arguments"));
        return 1;
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];

    FILE *in = fopen(infile, "rb");
    if (!in) {
        fprintf(stderr, ("Failed to open input file"));
        return 2;
    }

    FILE *out = fopen(outfile, "wb");
    if (!out) {
        fprintf(stderr, ("Failed to open output file"));
        fclose(in);
        return 3;
    }

    setvbuf(out, NULL, _IONBF, 0);

    int c;
    while ((c = fgetc(in)) != EOF) {
        if (fputc(c, out) == EOF) {
            fprintf(stderr, ("Failed to write into output file"));
            fclose(in);
            fclose(out);
            remove(outfile);
            return 4;
        }
    }

    if (ferror(in)) {
        fprintf(stderr, ("Failed to read from input file"));
        fclose(in);
        fclose(out);
        remove(outfile);
        return 5;
    }

    if (fclose(in) == EOF) {
        fprintf(stderr, ("Failed to close input file"));
        fclose(out);
        remove(outfile);
        return 6;
    }

    if (fclose(out) == EOF) {
        fprintf(stderr, ("Failed to close output file"));
        return 7;
    }

    if (remove(argv[1]) != 0) {
        fprintf(stderr, ("Failed to remove input file"));
        return 8;
    }

    return 0;
}

