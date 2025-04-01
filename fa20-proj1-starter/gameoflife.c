/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				Frank
**
**
** DATE:        2025-03-31
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"
#include <stdbool.h>

bool isAlive(Image *image, int row, int col)
{
	return image->image[row][col].B & 1;
}

// return the nums of the alive neighbours of targeted cell
int numsOfNeighbors(Image *image, int row, int col)
{
	int count = 0;
	int direction[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	for (int i = 0; i < 8; i++)
	{
		int next_row = (row + direction[i][0] + image->rows) % image->rows;
		int next_col = (col + direction[i][1] + image->cols) % image->cols;
		if (isAlive(image, next_row, next_col))
		{
			count += 1;
		}
	}
	return count;
}

// Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
// Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
// and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	// YOUR CODE HERE
	Color *color = malloc(sizeof(Color));
	int numsOfNei = numsOfNeighbors(image, row, col);
	if (isAlive(image, row, col))
	{
		// if it is alive, the rule is 前9位
		if ((rule >> (9 + numsOfNei)) & 1)
		{
			// it means the cell should be alive
			*color = (image->image[row][col]);
		}
		else
		{
			color->R = 0;
			color->G = 0;
			color->B = 0;
		}
	}
	else
	{
		if ((rule >> numsOfNei) & 1)
		{
			*color = image->image[row][col];
		}
		else
		{
			color->R = 0;
			color->G = 0;
			color->B = 0;
		}
	}
	return color;
}

// The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
// You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	// YOUR CODE HERE
	Image *newImage = malloc(sizeof(Image));
	newImage->rows = image->rows;
	newImage->cols = image->cols;
	newImage->image = malloc(sizeof(Color *) * image->rows);
	for (int row = 0; row < image->rows; row++)
	{
		newImage->image[row] = malloc(sizeof(Color) * image->cols);
		for (int col = 0; col < image->cols; col++)
		{
			Color *temp = evaluateOneCell(image, row, col, rule);
			newImage->image[row][col] = *temp;
			free(temp);
		}
	}
	return newImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	// YOUR CODE HERE
	char *filename = argv[1];
	char *rule = argv[2];
	char *endptr;
	Image *img = readData(filename);
	Image *newImg = life(img, strtol(rule, &endptr, 0));
	writeData(newImg);

	freeImage(img);
	freeImage(newImg);
}
