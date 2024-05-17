#ifndef MP3_H
#define MP3_H

#define SUCCESS 1
#define FAILURE 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct song
{
    char *album;
    int title_pos;
    int singer_pos;
    int album_pos;
    int cast_pos;
    int year_pos;
    int lang_pos;
    int composer_pos;
    int copyright_pos;

    char *singers;
    char *frame_id;
    int version;
    char *title;
    char *cast;
    unsigned int year;
    char *content;
    char *lang;
    char *comment;
    char *copyright;
    char *composer;
    char *tracknum;
    char *url;
}Song;

void show_invalid_arguments(void );

void help(void);

int validate_file(char *filename);

void display_success(void);

void change_size(FILE *fp, int size);

int get_details(FILE *fptr, Song *s);

int get_size(FILE *fptr, int size);

void get_text( int size, FILE *fptr, char *text);

void song_display(Song *s);

int edit_details(FILE *f, char* argv[], Song *s);

void change_size(FILE *FP, int size);

void copy_remaining_img_data(FILE *FP, FILE *FD);

void edit_argument(char *argv[],Song song);

#endif
