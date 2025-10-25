#include <dlfcn.h>
#include <string.h>

typedef int (*remove_type)(const char *);

int remove(const char *path) {
    if (strstr(path, "PROTECT") != NULL) {
        return 0;
    }
    
    int res;
    res = ((remove_type)(dlsym(RTLD_NEXT, "remove")))(path);
    return res;
}
