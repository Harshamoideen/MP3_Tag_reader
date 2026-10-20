
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"


void edit_mp3(MP3Tag *song,char* argv[])
{
	char file_name[200];
	strcpy(file_name , argv[1]);
	FILE *f2 = fopen(file_name,"rb");
	if(f2 == NULL) 
	{
		printf("File open failed!\n");
		return;
	}
	FILE *f1 = fopen("duplicate.mp3","wb");
	if(f1 == NULL)
	{
		printf("File open failed!\n");
		fclose(f2);
		return;
	}
	//copying header to dulplicate file
	char header[10];
	fseek(f1 ,0 ,SEEK_SET);
	fseek(f2 ,0 ,SEEK_SET);
	if (fread(header, 1, 10, f2) != 10 ||
			memcmp(header, "ID3", 3) != 0)
	{
		printf("Invalid ID3 header!\n");
		fclose(f1);
		fclose(f2);
		remove("duplicate.mp3");
		return;
	}
	unsigned int old_tag_size =  ((unsigned int)(header[6] & 0x7F) << 21) |
		((unsigned int)(header[7] & 0x7F) << 14) |
		((unsigned int)(header[8] & 0x7F) << 7) |
		(header[9] & 0x7F);
	fwrite(header, 1, 10, f1); 
	int size_difference = 0;
	int found = 0;

	char tag[5];
	char given_tag[5];

	int new_size;
	char new_data[4096];

	char flag[2];
	char data[4096];
	//comparing cla commad 3(tag) to ask permission
	char select;
	if(strcmp(argv[3],"-y") == 0)
	{
		strcpy(given_tag,"TYER");
		printf("Do you want to change the year? (y/n)\n");
		scanf(" %c",&select);
		if(select == 'y')
			printf("Enter new year: ");  
		else if(select == 'n')
		{
			printf("\nYear remains unchanged.\n\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		}
		else
		{
			printf("\nInvalid selection.\nYear is not changed\n\n");  
			return;
		}
	}
	else if(strcmp(argv[3],"-t") == 0)
	{
		strcpy(given_tag,"TIT2");
		printf("Do you want to change the title of the song? (y/n)\n");
		scanf(" %c",&select);
		if(select == 'y')
			printf("Enter new title: ");
		else if(select == 'n')
		{
			printf("\nTitle remains unchanged.\n\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		}
		else
		{
			printf("\nInvalid selection\nTitle is not changed\n\n");
			return;
		}
	}
	else if(strcmp(argv[3],"-A") == 0)
	{
		strcpy(given_tag,"TPE1");
		printf("Do you want to change the artist name? (y/n)\n");
		scanf(" %c",&select);
		if(select == 'y')
			printf("Ente new artist: ");
		else if(select == 'n') 
		{
			printf("\nArtist remains unchanged.\n\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		}
		else{
			printf("\nInvalid selection\nArtist is not changed\n\n");
			return;
		}
	}
	else if(strcmp(argv[3],"-a") == 0)
	{
		strcpy(given_tag,"TALB");
		printf("Do you want to change the Album name? (y/n)\n");
		scanf(" %c",&select);
		if(select == 'y')
			printf("Enter new album: ");
		else if(select == 'n')
		{
			printf("\nAlbum remains unchanged.\n\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		} 
		else
		{
			printf("\nInvalid selection\nAlbum is not changed\n\n");
			return;
		}
	}
	else if(strcmp(argv[3],"-g") == 0)
	{
		strcpy(given_tag,"TCON");
		printf("Do you want to change the Genre? (y/n)\n");
		scanf(" %c",&select);
		if(select == 'y')
			printf("Enter new genre: ");
		else if(select == 'n')
		{
			printf("\nGenre remains unchanged.\n\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		}
		else
		{
			printf("\nInvalid selection\nGenre is not changed\n\n");
			return;
		}

	}
	else if(strcmp(argv[3],"-c") == 0)
	{
		strcpy(given_tag,"COMM");
		printf("Do you want to change the Comment? (y/n)\n");
		scanf(" %c",&select);
		if(select == 'y')
			printf("Enter new comment: ");
		else if(select == 'n')
		{
			printf("\nComment remains unchanged.\n\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
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
	if (scanf(" %4095[^\n]", new_data) != 1)
	{
		printf("Invalid input!\n");
		fclose(f1);
		fclose(f2);
		remove("duplicate.mp3");
		return;
	}
	new_size = strlen(new_data) + 1;


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
	while(fread(tag,1,4,f2) == 4)
	{
		tag[4] = '\0';
		//read size of the tag
		if(fread(size_bytes, 1, 4, f2) != 4) 
		{
			printf("Frame size read failed!\n");

			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		}

		unsigned int size =
			((unsigned int)size_bytes[0] << 24) |
			((unsigned int)size_bytes[1] << 16) |
			((unsigned int)size_bytes[2] << 8) |
			(unsigned int)size_bytes[3];
		//reaf flag 2bytes and 1 encoding
		if(fread(flag,1,2,f2) != 2)
		{
			printf("Frame read failed!\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		}

		if (size < 1)
		{
			printf("Invalid frame size!\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		}

		if (strcmp(tag, given_tag) != 0)
		{
			// Copy frame header
			if (fwrite(tag, 1, 4, f1) != 4 ||
					fwrite(size_bytes, 1, 4, f1) != 4 ||
					fwrite(flag, 1, 2, f1) != 2)
			{
				fclose(f1);
				fclose(f2);
				remove("duplicate.mp3");
				return;
			}

			// Copy frame data in chunks
			unsigned char buffer[4096];
			unsigned int remaining = size;

			while (remaining > 0)
			{
				size_t chunk = remaining > sizeof(buffer)
					? sizeof(buffer) : remaining;

				if (fread(buffer, 1, chunk, f2) != chunk ||
						fwrite(buffer, 1, chunk, f1) != chunk)
				{
					printf("Frame copy failed!\n");
					fclose(f1);
					fclose(f2);
					remove("duplicate.mp3");
					return;
				}

				remaining -= chunk;
			}

			continue;
		}

		// For the requested tag, read its data into data[].
		// Your existing replacement code can follow here.
		if (size > sizeof(data))
		{
			printf("Requested frame is too large to edit safely!\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		}

		if (fread(data, 1, size, f2) != size)
		{
			printf("Frame data read failed!\n");
			fclose(f1);
			fclose(f2);
			remove("duplicate.mp3");
			return;
		}
		//comparing editing tag and updating new data and new size rest same then break to copy rest of the file 
		if(strcmp(tag,given_tag) == 0)
		{
			size_difference = new_size - size;
			if(fwrite(tag,1,4,f1) != 4 ||
					fwrite(new_size_bytes, 1, 4, f1) != 4 ||
					fwrite(flag,1,2,f1) != 2)
			{
				fclose(f1);
				fclose(f2);
				remove("duplicate.mp3");
				return;

			}
			char encoding = 0;
			if(fwrite(&encoding, 1, 1, f1) != 1 ||
					fwrite(new_data, 1, strlen(new_data), f1) != strlen(new_data))
			{
				fclose(f1);
				fclose(f2);
				remove("duplicate.mp3");
				return;
			}
			found = 1;
			break;

		}

	}
	//rest of the file
	if (!found)
	{
		printf("Requested tag not found!\n");
		fclose(f1);
		fclose(f2);
		remove("duplicate.mp3");
		return;
	}
	int current=ftell(f2);
	fseek(f2,0,SEEK_END);
	int end = ftell(f2);
	fseek(f2,current,SEEK_SET);
	int rem = end - current;
	char ch;
	while(rem--){
		fread(&ch,1,1,f2);
		fwrite(&ch,1,1,f1);
	}
	unsigned int total_size = old_tag_size + size_difference;

	header[6] = (total_size >> 21) & 0x7F;
	header[7] = (total_size >> 14) & 0x7F;
	header[8] = (total_size >> 7) & 0x7F;
	header[9] = total_size & 0x7F;

	if (total_size > 0x0FFFFFFF)
	{
		printf("ID3 tag is too large!\n");
		fclose(f1);
		fclose(f2);
		remove("duplicate.mp3");
		return;
	}

	fseek(f1, 0, SEEK_SET);

	if (fwrite(header, 1, 10, f1) != 10)
	{
		fclose(f1);
		fclose(f2);
		remove("duplicate.mp3");
		return;
	}
	//removing and renaming
	if (fclose(f1) != 0)
	{
		fclose(f2);
		remove("duplicate.mp3");
		printf("Failed to close output file!\n");
		return;
	}

	fclose(f2);

	if (rename("duplicate.mp3", file_name) != 0)
	{
		perror("rename failed");
		return;
	}
}
