#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint8_t value = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            RGBTRIPLE pixel = { .rgbtBlue = value, .rgbtGreen = value, .rgbtRed = value };
            image[i][j] = pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    memcpy(temp, image, sizeof temp);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = 0;
            int green = 0;
            int red = 0;
            // Looping to get the surrounding pixels
            int count = 0;
            for (int a = -1; a <= 1; a++)
            {
                for (int b = -1; b <= 1; b++)
                {
                    // Check if the surrounding pixel is inside the image
                    if (i + a >= 0 && i + a < height && j + b >= 0 && j + b < width)
                    {
                        blue += temp[i + a][j + b].rgbtBlue;
                        green += temp[i + a][j + b].rgbtGreen;
                        red += temp[i + a][j + b].rgbtRed;
                        count++;
                    }
                }
            }
            blue = round(blue / (double) count);
            green = round(green / (double) count);
            red = round(red / (double) count);
            RGBTRIPLE pixel = { .rgbtBlue = blue, .rgbtGreen = green, .rgbtRed = red };
            image[i][j] = pixel;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    memcpy(temp, image, sizeof temp);
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0;
            int gxGreen = 0;
            int gxRed = 0;
            int gyBlue = 0;
            int gyGreen = 0;
            int gyRed = 0;
            for (int a = -1; a <= 1; a++)
            {
                for (int b = -1; b <= 1; b++)
                {
                    RGBTRIPLE value;
                    if (i + a >= 0 && i + a < height && j + b >= 0 && j + b < width)
                    {
                        value = temp[i + a][j + b];
                        gxBlue += (value.rgbtBlue * gx[a + 1][b + 1]);
                        gxGreen += (value.rgbtGreen * gx[a + 1][b + 1]);
                        gxRed += (value.rgbtRed * gx[a + 1][b + 1]);
                        gyBlue += (value.rgbtBlue * gy[a + 1][b + 1]);
                        gyGreen += (value.rgbtGreen * gy[a + 1][b + 1]);
                        gyRed += (value.rgbtRed * gy[a + 1][b + 1]);
                    }
                }
            }
            int blue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));
            int green = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            int red = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            image[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            image[i][j].rgbtGreen = (green > 255) ? 255 : green;
            image[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }
    return;
}
