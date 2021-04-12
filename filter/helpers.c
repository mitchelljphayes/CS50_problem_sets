#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int r = image[h][w].rgbtRed;
            int g = image[h][w].rgbtGreen;
            int b = image[h][w].rgbtBlue;

            //calculate average of rgb, divide using float to prevent integer division.
            int gs_average = round((r + g + b) / 3.0);

            //reassign averge value to all colour channels at current index
            image[h][w].rgbtRed = gs_average;
            image[h][w].rgbtGreen = gs_average;
            image[h][w].rgbtBlue = gs_average;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int r = image[h][w].rgbtRed;
            int g = image[h][w].rgbtGreen;
            int b = image[h][w].rgbtBlue;

            // find the reflected width index for the reflected image
            int rw = (width - 1) - w;
            // generate temporary image struct to keep image from being overwritten while being read
            temp[h][rw].rgbtRed = r;
            temp[h][rw].rgbtGreen = g;
            temp[h][rw].rgbtBlue = b;
        }
    }
    // reassiging temporary image to main image.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
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
            //find the avaeages of each colour channel all neighbouring pixels
            int sqrs = 0, total_r = 0, total_g = 0, total_b = 0;
            for (int i = (h - 1); i <= (h + 1); i++)
            {
                if ((i >= 0) && (i < height)) // disregard height edgecases
                {
                    for (int j = (w - 1); j <= (w + 1); j++)
                    {
                        if ((j >= 0) && (j < width)) // disregard width edgecases
                        {
                            sqrs++;
                            total_r += image[i][j].rgbtRed;
                            total_g += image[i][j].rgbtGreen;
                            total_b += image[i][j].rgbtBlue;
                        }
                    }
                }
            }
            // calculate the blurred values for each channel.
            int blur_r = round(total_r / (float) sqrs);
            int blur_g = round(total_g / (float) sqrs);
            int blur_b = round(total_b / (float) sqrs);
            // generate temporary image struct to keep image from being overwritten while being read
            temp[h][w].rgbtRed = blur_r;
            temp[h][w].rgbtGreen = blur_g;
            temp[h][w].rgbtBlue = blur_b;
        }
    }
    // reassiging temporary image to main image.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //application of the Sobel operator.
            int sqrs = 9, total_gxr = 0, total_gxg = 0, total_gxb = 0, total_gyr = 0, total_gyg = 0, total_gyb = 0;
            for (int i = (h - 1); i <= (h + 1); i++)
            {
                if ((i >= 0) && (i < height)) // disregard height edgecases
                {
                    for (int j = (w - 1); j <= (w + 1); j++)
                    {
                        if ((j >= 0) && (j < width)) // disregard width edgecases
                        {
                            //Generate Gx Kernel
                            int sobx = (j - w) * (2 - pow((i - h), 2));
                            total_gxr += image[i][j].rgbtRed * sobx;
                            total_gxg += image[i][j].rgbtGreen * sobx;
                            total_gxb += image[i][j].rgbtBlue * sobx;

                            //Generate Gy Kernel
                            int soby = (i - h) * (2 - pow((j - w), 2));
                            total_gyr += image[i][j].rgbtRed * soby;
                            total_gyg += image[i][j].rgbtGreen * soby;
                            total_gyb += image[i][j].rgbtBlue * soby;

                        }
                    }
                }
            }
            // calculate the sobel values for each channel.
            int sob_r = round(fmin((sqrt(pow(total_gxr, 2) + pow(total_gyr, 2))), 255));
            int sob_g = round(fmin((sqrt(pow(total_gxg, 2) + pow(total_gyg, 2))), 255));
            int sob_b = round(fmin((sqrt(pow(total_gxb, 2) + pow(total_gyb, 2))), 255));
            // generate temporary image struct to keep image from being overwritten while being read
            temp[h][w].rgbtRed = sob_r;
            temp[h][w].rgbtGreen = sob_g;
            temp[h][w].rgbtBlue = sob_b;
        }
    }
    // reassiging temporary image to main image.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
        }
    }
    return;
}
