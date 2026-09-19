#ifndef MP3_H
#define MP3_H

typedef struct
{
    char title[100];
    char artist[100];
    char album[100];
    char year[10];
    char genre[50];
    char comment[200];
} MP3Tag;
void view_mp3(MP3Tag *song,char *file_name);
void edit_mp3(MP3Tag *song, char* argv[]);
void help_mp3(void);

#endif