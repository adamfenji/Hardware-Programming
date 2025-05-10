/*
-Adam Fenjiro, afenjiro@mtu.edu
-CS1142
-10/30/2023
-Project1: RandomInts.c
*/

#include <stdio.h>
#include <stdlib.h>

#define A 75
#define C 74
#define M 65537

// Function to generate random integers
int generateRandomInt(int min, int max, int *seed) {
    *seed = (A * (*seed) + C) % M;
    return min + ((*seed) % (max - min + 1));
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: RandomInts <min> <max> <num> <seed>\n");
        return 1;
    }

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    int num = atoi(argv[3]);
    int seed = atoi(argv[4]);

    // Check if arguments are valid
    if (min < -1000 || min > 1000 || max < -1000 || max > 1000 || max < min || num <= 0 || seed < 0) {
        printf("ERROR: invalid args!\n");
        return 1;
    }

    // Generate and print random integers
    for (int i = 0; i < num; i++) {
        int randomInt = generateRandomInt(min, max, &seed);
        printf("%d ", randomInt);

        if (i % 10 == 9) {
            printf("\n");
        }
    }
    
    printf("\n");

    return 0;
}
