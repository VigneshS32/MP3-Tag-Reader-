#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID3_HEADER_SIZE 10
#define FRAME_HEADER_SIZE 10

typedef enum _status
{
    true =0,
    false
}status;


status viewmp3(char *filename);
void read_frame(FILE *mp3_file, const char *frame_id, const char *label);
status editmp3(const char *filename,  char *content, const char *option);
status edit_frame(FILE *mp3_file, const char *frame_id, const char *label,char *content);
#endif