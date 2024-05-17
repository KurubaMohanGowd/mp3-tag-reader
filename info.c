
/* This file contain help function which display the input argument format as help for the user to understand */

#include "header.h"

/* This function display the input argument format to understand user */
void help(void)
{
    // displaying VALID format to understand by the user
    printf("\n");
    for(int i = 0; i <= 30; i++)
    {
        printf("--");
        if(i == 12){
            printf(" HELP MENU ");
        }
    }
    printf("\n\n");
    printf("1. ./a.out -v  -> to view mp3 file contents\n");
    printf("2. ./a.out -e  -> to edit mp3 file contents\n");
    printf("\t2.1. -t  -> to edit song title\n");
    printf("\t2.2. -a  -> to edit song artist name\n");
    printf("\t2.3. -A  -> to edit song album name\n");
    printf("\t2.4. -y  -> to edit song year\n");
    printf("\t2.5. -l  -> to edit song Language\n");
    printf("\t2.6. -c  -> to edit song copy rights\n");
    printf("\t2.7. -cast  -> to edit song Album Cast\n");
    printf("\t2.8. -cmp  -> to edit song Composer\n");

    for(int i = 0; i <= 36; i++)
    {
        printf("--");
    }
    printf("\n\n");
}
