#include"main.h"

status editmp3(const char *filename,  char *content, const char *option)
{
    printf("----------------------SELECTED EDIT OPTION-------------------------------\n");
     //check file extention is mp3?
    if (strstr(filename, ".mp3") == NULL) {
        fprintf(stderr, "Error: File must have .mp3 extension\n");
        return 1;
    }

    //open the mp3 file
    FILE *mp3_file = fopen(filename, "r+");
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
   
    // check for option
    if(strcmp(option,"-t")==0)
    {
        printf("----------------CHANGE THE TITLE---------------------\n\n");
        if(edit_frame(mp3_file, "TIT2", "TITLE",content)==0)
        {
        printf("\n--------------CHANGE SUCCESS---------------------\n");
       }
    }
    else if(strcmp(option,"-a")==0)
    {
       printf("----------------CHANGE THE ARTIST---------------------\n\n");
       if(edit_frame(mp3_file, "TPE1", "ARTIST",content)==0)
       {
        printf("\n--------------CHANGE SUCCESS---------------------\n");
       }

    }
    else if(strcmp(option,"-A")==0)
    {
      printf("----------------CHANGE THE ALBUM---------------------\n\n");
      if(edit_frame(mp3_file, "TALB", "ALBUM",content)==0)
      {
        printf("\n--------------CHANGE SUCCESS---------------------\n");
      }

    }
    else if(strcmp(option,"-y")==0)
    {
      printf("----------------CHANGE THE YEAR---------------------\n\n");
      if(edit_frame(mp3_file, "TYER", "YEAR",content)==0)
      {
        printf("\n--------------CHANGE SUCCESS---------------------\n");
      }
    }
    else if(strcmp(option,"-m")==0)
    {
    printf("----------------CHANGE THE MUSIC---------------------\n\n");
       if(edit_frame(mp3_file, "TCON", "MUSIC",content)==0)
       {
        printf("\n--------------CHANGE SUCCESS---------------------\n");
       }
    }
    else if(strcmp(option,"-c")==0)
    {
    printf("----------------CHANGE THE COMMENT---------------------\n\n");
       if(edit_frame(mp3_file, "COMM", "COMMENT",content)==0)
       {
        printf("\n--------------CHANGE SUCCESS---------------------\n");
       }
    }
    else
    {
        return 1;
    }

}

// Function to edit and display a specific ID3v2 frame
 status edit_frame(FILE *mp3_file, const char *frame_id, const char *label,char *content) {
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
            // Calculate content size
            unsigned int content_size = strlen(content);

            // Ensure new content fits within the original frame size
            if (content_size > frame_size) {
                fprintf(stderr, "New content is too large for the frame\n");
                return false;
            }
             
            
            // Update the frame content
            fwrite(content, 1,content_size, mp3_file);

            // Fill remaining bytes with null if content is smaller than frame size
            if (content_size < frame_size) {
                char *padding = (char *)calloc(frame_size - content_size, 1); // Allocate null padding
                fwrite(padding, 1, frame_size - content_size, mp3_file);
                free(padding);
            }

            printf("%-10s : %s\n", label, content);
            
            return true;
        }

        fseek(mp3_file, frame_size, SEEK_CUR); // Skip the current frame
    }

    printf("%-10s : Not Found\n", label);
}