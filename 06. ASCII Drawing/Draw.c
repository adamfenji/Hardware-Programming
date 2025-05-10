//Adam Fenjiro, afenjiro@mtu.edu
//CS1142
//Program 6: Draw.c

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

// Function to initialize the image array with default grayscale values (0.0)
void initImage(int width, int height, double image[width][height])
{
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            image[x][y] = 0.0;
        }
    }
}

// Function to print the image with a border
void printImage(int width, int height, double image[width][height])
{
    printf("+");
    for (int x = 0; x < width; x++) {
        printf("-");
    }
    printf("+\n");

    for (int y = 0; y < height; y++) {
        printf("|");
        for (int x = 0; x < width; x++) {
            double color = image[x][y];
            char c;

            if (color < 0.1) {
                c = ' ';
            } else if (color < 0.2) {
                c = '.';
            } else if (color < 0.3) {
                c = ':';
            } else if (color < 0.4) {
                c = '-';
            } else if (color < 0.5) {
                c = '=';
            } else if (color < 0.6) {
                c = '+';
            } else if (color < 0.7) {
                c = '*';
            } else if (color < 0.8) {
                c = '#';
            } else if (color < 0.9) {
                c = '%';
            } else {
                c = '@';
            }
            printf("%c", c);
        }
        printf("|\n");
    }

    printf("+");
    for (int x = 0; x < width; x++) {
        printf("-");
    }
    printf("+\n");
}

// Function to draw a point with a specified color at the given (x, y) location
void drawPoint(int width, int height, double image[width][height], int x, int y, double color)
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
        image[x][y] = color;
    }
}

// Function to draw a filled rectangle at the specified location with a given color
void drawRectangle(int width, int height, double image[width][height], int left, int top, int rectangleWidth, int rectangleHeight, double color)
{
    for (int x = left; x < left + rectangleWidth; x++) {
        for (int y = top; y < top + rectangleHeight; y++) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                image[x][y] = color;
            }
        }
    }
}

// Function to draw a line using the DDA algorithm between two endpoints
void drawLine(int width, int height, double image[width][height], int x1, int y1, int x2, int y2, double color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int steps = (dx > dy) ? dx : dy;

    double xIncrement = (double)(x2 - x1) / steps;
    double yIncrement = (double)(y2 - y1) / steps;

    double x = x1;
    double y = y1;

    for (int i = 0; i <= steps; i++) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            image[(int)x][(int)y] = color;
        }
        x += xIncrement;
        y += yIncrement;
    }
}

void convertToBlackAndWhite(int width, int height, double image[height][width], double threshold) {

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (image[y][x] >= threshold) {
                image[y][x] = 1.0;
            } else {
                image[y][x] = 0.0;
            }
        }
    }
}

// Function to calculate the minimum, maximum, and average grayscale values in the image
void printStats(int width, int height, double image[height][width]) {
    double min = DBL_MAX;
    double max = -DBL_MAX;
    double sum = 0;
    double sum_squared_diff = 0;

    // Compute minimum, maximum, and sum of pixel values
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double pixel = image[i][j];
            if (pixel < min) {
                min = pixel;
            }
            if (pixel > max) {
                max = pixel;
            }
            sum += pixel;
        }
    }

    // Compute mean
    double mean = sum / (width * height);

    // Compute sum of squared differences for standard deviation
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double pixel = image[i][j];
            sum_squared_diff += pow(pixel - mean, 2);
        }
    }

    // Compute standard deviation
    double sd = sqrt(sum_squared_diff / (width * height));

    // Print the statistics
    printf("Color range [%.2f, %.2f], mean %.4f, sd %.4f\n", min, max, mean, sd);
}

void floodFill(int width, int height, double image[width][height], int x, int y, double color)
{    if (x < 0 || x >= width || y < 0 || y >= height) {
        // Coordinates are out of bounds
        return;
    }

    if (image[x][y] >= color) {
        // Current pixel is darker or equal to the target color
        return;
    }

    image[x][y] = color;

    floodFill(width, height, image, x - 1, y, color); // Left
    floodFill(width, height, image, x + 1, y, color); // Right
    floodFill(width, height, image, x, y - 1, color); // Up
    floodFill(width, height, image, x, y + 1, color); // Down
} 

// Print the resulting greyscale image as ASCII art.
// You need to fix the lines marked with TODO comments to read input from standard input.
// Do not change other things in the main function.
int main(void)
{
    // Read in the size of the drawing canvas
    int width = 0;
    int height = 0;
    
    // Read the width and height from standard input
    int result = scanf("%d %d", &width, &height);
    
    // Program only supports images that are 1x1 or bigger
    if ((width <= 0) || (height <= 0) || (result != 2))
    {
        printf("Failed to read a valid width and height from standard input!\n");
        return 0;
    }
    
    // Create the 2D array and initialize all the greyscale values to 0.0.
    // The first dimension is the x-coordinate.
    // The second dimension is the y-coordinate.
    double image[width][height];
    initImage(width, height, image);
    
    char command = '\0';
    double color = 0.0;
    
    // Keep reading in drawing commands until we reach the end of the input
    while (scanf(" %c", &command) == 1)
    {
        switch (command)
        {		
            case 'p': 	
            {
                // Draw a point, read in: x, y, color
                int x = 0;
                int y = 0;
                result = scanf("%d %d %lf", &x, &y, &color);
                if (result != 3)
                {
                    printf("Invalid point command!\n");
                    return 0;
                }
                drawPoint(width, height, image, x, y, color);
                break;
            }
            case 'r': 	
            {
                // Draw a rectangle, read in: x, y, w, h, color
                int left = 0;
                int top = 0;
                int rectangleWidth = 0;
                int rectangleHeight = 0;
                result = scanf("%d %d %d %d %lf", &left, &top, &rectangleWidth, &rectangleHeight, &color);
                if (result != 5)
                {
                    printf("Invalid rectangle command!\n");
                    return 0;
                }
                drawRectangle(width, height, image, left, top, rectangleWidth, rectangleHeight, color);
                break;
            }
            case 'b':   
            {
                // Convert to black and white
                double threshold = 0.0;
                result = scanf("%lf", &threshold);
                if (result != 1)
                {
                    printf("Invalid black and white command!\n");
                    return 0;
                }
                convertToBlackAndWhite(width, height, image, threshold);
                break;
            }

            case 'l':
            {
                // Draw a line, read in x1, y1, x2, y2, color
                int x1 = 0;
                int y1 = 0;
                int x2 = 0;
                int y2 = 0;      
                result = scanf("%d %d %d %d %lf", &x1, &y1, &x2, &y2, &color);
                if (result != 5)
                {
                    printf("Invalid line command!\n");
                    return 0;
                }
                drawLine(width, height, image, x1, y1, x2, y2, color);
                break;
            }            
            case 'f':
            {
                // Flood fill a color in, read in: x, y, color
                int x = 0;
                int y = 0;
                result = scanf("%d %d %lf", &x, &y, &color);
                if (result != 3)
                {
                    printf("Invalid flood fill command!\n");
                    return 0;
                }
                floodFill(width, height, image, x, y, color);
                break;
            }
            default:
            {
                printf("Unknown command!\n");
                return 0;
            }
        }
    }
	
    // Print the final image
    printImage(width, height, image);
    
    // Finally display some statistics about the image
    printStats(width, height, image);

    return 0;
}