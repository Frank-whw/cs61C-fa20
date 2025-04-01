/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Frank
**
**
** DATE:        2025-03-31
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

// Opens a .ppm P3 image file, and constructs an Image object.
// You may find the function fscanf useful.
// Make sure that you close the file with fclose before returning.
Image *readData(char *filename)
{
	// YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	Image *img = malloc(sizeof(Image));
	char format[4];
	fscanf(fp, "%s", format);
	fscanf(fp, "%d %d", &img->cols, &img->rows);
	img->image = malloc(sizeof(Color **) * img->rows);
	int nums;
	fscanf(fp, "%d", &nums);
	for (int row = 0; row < img->rows; row++)
	{
		img->image[row] = malloc(sizeof(Color *) * img->cols);
		for (int col = 0; col < img->cols; col++)
		{
			// printf("%d\n", row);
			fscanf(fp, "%hhu %hhu %hhu", &img->image[row][col].R, &img->image[row][col].G, &img->image[row][col].B);
		}
	}
	fclose(fp);
	return img;
}

// Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	// YOUR CODE HERE
	printf("P3\n%d %d\n255\n", image->cols, image->rows);
	for (int row = 0; row < image->rows; row++)
	{
		for (int col = 0; col < image->cols; col++)
		{
			if (col != 0)
				printf("   ");
			printf("%3hhu %3hhu %3hhu", image->image[row][col].R, image->image[row][col].G, image->image[row][col].B);
		}
		printf("\n");
	}
}

// Frees an image
void freeImage(Image *image)
{
	// YOUR CODE HERE
	for (int row = 0; row < image->rows; row++)
	{
		free(image->image[row]);
	}
	free(image->image);
	free(image);
}

// int main()
// {
// 	Image *img = readData("JohnConway.ppm");
// 	writeData(img);
// }