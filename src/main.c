#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(int argc, char *argv[]) {
    if (argc > 3)
    {
        if (compare(argv[1], "-getwordreport") == 1)
        {
            char *full_input = copy("");
            for (int i = 2; i < argc; i++)
            {
                char *temp_str = concat(full_input, argv[i]);
                free(full_input);
                full_input = temp_str;

                if (i < argc - 1)
                {
                    char *space_str = concat(full_input, " ");
                    free(full_input);
                    full_input = space_str;
                }
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
    }
    else if (argc < 3)
    {
        printf("Usage: %s -%subcmd% <text input>\n", argv[0]);
        return 1;
    }

    return 0;
}
