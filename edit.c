
/* This file contain update_text, edit_details, change_size,copy_remaining_img_data functions  */

#include "header.h"

/* This function update the text in file at particular location */
void update_text(FILE *fwr, char *text)
{
    // write the text into file at particular location
    fwrite(text,1,strlen(text),fwr);
    
}

/* This function check the edit type and then edit the required field in mp3 file */
int edit_details(FILE *fp, char *argv[], Song *song)
{
    FILE *fwr = fopen(argv[4],"r+");
    //fseek(fwr,ftell(fp),SEEK_SET);

    // check for the argument to edit which data of mp3 file
    //  -t => Title of song and set pointer indicator to that location
    if(strcmp(argv[2],"-t") == 0)
    {
	fseek(fwr,song->title_pos,SEEK_SET);
    }
    //  -y => Year of song and set pointer indicator to that location
    else if(strcmp(argv[2],"-y") == 0)
    {
	fseek(fwr,song->year_pos,SEEK_SET);
	if(isdigit(argv[3][0]) == 0 || strlen(argv[3]) > 4){
	    printf("ERROR : The year is not matched\n");
	    return FAILURE;
	}
	

    }
    //  -A => Album Name of song and set pointer indicator to that location
    else if(strcmp(argv[2],"-A") == 0)
    {
	fseek(fwr,song->album_pos,SEEK_SET);
    }
    //  -a => Artists of song and set pointer indicator to that location
    else if(strcmp(argv[2],"-a") == 0)
    {
	fseek(fwr,song->singer_pos,SEEK_SET);
    }
    //  -l => Lyricist of song and set pointer indicator to that location
    else if(strcmp(argv[2],"-l") == 0)
    {
	fseek(fwr,song->lang_pos,SEEK_SET);
    }
    //  -c => copy rights of song and set pointer indicator to that location
    else if(strcmp(argv[2],"-c") == 0)
    {
	fseek(fwr,song->copyright_pos,SEEK_SET);
    }
    //  -cast => Cast of song and set pointer indicator to that location
    else if(strcmp(argv[2],"-cast") == 0)
    {
	fseek(fwr,song->cast_pos,SEEK_SET);
    }
    //  -cmp => Composer of song and set pointer indicator to that location
    else if(strcmp(argv[2],"-cmp") == 0)
    {
	fseek(fwr,song->composer_pos,SEEK_SET);
    }
    // if not all above cases, it means we given wront input 
    else
    {
	printf("ERROR : \"%s\" is not a correct choice to edit\n",argv[2]);
	return FAILURE;
    }

    // take size of tha TAG data
    int size = get_size(fwr,4);

    // fp is indicator, points to next TAG starting location
    // ftell(fwr) = fwr location, 2 = 2 flag bytes want to skip, size = that data of TAG ,
    // so we want our pointer to jump to that location
    fseek(fp,ftell(fwr)+2+size,SEEK_SET);

    // fwr getting back 4 bytes to access size and update size (4 bytes)
    fseek(fwr,-4,SEEK_CUR);
    // size is length of given input string (ex: if string is 25 bytes/chars, that 25 stored in 4 bytes(integer))
    change_size(fwr,strlen(argv[3]));
    // skip the 2 bytes which is for flags, no operation with that 
    fseek(fwr,2,SEEK_CUR);
    // write the required data in that mp3 tag type 
    update_text(fwr,argv[3]);
    // after updating the required data, copy the remaining data into file
    copy_remaining_img_data(fp, fwr);

    return SUCCESS;

}

/* This file changes the 4 bytes of previous size value(integer) with the new value */
void change_size(FILE *fwr, int num)
{
    unsigned char buffer[4]; // String buffer of 4 bytes

    // Convert integer to string of 4 bytes    
    buffer[0] = (num >> 24) & 0xFF;
    buffer[1] = (num >> 16) & 0xFF;
    buffer[2] = (num >> 8) & 0xFF;
    buffer[3] = num & 0xFF;

    // write the size value into the file
    fwrite(buffer,1,4,fwr);

}

/* This file copy the remaining data of the mp3 file from next TAG to ending of editable TAG */ 
void copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    //here take any size buffer because we dont know how much remaining
    char buffer[10];
    int size;

    //until fptr_src is false, it will read from src F and write into dest F of size it read.
    while(!feof(fptr_src)){
       size=fread(buffer,1,sizeof(buffer),fptr_src);
       fwrite(buffer,1,size,fptr_dest);
    }
}
