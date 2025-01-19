#include"main.h"


status viewmp3(char *filename)
{
    //check file extention is mp3?
    if (strstr(filename, ".mp3") == NULL) {
        fprintf(stderr, "Error: File must have .mp3 extension\n");
        return 1;
    }

    //open the mp3 file
    FILE *mp3_file = fopen(filename, "rb");
    if (!mp3_file) {
        perror("Error opening file");
        return 1;
    }

    char header[ID3_HEADER_SIZE];
    fread(header, 1, ID3_HEADER_SIZE, mp3_file);


     // Check for ID3 tag
    if (strncmp(header, "ID3", 3) != 0) {
        fprintf(stderr, "Error: No ID3 tag found\n");
        fclose(mp3_file);
        return 1;
    }
    
     // Check ID3 version (03 00 for ID3v2.3)
    if (header[3] != 3 || header[4] != 0) {
        fprintf(stderr, "Error: Unsupported ID3 version (%d.%d)\n", header[3], header[4]);
        fclose(mp3_file);
        return 1;
    }

      printf("------------------------SELECTED VIEW DETAILS----------------------\n");
      printf("-------------------------------------------------------------------\n");
    printf("  MP3 TAG READER AND EDITOR FOR ID3v2 \n");
    printf("---------------------------------------------------------------------\n");


      // Read and display frames
    read_frame(mp3_file, "TIT2", "TITLE");
    read_frame(mp3_file, "TPE1", "ARTIST");
    read_frame(mp3_file, "TALB", "ALBUM");
    read_frame(mp3_file, "TYER", "YEAR");
    read_frame(mp3_file, "TCON", "MUSIC");
    read_frame(mp3_file, "COMM", "COMMENT");

    printf("-----------------------------------------------------------------------\n");
    printf("\n-------------------------DETAILS DISPLAYED SUCCESSFULLY---------------\n");

    fclose(mp3_file);
    return 0;
}

// Function to read and display a specific ID3v2 frame
 void read_frame(FILE *mp3_file, const char *frame_id, const char *label) {
    char frame_id_buf[5] = {0};
    unsigned char frame_size_bytes[4];
    unsigned int frame_size;

    fseek(mp3_file, ID3_HEADER_SIZE, SEEK_SET); // Start after the header

    while (fread(frame_id_buf, 1, 4, mp3_file) == 4) {
        fread(frame_size_bytes, 1, 4, mp3_file);

        frame_size = (frame_size_bytes[0] << 21) |
                     (frame_size_bytes[1] << 14) |
                     (frame_size_bytes[2] << 7) |
                     frame_size_bytes[3];

        if (frame_size == 0) break; // Stop if the frame size is 0

        fseek(mp3_file, 2, SEEK_CUR); // Skip flags

        if (strcmp(frame_id_buf, frame_id) == 0) {
            char *frame_content = (char *)malloc(frame_size + 1);
            if (!frame_content) {
                fprintf(stderr, "Memory allocation failed\n");
                return ;
            }
            fread(frame_content, 1, frame_size, mp3_file);
            frame_content[frame_size] = '\0';
            printf("%-10s : %s\n", label, frame_content);
            free(frame_content);
            return;
        }

        fseek(mp3_file, frame_size, SEEK_CUR); // Skip the current frame
    }

    printf("%-10s : Not Found\n", label);
}
