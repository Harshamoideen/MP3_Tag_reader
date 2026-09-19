
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"


void edit_mp3(MP3Tag *song,char* argv[]){
    char file_name[200];
    strcpy(file_name,argv[1]);
   FILE *f1=fopen("duplicate.mp3","wb");
   FILE *f2=fopen(file_name,"rb");
   if(f1==NULL || f2==NULL)
   {
    printf("FILE open failed!\n");
   }
   //copying header to dulplicate file
   char header[10];
   fseek(f1,0,SEEK_SET);
   fseek(f2,0,SEEK_SET);
   fread(header,1,10,f2);
   fwrite(header,1,10,f1);

   char tag[5];
   char given_tag[5];
   
   int new_size;
   char new_data[200];

   char flag[3];
   char data[200];
//comparing cla commad 3(tag) to ask permission
char select;
   if(strcmp(argv[3],"-y")==0)
   {
    strcpy(given_tag,"TYER");
    printf("Do you want to change the year? (y/n)\n");
    scanf(" %c",&select);
    if(select=='y')
        printf("Enter new year: ");  
    else if(select=='n')
    {
        printf("\nYear remains unchanged.\n\n");
        return;
    }
    else
    {
        printf("\nInvalid selection.\nYear is not changed\n\n");  
        return;
    }
   }
   else if(strcmp(argv[3],"-t")==0)
   {
    strcpy(given_tag,"TIT2");
    printf("Do you want to change the title of the song? (y/n)\n");
    scanf(" %c",&select);
    if(select=='y')
        printf("Enter new title: ");
    else if(select=='n')
    {
        printf("\nYear remains unchanged.\n\n");
        return;
    }
    else
    {
        printf("\nInvalid selection\nTitle is not changed\n\n");
        return;
    }
   }
   else if(strcmp(argv[3],"-A")==0)
   {
    strcpy(given_tag,"TPE1");
    printf("Do you want to change the artist name? (y/n)\n");
    scanf(" %c",&select);
    if(select=='y')
        printf("Ente new year: ");
    else if(select=='n') 
    {
        printf("\nYear remains unchanged.\n\n");
        return;
    }
    else{
        printf("\nInvalid selection\nArtist is not changed\n\n");
        return;
    }
   }
   else if(strcmp(argv[3],"-a")==0)
   {
    strcpy(given_tag,"TALB");
    printf("Do you want to change the Album name? (y/n)\n");
    scanf(" %c",&select);
    if(select=='y')
        printf("Enter new album: ");
    else if(select=='n')
     {
        printf("\nYear remains unchanged.\n\n");
        return;
    } 
    else
    {
        printf("\nInvalid selection\nAlbum is not changed\n\n");
        return;
    }
   }
   else if(strcmp(argv[3],"-g")==0)
   {
    strcpy(given_tag,"TCON");
    printf("Do you want to change the Genre? (y/n)\n");
    scanf(" %c",&select);
    if(select=='y')
        printf("Enter new genre: ");
    else if(select=='n')
     {
        printf("\nYear remains unchanged.\n\n");
        return;
    }
    else
    {
        printf("\nInvalid selection\nGenre is not changed\n\n");
        return;
    }

   }
   else if(strcmp(argv[3],"-c")==0)
   {
    strcpy(given_tag,"COMM");
    printf("Do you want to change the Comment? (y/n)\n");
    scanf(" %c",&select);
    if(select=='y')
        printf("Enter new comment: ");
    else if(select=='n')
      {
        printf("\nYear remains unchanged.\n\n");
        return;
    }
    else
    {
        printf("\nInvalid selection\nComment is not changed\n\n");
        return;
    }
   }
   else{
    printf("\nEnter valid tag\n\n");
    return;
   }
   //reading new data 
   scanf(" %[^\n]",new_data);
   new_size=strlen(new_data)+1;
   
   
   unsigned char size_bytes[4];
   unsigned char new_size_bytes[4];
   int size;
   //little endian to big endian
   //reading new size
   new_size_bytes[0] = (new_size >> 24) & 0xFF;
   new_size_bytes[1] = (new_size >> 16) & 0xFF;
   new_size_bytes[2] = (new_size >> 8) & 0xFF;
   new_size_bytes[3] = new_size & 0xFF;
   //read tag
   while(fread(tag,1,4,f2)){
   tag[4]='\0';
   //read size of the tag
   fread(size_bytes, 1, 4, f2);

   size = (size_bytes[0] << 24) |
       (size_bytes[1] << 16) |
       (size_bytes[2] << 8)  |
       size_bytes[3];
   //reaf flag 2bytes and 1 encoding
   fread(flag,1,3,f2);
   //read data
   fread(data,1,size-1,f2);
   //comparing editing tag and updating new data and new size rest same then break to copy rest of the file 
   if(strcmp(tag,given_tag)==0){
    fwrite(tag,1,4,f1);
    fwrite(new_size_bytes, 1, 4, f1);
    fwrite(flag,1,3,f1);
   fwrite(new_data,1,new_size-1,f1);
   break;
  
   }
   else{
    //write everything to duplicate file
    fwrite(tag,1,4,f1);
    fwrite(size_bytes, 1, 4, f1);
    fwrite(flag,1,3,f1);
    fwrite(data,1,size-1,f1);
   }
}
//rest of the file
   int current=ftell(f2);
   fseek(f2,0,SEEK_END);
   int end=ftell(f2);
   fseek(f2,current,SEEK_SET);
   int rem=end-current;
   char ch;
   while(rem--){
   fread(&ch,1,1,f2);
   fwrite(&ch,1,1,f1);
   }
   //removing and renaming
   remove(file_name);
   rename("duplicate.mp3",file_name);
   fclose(f1);
   fclose(f2);
}
