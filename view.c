/* This file contain song_display, get_details, get_size, get_text functions */

#include "header.h"

/* This function display the details of the song */
void song_display(Song *song)
{
    //printf("=======================> SONG DETAILS <====================== \n");
    printf("-------------------------------------------------------------\n");
    printf("%s %d.0 \n",song->frame_id,song->version);
    printf("-------------------------------------------------------------\n");
    printf("%-15s : %-20s\n","Title",song->title);
    printf("%-15s : %-40s\n%-15s : %-7d\n","Album",song->album,"Year",song->year);
    printf("%-15s : %s\n","Artist",song->singers);
    printf("%-15s : %s\n","Cast",song->cast);
    printf("%-15s : %s\n","Track",song->tracknum);
    printf("%-15s : %-40s \n%-15s : %-10s\n","Composer",song->composer,"Language",song->lang);
    printf("%-15s : %s\n","Copy Rights",song->copyright);
    printf("-------------------------------------------------------------\n\n");
}

/* This function fetch the details of every TAG required and stores that location in a structure */
int get_details(FILE *file_ptr, Song *song)
{
    int i;
    char str[4];
    // for the ID3 
    fread(str,1,3,file_ptr);
    // stores that into structure
    song->frame_id = malloc(strlen(str));
    strcpy(song->frame_id,str);
    // for the version
    fread(str,1,2,file_ptr);
    song->version = str[0];

    // take the pointer to the header block starting
    fseek(file_ptr, 10, SEEK_SET);
    for(i = 0; i < 20; i++)
    {
        // here 4 bytes contain the TAG , ex: TALB for album of song
        fread(str,1,4,file_ptr);
	int pos = ftell(file_ptr);

	// getting size of the TAG data ( 4 bytes)
        int size = get_size(file_ptr,4);

	// skip 2 Bytes because, no use with FLAG values(2bytes)
        fseek(file_ptr,2L,SEEK_CUR);
        char content[size];

	// getting that data of TAG 
        get_text(size, file_ptr, content);

	// comparing every TAG and adding that file position into respective structure members
        if(strcmp("TALB",str) == 0)
        {
            song->album = malloc(strlen(content));
            strcpy(song->album,content);
	    song->album_pos = pos;
        }
        else if(strcmp("TIT2",str) == 0)
        {
            song->title = malloc(strlen(content));
            strcpy(song->title,content);
	    song->title_pos = pos;
        }
        else if(strcmp("TPE1",str) == 0)
        {
            song->singers = malloc(strlen(content));
            strcpy(song->singers,content);
	    song->singer_pos = pos;
        }
        else if(strcmp("TPE2",str) == 0)
        {
            song->cast = malloc(strlen(content));
            strcpy(song->cast,content);
	    song->cast_pos = pos;
        }
        else if(strcmp("COMM",str) == 0)
        {
            song->comment = malloc(strlen(content));
            strcpy(song->comment,content);
        }
        else if(strcmp("TCOM",str) == 0)
        {
            song->composer = malloc(strlen(content));
            strcpy(song->composer,content);
	    song->composer_pos = pos;
        }
        else if(strcmp("TCOP",str) == 0)
        {
            song->copyright = malloc(strlen(content));
            strcpy(song->copyright,content);
	    song->copyright_pos = pos;
        }
        else if(strcmp("TCON",str) == 0)
        {
            song->lang = malloc(strlen(content));
            strcpy(song->lang,content);
	    song->lang_pos = pos;
        }
        else if(strcmp("TRCK",str) == 0)
        {
            song->tracknum = malloc(strlen(content));
            strcpy(song->tracknum,content);
        }
        else if(strcmp("TYER",str) == 0)
        {
            song->year = atoi(content);
	    song->year_pos = pos;
        }
        else if(strcmp("WXXX",str) == 0)
        {
            song->url = malloc(strlen(content));
            strcpy(song->url,content);
        }
    }
    return SUCCESS;
}

/* This function fetch the size(integer value of 4 bytes), it contains TAG data size */
int get_size(FILE *fptr, int size)
{
    int val = 0;
    char str[5];
    
    // the size is 4 
    for( int i = 1; i <= size; i++)
    {
	fread(str,1,1,fptr);

	unsigned char x;
	x = str[0];
	val += (x<<(8*(4-i)));
    }
    // value is decimal form of 4 bytes value from file which is the size of that tag member data
    return val;
}

/* This function extract data from the file related to particular TAG */
void get_text(int size, FILE *fptr, char *text)
{
    char str[size+1];
    int i,j=0;
    for(i = 0; i < size; i++)
    {
	fread(str,1,1,fptr);
	// here i am taking only supported characters from that TAG data
	if(str[0] >=32 && str[0] <=126){
	    //printf("%c",str[0]);
	    text[j] = str[0];
	    j++;
	}

    }
    text[j] = '\0';

}



