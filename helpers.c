#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop the rows and columns and for each column give each rgb color the average color to have grayscale affect
    for (int i = 0; i < height; i++)
    {
        //now loop the columns and apply grayscale
        for (int j = 0; j < width; j++)
        {
            //calculate the average on the grayscale color for each rgb color
            double avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            //make sure the value is an integer
            int n = round(avg);
            image[i][j].rgbtBlue = n;
            image[i][j].rgbtGreen = n;
            image[i][j].rgbtRed = n;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop through each row and the for each column, calculate the sepia color for each rgb color and apply to each color
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate the sepia number for each color and apply to each color respectively
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            //check to make sure that the value does not exceed 255 else set the value to 255
            if (sepiaRed > 255)
            {

                image[i][j].rgbtRed = 255;

            }
            else
            {
                image[i][j].rgbtRed =  sepiaRed ;

            }
            //check to make sure that the value does not exceed 255 else set the value to 255
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;

            }
            else
            {
                image[i][j].rgbtGreen =  sepiaGreen  ;

            }
            //check to make sure that the value does not exceed 255 else set the value to 255
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtGreen = 255;

            }
            else
            {
                image[i][j].rgbtBlue =   sepiaBlue  ;

            }

        }
    }

    return;
}

// Reflect image horizontally

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //swap function prototype
    void swap(RGBTRIPLE *, RGBTRIPLE *);
    for (int i = 0; i < height; i++)
    {
        //initialize counter
        int n = 1;
        for (int j = 0; j < width / 2; j++)
        {
            //call the function to perform swap
            swap(&image[i][j], &image[i][width - 1 - j]);
            n++;
        }
    }



    return;
}
//create function swap to use in reflectioom for swaping pixels
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tempArray;
    RGBTRIPLE tempArray2;
    tempArray = *a;
    tempArray2 = *b;
    *a = tempArray2;
    *b = tempArray;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create an image copy
    RGBTRIPLE imgCopy[height][width];
    float avgRed;
    float avgGreen;
    float avgBlue;
    //create a copy of original image to save original pixel values
    for (int row = 0; row < height; row++)
    {
        for (int w = 0; w < width; w++)
        {

            imgCopy[row][w].rgbtRed = image[row][w].rgbtRed;
            imgCopy[row][w].rgbtGreen = image[row][w].rgbtGreen;
            imgCopy[row][w].rgbtBlue = image[row][w].rgbtBlue;


        }

    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //In the case that the pixel is on the top left edge
            if (w == 0 && h == 0)
            {
                avgRed = (float)(imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed + imgCopy[h + 1][w].rgbtRed + imgCopy[h + 1][w + 1].rgbtRed) / 4;
                avgGreen = (float)(imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen + imgCopy[h + 1][w + 1].rgbtGreen) / 4;
                avgBlue = (float)(imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue + imgCopy[h + 1][w + 1].rgbtBlue) / 4;
                avgRed = round(avgRed);
                avgBlue = round(avgBlue);
                avgGreen = round(avgGreen);
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;

            }
            //In the case that the pixel is on the lower left edge
            else if (w == 0 && h == (height - 1))
            {
                avgRed = (float)(imgCopy[h - 1][w].rgbtRed + imgCopy[h - 1][w + 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed) / 4;
                avgGreen = (float)(imgCopy[h - 1][w].rgbtGreen + imgCopy[h - 1][w + 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen) / 4;
                avgBlue = (float)(imgCopy[h - 1][w].rgbtBlue + imgCopy[h - 1][w + 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue) / 4;
                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;

            }
            //In the case that the pixel is on top Right
            else if (h == 0 && w == (width - 1))
            {
                avgRed = (float)(imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h + 1][w - 1 ].rgbtRed + imgCopy[h + 1][w].rgbtRed)/ 4;
                avgGreen = (float)(imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h + 1][w - 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen) / 4;
                avgBlue = (float)(imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h + 1][w - 1].rgbtBlue + imgCopy[h+  1][w].rgbtBlue) / 4;
                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;

            }
            //In the case that the pixel is on lower right
            else if(h == (height - 1) && w == (width - 1))
            {
                avgRed = (float)(imgCopy[h - 1][w - 1].rgbtRed + imgCopy[h - 1][w].rgbtRed + imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed) / 4;
                avgBlue = (float)(imgCopy[h - 1][w - 1].rgbtBlue + imgCopy[h - 1][w].rgbtBlue + imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue) / 4;
                avgGreen = (float)(imgCopy[h - 1][w - 1].rgbtGreen + imgCopy[h - 1][w].rgbtGreen + imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen) / 4;
                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;

            }
            //In the case that the pixel is on left side
            else if (w == 0 && (h > 0 && h < height - 1))
            {
                avgRed = (float)(imgCopy[h - 1][w].rgbtRed + imgCopy[h - 1][w + 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed + imgCopy[h + 1][w].rgbtRed + imgCopy[h + 1][w + 1].rgbtRed) / 6;
                avgGreen = (float)(imgCopy[h - 1][w].rgbtGreen + imgCopy[h - 1][w + 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen + imgCopy[h + 1][w + 1].rgbtGreen) / 6;
                avgBlue = (float)(imgCopy[h - 1][w].rgbtBlue + imgCopy[h - 1][w + 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue + imgCopy[h + 1][w + 1].rgbtBlue) / 6;
                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;

            }
            //In the case that the pixel is on right side
            else if (w == (width - 1) && (h > 0 && h < height - 1))
            {
                avgRed = (float)(imgCopy[h - 1][w - 1].rgbtRed + imgCopy[h - 1][w].rgbtRed + imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h + 1][w - 1].rgbtRed + imgCopy[h + 1][w].rgbtRed) / 6;
                avgGreen = (float)(imgCopy[h - 1][w - 1].rgbtGreen + imgCopy[h - 1][w].rgbtGreen + imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h + 1][w - 1].rgbtGreen + imgCopy[h+1][w].rgbtGreen) / 6;
                avgBlue = (float)(imgCopy[h - 1][w - 1].rgbtBlue + imgCopy[h - 1][w].rgbtBlue + imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h + 1][w - 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue) / 6;
                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;

            }
            //In the case that the pixel is on upper side
            else if (h == 0 && (w > 0 &&  w < width - 1))
            {
                avgRed = (float)(imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed + imgCopy[h + 1][w - 1].rgbtRed + imgCopy[h + 1][w].rgbtRed + imgCopy[h + 1][w + 1].rgbtRed) / 6;
                avgGreen = (float)(imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen + imgCopy[h + 1][w - 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen + imgCopy[h + 1][w + 1].rgbtGreen) / 6;
                avgBlue = (float)(imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue + imgCopy[h + 1][w - 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue + imgCopy[h + 1][w + 1].rgbtBlue) / 6;
                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;

            }
            //In the case that the pixel is on lower side
            else if (h == height - 1 && (w > 0 && w < width - 1))
            {
                avgRed = (float)(imgCopy[h - 1][w - 1].rgbtRed + imgCopy[h - 1][w].rgbtRed + imgCopy[h - 1][w + 1].rgbtRed + imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed) / 6;
                avgGreen = (float)(imgCopy[h - 1][w - 1].rgbtGreen + imgCopy[h - 1][w].rgbtGreen + imgCopy[h - 1][w + 1].rgbtGreen + imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen) / 6;
                avgBlue = (float)(imgCopy[h - 1][w - 1].rgbtBlue + imgCopy[h - 1][w].rgbtBlue + imgCopy[h - 1][w + 1].rgbtBlue + imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w + 1].rgbtBlue) / 6;
                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;

            }
            //In the case that the pixel is on the middle and can form a 3x3 grid
            else
            {
                avgRed = (float)(imgCopy[h - 1][w - 1].rgbtRed + imgCopy[h - 1][w].rgbtRed + imgCopy[h - 1][w + 1].rgbtRed + imgCopy[h][w - 1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w + 1].rgbtRed + imgCopy[h + 1][w - 1].rgbtRed + imgCopy[h + 1][w].rgbtRed + imgCopy[h + 1][w + 1].rgbtRed) / 9;
                avgGreen = (float)(imgCopy[h - 1][w - 1].rgbtGreen + imgCopy[h - 1][w].rgbtGreen + imgCopy[h - 1][w + 1].rgbtGreen + imgCopy[h][w - 1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w + 1].rgbtGreen + imgCopy[h + 1][w - 1].rgbtGreen + imgCopy[h + 1][w].rgbtGreen + imgCopy[h +  1][w + 1].rgbtGreen) / 9;
                avgBlue = (float)(imgCopy[h - 1][w - 1].rgbtBlue + imgCopy[h - 1][w].rgbtBlue + imgCopy[h-1][w + 1].rgbtBlue + imgCopy[h][w - 1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][ w+ 1].rgbtBlue + imgCopy[h + 1][w - 1].rgbtBlue + imgCopy[h + 1][w].rgbtBlue + imgCopy[h + 1][w + 1].rgbtBlue) / 9;
                avgRed = round(avgRed);
                avgGreen = round(avgGreen);
                avgBlue = round(avgBlue);
                image[h][w].rgbtRed = avgRed;
                image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;

            }

        }

    }
    return;
}
