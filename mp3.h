#ifndef MP3_H
#define MP3_H

/*
 * Structure: MP3Tag
 * Description: Stores the metadata fields of an MP3 file.
 */
typedef struct
{
    char title[100];    
    char artist[100];   
    char album[100];    
    char year[10];      
    char genre[50];    
    char comment[200];  
} MP3Tag;

/*Reads and displays metadata from an MP3 file.*/
void view_mp3(MP3Tag *song, char *file_name);

/*Modifies a selected metadata tag in an MP3 file.*/
void edit_mp3(MP3Tag *song, char *argv[]);

/*Displays usage instructions and available options.*/
void help_mp3(void);

#endif