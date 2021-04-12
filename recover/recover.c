#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Validate input
    if (argc != 2)
    {
        printf("Usage: recover forensic_image\n");
        return 1;
    }
    char *input = argv[1];
    FILE *f_img = fopen(input, "r");
    // Validate file pointer
    if (f_img == NULL)
    {
        printf("image could not be read\n");
        return 1;
    }
    // create 512 byte buffer block
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    // initialise filename string
    char *filename = malloc(8);
    // initialise counter
    int filenum = 0;
    // currently writing file boolean
    int cwf = 0;
    while (!feof(f_img))
    {
        int finished = fread(buffer, sizeof(BYTE), 512, f_img);
        // check if paritial block, if so break loop
        if (finished == 0)
        {
            break;
        }
        // check if block contains jpeg header

        if ((buffer[0] == 0xff)
            && (buffer[1] == 0xd8)
            && (buffer[2] == 0xff)
            && ((buffer[3] & 0xf0) == 0xe0))
        {
            // if there is no file open i.e. first file found.
            if (cwf == 0)
            {
                cwf = 1;
                sprintf(filename, "%03i.jpg", filenum);
                FILE *f = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, f);
                fclose(f);
            }
            // check if there is a current file being worked on, if so increment the counter and move onto the next file.
            else if (cwf == 1)
            {
                filenum++;
                sprintf(filename, "%03i.jpg", filenum);
                FILE *f = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, f);
                fclose(f);
            }
        }
        // keep appending the current file. Could have just been an else, the valididation doesnt do anything.
        else if (cwf == 1)
        {
            FILE *f = fopen(filename, "a");
            fwrite(buffer, sizeof(BYTE), 512, f);
            fclose(f);
        }
    }
    return 0;
}
