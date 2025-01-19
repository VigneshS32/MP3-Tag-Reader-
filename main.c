/*
 NAME         :  VIGNESH S
 REG ID       :  24017f_025
 PROJECT NAME :  MP3 TAG READER AND EDITER
 DATE         :  1-12-24
 BRIEF        :  MP3  tag reader and editer in software application which used to view and edit the mp3 tag meta data.
 */

#include "main.h"

int main(int argc, char *argv[]) 
{

    if(argc == 2)
    {
        if(strcmp(argv[1],"--help")== 0)
        {
            printf("------------------------------------HELP MENU------------------------------------\n"
       "1. -v  -> View MP3 file contents\n"
       "2. -e  -> Edit MP3 file contents\n"
       "   2.1 -t  -> Edit song title\n"
       "   2.2 -a  -> Edit artist name\n"
       "   2.3 -A  -> Edit album name\n"
       "   2.4 -y  -> Edit year\n"
       "   2.5 -m  -> Edit content\n"
       "   2.6 -c  -> Edit comment\n");
        return 0;

        }
    }


    if(strcmp(argv[1],"-v")==0)  
    {
        if(argc != 3)
        {
            printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
            printf("USAGE :\n");
            printf("To view please pass like:  ./a.out -v mp3filename\n");
            printf("To edit please pass like:  ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
            printf("To get help pass like : ./a.out --help\n");
            return 1;
        }
        else
        {
            char *filename = argv[2];
            if(viewmp3(filename)==false)
            {
                printf("view is unsuccessfull");
            }
        }
       
    }

    if (strcmp(argv[1],"-e")==0)  
    {
        if(argc != 5)
        {
            printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
            printf("USAGE :\n");
            printf("To view please pass like:  ./a.out -v mp3filename\n");
            printf("To edit please pass like:  ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
            printf("To get help pass like : ./a.out --help\n");
            return 1;
        }
        else
        {
         
            char *filename = argv[4];
            char *content = argv[3];
            char *option = argv[2];
            printf("----------------------------------SELECTED EDIT DETAILS--------------------------\n\n");
            if(editmp3(filename,content,option)==false)
            {
                printf("Edit is unsuccessfull");
            }
        }
       
    }

}