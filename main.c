
#include <stdio.h>
#include <string.h>
#include "mp3.h"

/* Main function: handles command-line arguments */
int main(int argc, char *argv[])
{
    /* Initialize the MP3 tag structure */
    MP3Tag song = {0};

    /* Display help when -h is specified */
    if (argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        help_mp3();
        return 0;
    }

    /* Check whether sufficient arguments are provided */
    if (argc < 3)
    {
        printf("\nInsufficient arguments!\n\n");
        help_mp3();
        return 1;
    }

    /* View MP3 metadata */
    if (strcmp(argv[2], "-v") == 0)
    {
        /* Viewing requires exactly a filename and an option */
        if (argc != 3)
        {
            printf("\nInvalid number of arguments!\n\n");
            help_mp3();
            return 1;
        }

        view_mp3(&song, argv[1]);
    }
    /* Edit a selected metadata tag */
    else if (strcmp(argv[2], "-e") == 0)
    {
        /* Editing requires a filename, -e, and a tag option */
        if (argc != 4)
        {
            printf("\nInvalid number of arguments!\n\n");
            help_mp3();
            return 1;
        }

        edit_mp3(&song, argv);
    }
    /* Handle an unsupported option */
    else
    {
        printf("\nUnknown option: %s\n", argv[2]);
        printf("Enter ./a.out -h for the help guide.\n\n");
        return 1;
    }

    return 0;
}

