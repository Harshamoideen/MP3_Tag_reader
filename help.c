
#include <stdio.h>
#include "mp3.h"

/*
 * Function: help_mp3
 * Description: Displays usage instructions, available commands,
 *              editing options, and examples for the MP3 Tag Reader.
 * Return: void
 */
void help_mp3()
{
    printf("\n");
    printf("=====================================================\n");
    printf("                  MP3 TAG READER\n");
    printf("=====================================================\n");

    printf("\nDESCRIPTION:\n");
    printf("  View and edit ID3 metadata tags in MP3 audio files.\n");

    printf("\nUSAGE:\n");
    printf("  ./a.out <file.mp3> <option>\n");

    printf("\nAVAILABLE OPTIONS:\n");
    printf("  -v    View MP3 metadata tags\n");
    printf("  -e    Edit a specific metadata tag\n");
    printf("  -h    Display this help menu\n");

    printf("\nVIEW TAGS:\n");
    printf("  Syntax:\n");
    printf("    ./a.out <file.mp3> -v\n");
    printf("  Displays the metadata stored in the MP3 file.\n");

    printf("\nEDIT TAGS:\n");
    printf("  Syntax:\n");
    printf("    ./a.out <file.mp3> -e <tag>\n");
    printf("  Allows you to modify a selected metadata field.\n");

    printf("\nTAG OPTIONS:\n");
    printf("  -t    Title\n");
    printf("  -A    Artist\n");
    printf("  -a    Album\n");
    printf("  -y    Year\n");
    printf("  -g    Genre\n");
    printf("  -c    Comment\n");

    printf("\nEXAMPLES:\n");
    printf("  View tags:\n");
    printf("    ./a.out song.mp3 -v\n");
    printf("\n");
    printf("  Edit title:\n");
    printf("    ./a.out song.mp3 -e -t\n");
    printf("\n");
    printf("  Edit artist:\n");
    printf("    ./a.out song.mp3 -e -A\n");
    printf("\n");
    printf("  Display help:\n");
    printf("    ./a.out -h\n");

    printf("\nNOTES:\n");
    printf("  * Provide a valid MP3 file as input.\n");
    printf("  * Editing requires confirmation and a new value.\n");
    printf("  * Keep a backup of important audio files.\n");

    printf("\n=====================================================\n\n");
}

