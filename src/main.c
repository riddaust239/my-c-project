#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int main(void) {
    char *greeting = concat("Hello, ", "World!");

    if (greeting != NULL) {
        printf("%s\n", greeting);
        free(greeting);
    }

    return 0;
}