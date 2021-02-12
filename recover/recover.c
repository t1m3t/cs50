#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *img_f = fopen(argv[1], "r");
    if (img_f == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    int file_n = 0;
    uint8_t buffer[512];
    char fname[8];
    int count = 0;
    FILE *image = NULL;
    while (fread(&buffer, sizeof(uint8_t), 512, img_f))
    {
        // Still only maybe, might have to implement more complex check
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (image != NULL)
            {
                fclose(image);
            }
            sprintf(fname, "%.3i.jpg", count);
            count++;
            image = fopen(fname, "w");
            if (image == NULL)
            {
                printf("Image file could not be created.\n");
            }
        }
        if (image != NULL)
        {
            fwrite(&buffer, sizeof(uint8_t), 512, image);
        }
    }

    fclose(img_f);

    return 0;
}