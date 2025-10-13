#include <stdlib.h>
#include <stdio.h>

const char *help = "Help message";

void print_range(int n, int m, int s){
        int i = 0;
        for (i = n; i < m; i += s)
                printf("%d\n", i);
}

int main(int argc, char *argv[]) {
        int n, m, s;
        switch (argc) {
        case 1:
                printf("%s\n", help);
                break;
        case 2:
                n = atoi(argv[1]);
                print_range(0, n, 1);
                break;
        case 3:
                n = atoi(argv[1]);
                m = atoi(argv[2]);
                print_range(n, m, 1);
                break;
        case 4:
                n = atoi(argv[1]);
                m = atoi(argv[2]);
                s = atoi(argv[3]);
                print_range(n, m, s);
                break;
        default:
                printf("Wrong num of args\n");
                return 1;
                break;
        }

        return 0;
}
