#include <stddef.h>
#pragma once

// --- String Helper Functions ---

// String length
size_t length(const char *s);

// String comparison
int compare(const char *s1, const char *s2);

// String copy
char *copy(const char *src);

// String concatenation
char *concat(const char *s1, const char *s2);

// Substring retrieval
char *substring(const char *src, size_t start, size_t len);

// Complete slice
char *absslice(const char *src, char *removed);

// --- File Functions ---

int fileExists(const char *fileName);

char *getFileContent(const char *filePath);

// --- Data Structures ---

// Word Entry
typedef struct WordEntry {
    char *word;
    int count;
} WordEntry;

// Word Table
typedef struct WordTable {
    WordEntry *entries;
    size_t size;
    size_t capacity;
} WordTable;

// --- Language Functions ---

char *count_words(const char *input);