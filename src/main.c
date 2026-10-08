#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int main() {
    char *greeting = strcat("Hello, ", "World!");

    if (greeting != NULL) {
        printf("%s\n", greeting);
        free(greeting);
    }

    return 0;
}
