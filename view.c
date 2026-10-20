#include <stdio.h>
#include <string.h>
#include "mp3.h"


void view_mp3(MP3Tag *song,char *file_name)
{
	FILE *fp=fopen(file_name,"rb");
	if (fp==NULL)
	{
		printf("File opening failed");
		return;
	}
	char tag[5];
	unsigned char size_bytes[4];
	int size;

	fseek(fp,10,SEEK_SET);

	while(fread(tag,1,4,fp) == 4)
	{
		tag[4]='\0';
		if(fread(size_bytes, 1, 4, fp) != 4)
        break;

		size = (size_bytes[0] << 24) |
			(size_bytes[1] << 16) |
			(size_bytes[2] << 8)  |
			size_bytes[3];

        if(size <= 0)
        break;
		if (fseek(fp,2,SEEK_CUR) != 0)
        break;

        // Check that the frame data is within the file
        long data_pos = ftell(fp);
        fseek(fp, 0, SEEK_END);
        long file_end = ftell(fp);
        fseek(fp, data_pos, SEEK_SET);
        if (data_pos < 0 || file_end - data_pos < size)
            break;
        char *dest = NULL;
        size_t capacity = 0;

		if(strcmp(tag,"TIT2") == 0)
		{
			dest = song->title;
            capacity = sizeof(song->title);
		}

		else if(strcmp(tag,"TPE1") == 0)
		{
			dest = song->artist;
            capacity = sizeof(song->artist);
		}

		else if(strcmp(tag,"TALB")==0)
		{
			dest = song->album;
            capacity = sizeof(song->album);
		}

		else if(strcmp(tag,"TYER")==0)
		{
			dest = song->year;
            capacity = sizeof(song->year);
		}

		else if(strcmp(tag,"TCON")==0)
		{
			dest = song->genre;
            capacity = sizeof(song->genre);
		}

		else if(strcmp(tag,"COMM")==0)
		{
			dest = song->comment;
            capacity = sizeof(song->comment);
		}

         if (dest != NULL)
        {
            // Skip the encoding byte
            int encoding = fgetc(fp);
            if (encoding == EOF)
                break;
            size_t text_size = (size_t)size - 1;
            if (text_size >= capacity)
                text_size = capacity - 1;
            if (fread(dest, 1, text_size, fp) != text_size)
                break;
            dest[text_size] = '\0';
            // Skip any remaining bytes in this frame
            if (fseek(fp, size - 1 - text_size, SEEK_CUR) != 0)
                break;
        }
		else
        {
			if(fseek(fp,size,SEEK_CUR) != 0)
            break;
        }
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
