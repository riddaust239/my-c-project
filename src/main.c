#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(int argc, char *argv[]) {
    if (argc > 3)
    {
        if (compare(argv[1], "-getwordreport") == 1)
        {
            char *full_input;

            if (fileExists(argv[2]) == 0)
            {
                printf("Failed to fetch word report, input not valid.");
                return 1;
            }
            else if (fileExists(argv[2]) == 1)
            {
                const char *file_input = argv[2];
                full_input = getFileContent(file_input);
            }

            char *log_report = count_words(full_input);

            if (log_report)
            {
                printf("%s", log_report);
                free(log_report);
            }

            free(full_input);
        }
        else if (compare(argv[1], "-absslice") == 1)
        {
            char *str = absslice(argv[2], argv[3]);
            printf(str);
        }
        else
        {
            printf("Usage: %s -\%subcmd% <text input>\n", argv[0]);
        }
    }
    else if (argc < 3)
    {
        printf("Usage: %s -\%subcmd% <text input>\n", argv[0]);
        return 1;
    }

    return 0;
}