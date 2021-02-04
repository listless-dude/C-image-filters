#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Read the RGB values from the image
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            // Rounding the average to avoid errors i.e. > 255
            float avg = round((blue + green + red) / 3);

            // Assigning each of the RGB value equal to the avg of the RGB value of each pixel
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initializing the RGB values from the image
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            // Calculating the sepia value from the given formula in the pset
            float sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            float sepiaGreen = round(.349 * red + .686 * green  + .168 * blue);
            float sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            // Checking if the values are not exceeding 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            // Assigning the RGB values of the image to the new calculated sepia values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // If done till the 'width' it becomes reflected symmetrically vertically, that is why done till 'width/2'
        for (int j = 0; j < width / 2; j++)
        {
            // Initializing the RGB values from the image
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            // Reversing the image horizontally, just like reversing an 1D array
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            // Assigning the newly reverse image with the oriiginal RGB values
            image[i][width - j - 1].rgbtBlue = blue;
            image[i][width - j - 1].rgbtGreen = green;
            image[i][width - j - 1].rgbtRed = red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating a temporary image for storing values
    RGBTRIPLE tmp[height][width];
    float blue, green, red, count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = green = red = count = 0;

            // This loop runs from rows i - 1 to i + 1, i.e. if i = 0, runs from -1 to 1, if i = 2, runs from 1 to 3
            for (int x = i - 1; x <= i + 1; x++)
            {
                // This loop runs from columns j - 1 to j + 1, i.e. if j = 3, j runs from 2 to 4
                for (int y = j - 1; y <= j + 1; y++)
                {
                    // Adding RGB values around 3x3 of the pixel
                    // Check the pixels around
                    if ((x >= 0 && x < height) && (y >= 0 && y < width))
                    {
                        blue += image[x][y].rgbtBlue;
                        green += image[x][y].rgbtGreen;
                        red += image[x][y].rgbtRed;
                        // count records the number of pixels around the particular pixel
                        count++;
                    }
                }
            }

            // Make sure that the values is not divided by zero
            if (count != 0)
            {
                tmp[i][j].rgbtBlue = round(blue / count);
                tmp[i][j].rgbtGreen = round(green / count);
                tmp[i][j].rgbtRed = round(red / count);
            }
            else
            {
                return;
            }
        }
    }

    // Assigning the temporary values to the original image to create the blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
