#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    //check command line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover input.raw\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    int count = 0;
    FILE *output = NULL;
    char filename[8];

    //repeat read 512 bytes once a time to buffer
    while (fread(&buffer, BLOCK_SIZE, 1, input))
    {
        //check the start of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count)
            {
                fclose(output);
            }

            //generate output JPEG file
            sprintf(filename, "%03i.jpg", count);
            output = fopen(filename, "w");
            count++;
        }

        if (count)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, output);
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}