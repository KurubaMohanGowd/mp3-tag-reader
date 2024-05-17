/*

NAME  : Mohan

DATE  : 16 May, 2024

TITLE : MP3 Tag reader


This file contains main function, edit_argument, show_invalid_arguments, validate_file functions 
 
 */

#include "header.h"

/* This main function compare the command line argument and call the validate function */ 
int main(int argc, char *argv[])
{
    Song song;
    // arg count = 2 => [ ./a.out --help ]
    if(argc == 2)
    {
	// compare argument and print help function to understand user
	if(strcmp(argv[1],"--help") == 0)
	{
	    help();
	}
	else
	{
	    show_invalid_arguments();
	}
    }
    // arguments  [./a.out  -v  mp3_file ]
    else if(argc == 3)
    {
	if(strcmp(argv[1],"-v") == 0)
	{
	    // validate the arguments, if invalid print error 
	    if(validate_file(argv[2]) == SUCCESS)
	    {
		// read the details of the file after validating args
		if(get_details(fopen(argv[2],"r"),&song) == SUCCESS)
		{
		    // display song details
		    song_display(&song);
		    return SUCCESS;
		}
	    }
	    else
	    {
		printf("ERROR : Invalid File \n");
	    }
	}
	// if arg2 is not -v means, incorrect type arguments, so show correct arguments to user
	else
	{
	    show_invalid_arguments();
	}
    }
    else if(argc == 5)
    {
	// check for the arguments to edit the data or not
	edit_argument(argv,song);
    }
    else
    {
	// it display the correct format of input
	show_invalid_arguments();
    }

    return SUCCESS;
}

/* if argument count = 5, chance to edit the mp3 data, so this function validate and call functions for edit the data */
void edit_argument(char *argv[], Song song)
{

    FILE *fptr;
    // make sure arg count = 5 and user needs to edit (-e) for arg2
    if(strcmp(argv[1],"-e") == 0)
    {
	if(validate_file(argv[4]) == SUCCESS)
	{
	    // open the file in read mode
	    fptr = fopen(argv[4],"r");
	    // store details in one structure
	    if(get_details(fptr,&song) == SUCCESS){
		// edit the details based on users choice
		if(edit_details(fptr,argv,&song) == SUCCESS)
		{
		    printf("**** Successful : Editing completed ****\n");
		}
	    }
	}
    }
}


/* this function display the argument format which makes user to understand better */
void show_invalid_arguments(void )
{
    printf("\n");
    // printing the VALID ARGUMENTS format to understand by the user
    printf("ERROR : INVALID ARGUMENTS\n");
    printf("USAGE :\nTo VIEW mp3 file please pass like : ./a.out -v mp3filename\n");
    printf("To EDIT mp3 file please pass like : ./a.out -e -t/-a/-A/-l/-y/-c/-cast/-cmp changing_text mp3filename\n");
    printf("To get help pass like             : ./a.out --help\n");
    printf("\n");

}

/* this function validate the file i.e, exists or not and expected file or not */
int validate_file(char *filename)
{
    char *ext;
    ext = strchr(filename,'.');
    // check the file is valid or not
    if(ext != NULL && strcmp(".mp3",ext) == 0)
    {
	FILE *file_ptr = fopen(filename,"r");
	if(file_ptr != NULL)
	{
	    char str[3];
	    fread(str,1,3,file_ptr);
	    //printf("ptr value : %s\n",str);
	    // check for first 3 bytes for "ID3" or not
	    if(strcmp(str,"ID3") == 0)
	    {
		// check for version in next 2 bytes
		fread(str,1,2,file_ptr);
		//here str stores 2 bytes i.e, 4th, 5th from .mp3 file
		//it must be | 03 00 | values for version 3
		if(str[0] == 0x03 && str[1] == 0x00)
		{
		    //printf("version %x.%x\n",str[0],str[1]);
		    fclose(file_ptr);
		    return SUCCESS;
		}
		printf("ERROR : version not matched. It is not ID3.3.0\n");
		return FAILURE;

	    }
	    printf("ERROR : The file is not ID3\n");
	    return FAILURE;
	}
	printf("ERROR : The given mp3 file is not present\n");
	return FAILURE;
    }
    else
    {
	printf("ERROR : This is not mp3 file\n");
	return FAILURE;
    }
}
