#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int h = 0; h < height; h++)
    {
        // For each column in each row
        for (int w = 0; w < width; w++)
        {
            // Finds the average color
            int average = round((image[h][w].rgbtBlue + image[h][w].rgbtRed + image[h][w].rgbtGreen) / 3.0);

            // Assigns the average color to all the colors in that pixel
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int h = 0; h < height; h++)
    {
        // For each column in each row
        for (int w = 0; w < width / 2; w++)
        {
            // Creates a temporary RGBTRIPLE
            RGBTRIPLE temp;

            int deduct = w + 1;

            // Set information of temp
            temp.rgbtBlue = image[h][width - deduct].rgbtBlue;
            temp.rgbtRed = image[h][width - deduct].rgbtRed;
            temp.rgbtGreen = image[h][width - deduct].rgbtGreen;

            // Replace last info with front into
            image[h][width - deduct].rgbtBlue = image[h][w].rgbtBlue;
            image[h][width - deduct].rgbtRed = image[h][w].rgbtRed;
            image[h][width - deduct].rgbtGreen = image[h][w].rgbtGreen;

            // Replace first info with temp
            image[h][w].rgbtBlue = temp.rgbtBlue;
            image[h][w].rgbtRed = temp.rgbtRed;
            image[h][w].rgbtGreen = temp.rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creates new temporary image
    RGBTRIPLE temp[height][width];

    // For each row
    for (int h = 0; h < height; h++)
    {
        // For each column in each row
        for (int w = 0; w < width; w++)
        {
            int aRed = 0;
            int aBlue = 0;
            int aGreen = 0;
            float count = 0.0;

            for (int avgH = -1; avgH <= 1; avgH++)
            {
                for (int avgW = -1; avgW <= 1; avgW++)
                {
                    if (h + avgH >= 0 && h + avgH < height)
                    {
                        if (w + avgW >= 0 && w + avgW < width)
                        {
                            aRed += image[h + avgH][w + avgW].rgbtRed;
                            aGreen += image[h + avgH][w + avgW].rgbtGreen;
                            aBlue += image[h + avgH][w + avgW].rgbtBlue;
                            count++;
                        }
                    }
                }
            }

            temp[h][w].rgbtRed = round(aRed / count);
            temp[h][w].rgbtBlue = round(aBlue / count);
            temp[h][w].rgbtGreen = round(aGreen / count);
        }
    }

    // For each row
    for (int h = 0; h < height; h++)
    {
        // For each column in each row
        for (int w = 0; w < width; w++)
        {
            // Replace old image with temp image
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // For each row
    for (int h = 0; h < height; h++)
    {
        // For each column in each row
        for (int w = 0; w < width; w++)
        {
            int redx = 0;
            int bluex = 0;
            int greenx = 0;
            int Gx[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1};

            int redy = 0;
            int bluey = 0;
            int greeny = 0;
            int Gy[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1};

            int count = 0;

            // Repeat check 3x3 area (height)
            for (int h2 = -1; h2 <= 1; h2++)
            {
                // Repeat check 3x3 area (width)
                for (int w2 = -1; w2 <= 1; w2++)
                {
                    // if area is within height and width
                    if (h + h2 >= 0 && h + h2 < height && w + w2 >= 0 && w + w2 < width)
                    {
                        redx += image[h + h2][w + w2].rgbtRed * Gx[count];
                        bluex += image[h + h2][w + w2].rgbtBlue * Gx[count];
                        greenx += image[h + h2][w + w2].rgbtGreen * Gx[count];

                        redy += image[h + h2][w + w2].rgbtRed * Gy[count];
                        bluey += image[h + h2][w + w2].rgbtBlue * Gy[count];
                        greeny += image[h + h2][w + w2].rgbtGreen * Gy[count];
                    }
                    count++;
                }
            }

            // Assigns the new value to temp
            if (round(sqrt(redx * redx + redy * redy)) > 255)
            {
                temp[h][w].rgbtRed = 255;
            }
            else
            {
                temp[h][w].rgbtRed = round(sqrt(redx * redx + redy * redy));
            }

            if (round(sqrt(bluex * bluex + bluey * bluey)) > 255)
            {
                temp[h][w].rgbtBlue = 255;
            }
            else
            {
                temp[h][w].rgbtBlue = round(sqrt(bluex * bluex + bluey * bluey));
            }

            if (round(sqrt(greenx * greenx + greeny * greeny)) > 255)
            {
                temp[h][w].rgbtGreen = 255;
            }
            else
            {
                temp[h][w].rgbtGreen = round(sqrt(greenx * greenx + greeny * greeny));
            }
        }
    }

    // For each row
    for (int h = 0; h < height; h++)
    {
        // For each column in each row
        for (int w = 0; w < width; w++)
        {
            // Replace old image with temp image
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
        }
    }
    return;
}
