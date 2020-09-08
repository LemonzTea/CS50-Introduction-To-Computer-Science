#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Check if terminal command is correct
    if (argc != 2)
    {
        printf("Usuage: ./recover image");
        return 1;
    }


    // Open file
    FILE *originalFile = fopen(argv[1], "r");
    if (originalFile == NULL)
    {
        return 1;
    }


    // Declaring Variables
    int currentJPG = 0;
    char *newFilename = malloc(8);
    int blockSize = 512;
    bool imageFound = false;
    FILE *newFile;

    // Check for jpeg header
    unsigned char byte[blockSize];

    fread(byte, blockSize, 1, originalFile);

    // Stops only when an image is found
    while (!imageFound)
    {
        // Check if there is the JPG header file
        if (byte[0] == 0xff && byte[1] == 0xd8 && byte[2] == 0xff)
        {
            if (byte[3] >= 0xe0 && byte[3] <= 0xef)
            {
                imageFound = true;
                // Assigns a filename
                sprintf(newFilename, "%03i.jpg", currentJPG);

                // Opens a new file
                newFile = fopen(newFilename, "w");

                // Writes info into the new file
                fwrite(byte, blockSize, 1, newFile);
            }
        }
        else
        {
            // Check the next block
            fread(byte, blockSize, 1, originalFile);
        }
    }

    // Repeats until end of file only if image is found
    while (imageFound && (fread(byte, blockSize, 1, originalFile) == 1))
    {
        // Check if new image is found
        if (byte[0] == 0xff && byte[1] == 0xd8 && byte[2] == 0xff)
        {
            if (byte[3] >= 0xe0 && byte[3] <= 0xef)
            {
                // if found, close file
                fclose(newFile);

                // Make new JPG filename and opens it
                currentJPG++;
                sprintf(newFilename, "%03i.jpg", currentJPG);
                newFile = fopen(newFilename, "w");

                // Write new image data into new JPG filename
                fwrite(byte, blockSize, 1, newFile);

            }
        }
        // if new image is not found, add current buffer into newfile
        else
        {
            fwrite(byte, blockSize, 1, newFile);
        }
    }


    // Close the file if there is a image written
    if (imageFound)
    {
        fclose(newFile);
    }
    free(newFilename);
}
