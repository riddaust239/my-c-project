#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat(const char *s1, const char *s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    // Allocate memory for s1 + s2 + null terminator ('\0')
    char *result = malloc(len1 + len2 + 1);
    
    if (result == NULL)
    {
        return NULL; // Memory allocation failed.
    }

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}
