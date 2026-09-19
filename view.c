#include <stdio.h>
#include <string.h>
#include "mp3.h"


void view_mp3(MP3Tag *song,char *file_name){
FILE *fp=fopen(file_name,"rb");
if (fp==NULL){
    printf("File opening failed");
    return;
}
char tag[5];
unsigned char size_bytes[4];
int size;

fseek(fp,10,SEEK_SET);

while(fread(tag,1,4,fp)==4){
tag[4]='\0';
fread(size_bytes, 1, 4, fp);

size = (size_bytes[0] << 24) |
       (size_bytes[1] << 16) |
       (size_bytes[2] << 8)  |
       size_bytes[3];
fseek(fp,3,SEEK_CUR);
if(strcmp(tag,"TIT2")==0){
fread(song->title,1,size-1,fp);
song->title[size-1]='\0';}

else if(strcmp(tag,"TPE1")==0){
fread(song->artist,1,size-1,fp);
song->artist[size-1]='\0';}

else if(strcmp(tag,"TALB")==0){
fread(song->album,1,size-1,fp);
song->album[size-1]='\0';}

else if(strcmp(tag,"TYER")==0){
fread(song->year,1,size-1,fp);
song->year[size-1]='\0';}

else if(strcmp(tag,"TCON")==0){
fread(song->genre,1,size-1,fp);
song->genre[size-1]='\0';}

else if(strcmp(tag,"COMM")==0){
fread(song->comment,1,size-1,fp);
song->comment[size-1]='\0';}

else
fseek(fp,size,SEEK_CUR);
}
printf("\n------------------------------------------------\n\n");
printf("Title - %s\n",song->title);
printf("Album - %s\n",song->album);
printf("Artist - %s\n",song->artist);
printf("Year - %s\n",song->year);
printf("Genre - %s\n",song->genre);
printf("Comment - %s\n",song->comment);
printf("\n-----------------------------------------------\n");
fclose(fp);
}