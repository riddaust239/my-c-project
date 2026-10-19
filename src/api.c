#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// --- String Help Functions ---

size_t strlength(const char *s)
{
    size_t len = 0;
    while (s && s[len] != '\0')
    {
        len++;
    }
    return len;
}

int compare(const char *s1, const char *s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

// Allocates memory via malloc and returns a new copy of the source string
char *copy(const char *src)
{
    if (src == NULL) return NULL;
    size_t len = strlength(src);
    char *dest = (char *)malloc(len + 1);
    if (!dest) return NULL;

    for (size_t i = 0; i <= len; i++)
    {
        dest[i] = src[i];
    }
    return dest;
}

// Alllocates memory via mallloc forboth strings
// combined and returns the concatenated string
char *concat(const char *s1, const char *s2)
{
    size_t len1 = s1 ? strlength(s1) : 0;
    size_t len2 = s2 ? strlength(s2) : 0;
    
    char *dest = (char *)malloc(len1 + len2 + 1);
    if (!dest) return "NULL";

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

// Absolute slice (Remove a character from an entire string globally)
char *absslice(const char *src, char *removed)
{
    int len = strlength(src);

    char *dest = (char *)malloc(len + 1);

    size_t idx = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (src[i] != removed)
        {
            dest[idx++] = src[i];
        }
    }

    return dest;
}

// Allocates memory via malloc and extracts a substring slice
char *substring(const char *src, size_t start, size_t len)
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

int is_whitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '.' || c == ',' || c == '!' || c == '?' || c == ';';
}

// --- File Functions

int fileExists(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file != NULL)
    {
        fclose(file);
        printf("File %s is inaccessible and/or doesn't exist", fileName);
        return 1; // File exists and can be read
    }
    return 0; // File does not exist or cannot be accessed
}

char *getFileContent(const char *filePath)
{
    if (!fileExists(filePath))
    {
        return copy("");
    }

    FILE *fptr;

    // Declare the character array
    // for the data to be read from file
    char data[500];
    fptr = fopen(filePath, "r");

    if (fptr == NULL)
    {
        printf("File located at %s has failed to open", filePath);
    }
    else
    {
        printf("The file is now opened.\n");

        // Read the data from the file
        // using fgets() method
        fgets(data, 500, fptr);

        if (data == NULL)
        {
            return copy("");
        }
        else
        {
            return copy(data);
        }
    }
}

// --- Data Structures ---

typedef struct WordEntry {
    char *word;
    int count;
} WordEntry;

typedef struct WordTable {
    WordEntry *entries;
    size_t size;
    size_t capacity;
} WordTable;

// --- Language Functions ---

// Counts words and returns a dynamically allocated
// report string formatted as "%word%: %count%\n"
char *count_words(const char *fileInput)
{
    if (fileInput == NULL || strlength(fileInput) == 0 || fileExists(fileInput) == 0) {
        return copy("");
    }

    const char *input = getFileContent(fileInput);

    WordTable table;
    table.size = 0;
    table.capacity = 4;
    table.entries = (WordEntry *) malloc(table.capacity * sizeof(WordEntry));
    
    size_t i = 0;
    size_t input_len = strlength(input);

    // Parse words using custom whitespace navigation
    while (i < input_len)
    {
        while (i < input_len && is_whitespace(input[i]))
        {
            i++;
        }
        if (i >= input_len) break;
        
        size_t start = i;
        while (i < input_len && !is_whitespace(input[i]))
        {
            i++;
        }

        size_t word_len = i - start;
        
        // Extract token using substring function
        char *token = substring(input, start, word_len);

        int found = 0;
        for (size_t j = 0; j < table.size; j++)
        {
            if (compare(table.entries[j].word, token) == 0)
            {
                table.entries[j].count++;
                found = 1;
                free(token);
                break;
            }
        }

        if (!found)
        {
            if (table.size >= table.capacity)
            {
                table.capacity *= 2;
                table.entries = (WordEntry *) realloc(table.entries, table.capacity * sizeof(WordEntry));
            }
            table.entries[table.size].word = token;
            table.entries[table.size].count = 1;
            table.size++;
        }
    }

    char *report = copy("");
    char line_buffer[128];

    for (size_t j = 0; j < table.size; j++)
    {
        sprintf(line_buffer, "%s: %d\n", table.entries[j].word, table.entries[j].count);
        
        char *new_report = concat(report, line_buffer);
        free(report);
        report = new_report;
    }

    // Clean up internal tracking data structures
    for (size_t j = 0; j < table.size; j++)
    {
        free(table.entries[j].word);
    }
    free(table.entries);

    return report; // Return report
}