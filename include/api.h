#pragma once

// String length
size_t strlen(const char *s);

// String comparison
int strcmp(const char *s1, const char *s2);

// String copy
char *strcpy(const char *src);

// String concatenation
char strcat(const char *s1, const char *s2);

// Substring retrieval
char *substr(const char *src, size_t start, size_t len);
