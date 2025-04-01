/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				Frank
**
** DATE:        2025-03-31
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

// Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	// YOUR CODE HERE
	Color *color = malloc(sizeof(Color));
	if (image->image[row][col].B & 1)
	{
		// the last bits of B is 1, means the color should be black
		color->R = 255;
		color->G = 255;
		color->B = 255;
	}
	else
	{
		color->R = 0;
		color->G = 0;
		color->B = 0;
	}
	return color;
}

// Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	// YOUR CODE HERE
	Image *newImage = malloc(sizeof(Image));
	newImage->rows = image->rows;
	newImage->cols = image->cols;
	newImage->image = malloc(sizeof(Color **) * image->rows);
	for (int row = 0; row < image->rows; row++)
	{
		newImage->image[row] = malloc(sizeof(Color *) * image->cols);
		for (int col = 0; col < image->cols; col++)
		{
			newImage->image[row][col] = *evaluateOnePixel(image, row, col);
		}
	}
	return newImage;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image,
where each pixel is black if the LSB of the B channel is 0,
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/

// #include "imageloader.c"
// It seems I don'tmake  need to include this c problem, because in the imageloader.h there are extern functions.
int main(int argc, char **argv)
{
	// YOUR CODE HERE
	char *filename = argv[1];
	Image *img = readData(filename);
	Image *newImg = steganography(img);
	writeData(newImg);

	freeImage(img);
	freeImage(newImg);
}
