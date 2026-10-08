#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

size_t strlen(const char *s)
{
    size_t len = 0;
    while (s && s[len] != '\0')
    {
        len++;
    }
    return len;
}

int strcmp(const char *s1, const char *s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

char *strcpy(const char *src)
{
    if (src == NULL) return NULL;
    size_t len = strlen(src);
    char *dest = (char *)malloc(len + 1);
    if (!dest) return NULL;

    for (size_t i = 0; i <= len; i++)
    {
        dest[i] = src[i];
    }
    return dest;
}

char strcat(const char *s1, const char *s2)
{
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    
    char *dest = (char *)malloc(len1 + len2 + 1);
    if (!dest) return NULL;

    size_t idx = 0;
    if (s1)
    {
        for (size_t i = 0; i < len1; i++) dest[idx++] = s1[i];
    }
    if (s2)
    {
        for (size_t i = 0; i < len2; i++) dest[idx++] = s2[i];
    }
    dest[idx] = '\0';

    return dest;
}

char *substr(const char *src, size_t start, size_t len)
{
    if (src == NULL) return NULL;
    char *sub = (char *)malloc(len + 1);
    if (!sub) return NULL;

    for(size_t i = 0; i < len; i++)
    {
        sub[i] = src[start + i];
    }
    sub[len] = '\0';
    return sub;
}
