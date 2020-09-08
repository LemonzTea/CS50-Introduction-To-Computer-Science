#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int blue = image[h][w].rgbtBlue;
            int green = image[h][w].rgbtGreen;
            int red = image[h][w].rgbtRed;

            int average = round((blue + green + red) / 3.0);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int originalBlue = image[h][w].rgbtBlue;
            int originalGreen = image[h][w].rgbtGreen;
            int originalRed = image[h][w].rgbtRed;


            // Check if more than 255 for blue
            if (round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue) > 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
            }


            // Check if more than 255 for green
            if (round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue) > 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            else
            {
                image[h][w].rgbtGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            }

            // Check if more than 255 for red
            if (round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue) > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0, max = round(width / 2); w < max; w++)
        {
            // Creates a temp variable to store value
            RGBTRIPLE temp;
            temp.rgbtGreen = image[h][width - (w + 1)].rgbtGreen;
            temp.rgbtBlue = image[h][width - (w + 1)].rgbtBlue;
            temp.rgbtRed = image[h][width - (w + 1)].rgbtRed;

            // Swap places with last value
            image[h][width - (w + 1)].rgbtGreen = image[h][w].rgbtGreen;
            image[h][width - (w + 1)].rgbtBlue = image[h][w].rgbtBlue;
            image[h][width - (w + 1)].rgbtRed = image[h][w].rgbtRed;

            // Swap initial
            image[h][w].rgbtGreen = temp.rgbtGreen;
            image[h][w].rgbtBlue = temp.rgbtBlue;
            image[h][w].rgbtRed = temp.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;
            float count = 0.0;

            // Cycle through blocks around the main area
            for (int hAverage = -1; hAverage <= 1; hAverage++)
            {
                for (int wAverage = -1; wAverage <= 1; wAverage++)
                {   
                    // check if surrounding height is out of bounds
                    if (h + hAverage >= 0 && h + hAverage < height)
                    {
                        // check if surrounding width is out of bounds
                        if (w + wAverage >= 0 && w + wAverage < width)
                        {
                            sumBlue += image[h + hAverage][w + wAverage].rgbtBlue;
                            sumGreen += image[h + hAverage][w + wAverage].rgbtGreen;
                            sumRed += image[h + hAverage][w + wAverage].rgbtRed;
                            count++;
                        }
                    }
                }
            }

            // Declaring new values in a new image
            temp[h][w].rgbtBlue = round(sumBlue / count);
            temp[h][w].rgbtGreen = round(sumGreen / count);
            temp[h][w].rgbtRed = round(sumRed / count);
        }
    }
    
    // Copy new image into previous image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
        }
    }
    
    return;
}
