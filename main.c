#include <stdio.h>
#include <string.h>
#include "mp3.h"

char file_name_str[10];
int main(int argc,char *argv[])
{

	MP3Tag song = {0};
    if( argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        help_mp3();
        return 0;
    }
	if(argc<3)
	{
		printf("\nInsufficient arguments!!\n\n");
        help_mp3();
		return 0;

	}
    if(strcmp(argv[2],"-v") == 0)
		{
			if(argc != 3){
				printf("\nInvalid no.of arguments!!\n\n");
				return 1;
			}
			view_mp3(&song,argv[1]); 
		}
		else if(strcmp(argv[2],"-e") == 0)
		{
			if(argc != 4){
				printf("\nInsufficient arguments!!\n\n");
                help_mp3();
				return 1;
			}
			edit_mp3(&song, argv);
		}
	
		else
        {
			printf("\nUnknown option : %s\n",argv[2]);
			printf("enter ./a.out -h for help guide\n\n");
            return 1;
		}
	return 0;
}
