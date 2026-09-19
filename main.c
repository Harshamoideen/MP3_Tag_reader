#include <stdio.h>
#include <string.h>
#include "mp3.h"

char file_name_str[10];
int main(int argc,char *argv[]){

    MP3Tag song;
    if(argc ==2 && strcmp(argv[1],"-h")==0){
     help_mp3();
    }
    else{
    if(strcmp(argv[2],"-v") == 0){
     view_mp3(&song,argv[1]); 
    }
    else if(strcmp(argv[2],"-e")==0){
     edit_mp3(&song, argv);
    }
    else if(strcmp(argv[2],"-h")==0){
     help_mp3();
    }
    else{
        printf("\nUnknown option : %s\n",argv[2]);
        printf("enter ./a.out -h for help guide\n\n");
    }
}
    return 0;
}