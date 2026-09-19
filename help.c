#include <stdio.h>
#include "mp3.h"

void help_mp3(){
    printf("\n-----------------------------------------------------\n");
    printf("%30s","MP3 tag\n");
    printf("-----------------------------------------------------\n");
    printf("usage:\n");
    printf("   ./a.out file.mp3 -v");
    printf("%26s","view tags\n");
     printf("   ./a.out <file.mp3> -e <tag> ");
    printf("%20s","edit one tag\n");
     printf("   ./a.out -h");
    printf("%30s","help\n");
    printf("\nTag options for -e:\n");
    printf("   -t title\n");
    printf("   -A artist\n");
    printf("   -a album\n");
    printf("   -y year\n");
    printf("   -g genre\n");
    printf("   -c comment\n");
    printf("\n----------------------------------------------------\n");
}