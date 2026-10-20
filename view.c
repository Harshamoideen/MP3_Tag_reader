
#include <stdio.h>
#include <string.h>
#include "mp3.h"

/*
 * Function: view_mp3
 * Description: Reads and displays ID3 metadata tags from an MP3 file.
 *              Extracts the title, artist, album, year, genre, and comment.
 *
 * Arguments:
 *   song      - Pointer to the structure storing the extracted metadata.
 *   file_name - Name of the MP3 file to read.
 *
 * Return: void
 */
void view_mp3(MP3Tag *song, char *file_name)
{
    /* Open the MP3 file in binary read mode */
    FILE *fp = fopen(file_name, "rb");

    /* Check whether the file opened successfully */
    if (fp == NULL)
    {
        printf("File opening failed");
        return;
    }

    char tag[5];
    unsigned char size_bytes[4];
    int size;

    /* Skip the 10-byte ID3 header and move to the first frame */
    fseek(fp, 10, SEEK_SET);

    /* Read ID3 frames until no complete frame ID remains */
    while (fread(tag, 1, 4, fp) == 4)
    {
        /* Null-terminate the frame ID */
        tag[4] = '\0';

        /* Read the four-byte frame size */
        if (fread(size_bytes, 1, 4, fp) != 4)
            break;

        /* Convert the frame size from big-endian to an integer */
        size = (size_bytes[0] << 24) |
               (size_bytes[1] << 16) |
               (size_bytes[2] << 8) |
                size_bytes[3];

        /* Stop if the frame size is invalid */
        if (size <= 0)
            break;

        /* Skip the two-byte frame flags */
        if (fseek(fp, 2, SEEK_CUR) != 0)
            break;

        /* Check whether the frame data lies within the file */
        long data_pos = ftell(fp);
        fseek(fp, 0, SEEK_END);
        long file_end = ftell(fp);
        fseek(fp, data_pos, SEEK_SET);

        if (data_pos < 0 || file_end - data_pos < size)
            break;

        /* Initialize the destination pointer and buffer capacity */
        char *dest = NULL;
        size_t capacity = 0;

        /* Identify the metadata field using its frame ID */
        if (strcmp(tag, "TIT2") == 0)
        {
            dest = song->title;
            capacity = sizeof(song->title);
        }
        else if (strcmp(tag, "TPE1") == 0)
        {
            dest = song->artist;
            capacity = sizeof(song->artist);
        }
        else if (strcmp(tag, "TALB") == 0)
        {
            dest = song->album;
            capacity = sizeof(song->album);
        }
        else if (strcmp(tag, "TYER") == 0)
        {
            dest = song->year;
            capacity = sizeof(song->year);
        }
        else if (strcmp(tag, "TCON") == 0)
        {
            dest = song->genre;
            capacity = sizeof(song->genre);
        }
        else if (strcmp(tag, "COMM") == 0)
        {
            dest = song->comment;
            capacity = sizeof(song->comment);
        }

        if (dest != NULL)
        {
            /* Read and skip the text encoding byte */
            int encoding = fgetc(fp);
            if (encoding == EOF)
                break;

            /* Limit the text length to fit the destination buffer */
            size_t text_size = (size_t)size - 1;

            if (text_size >= capacity)
                text_size = capacity - 1;

            /* Read the metadata text into the selected field */
            if (fread(dest, 1, text_size, fp) != text_size)
                break;

            /* Add the null terminator to form a valid C string */
            dest[text_size] = '\0';

            /* Skip any remaining bytes in the current frame */
            if (fseek(fp, size - 1 - text_size, SEEK_CUR) != 0)
                break;
        }
        else
        {
            /* Skip the data of unrecognized metadata frames */
            if (fseek(fp, size, SEEK_CUR) != 0)
                break;
        }
    }

    /* Display the extracted metadata */
    printf("\n------------------------------------------------\n\n");
    printf("Title   - %s\n", song->title);
    printf("Album   - %s\n", song->album);
    printf("Artist  - %s\n", song->artist);
    printf("Year    - %s\n", song->year);
    printf("Genre   - %s\n", song->genre);
    printf("Comment - %s\n", song->comment);
    printf("\n------------------------------------------------\n");

    /* Close the MP3 file */
    fclose(fp);
}
