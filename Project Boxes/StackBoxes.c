/*
-Adam Fenjiro, afenjiro@mtu.edu
-CS1142
-10/30/2023
-Project1: StackBoxes.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Display the stack heights as a bar chart
void displayStacks(int *stackHeights, int stacks) {
    int maxStackHeight = 0;

    // Find the maximum stack height
    for (int i = 0; i < stacks; i++) {
        if (stackHeights[i] > maxStackHeight) {
            maxStackHeight = stackHeights[i];
        }
    }

    // Print the bar chart
    for (int i = 90; i >= 0; i -= 10) {
    printf(">%2d%% ", i);
    for (int j = 0; j < stacks; j++) {
        int percentage = (int)round((stackHeights[j] * 100.0) / maxStackHeight);
        if (percentage >= i) {
            printf("X");
        } else {
            printf(".");
        }
    }
    printf("\n");
}

    // Print the x-axis labels
    printf("     ");
    for (int i = 0; i < stacks; i++) {
        printf("%d", i % 10);
    }
    printf("\n");
}

int findMinStack(int *stackHeights, int stacks, int boxID, int delta) {
    int homeStack = boxID;
    int minStack = homeStack;
    int minHeight = stackHeights[homeStack];

    for (int i = 1; i <= delta; i++) {
        int leftNeighbor = homeStack - i;
        int rightNeighbor = homeStack + i;

        if (leftNeighbor >= 0 && stackHeights[leftNeighbor] < minHeight) {
            minStack = leftNeighbor;
            minHeight = stackHeights[leftNeighbor];
        }

        if (rightNeighbor < stacks && stackHeights[rightNeighbor] < minHeight) {
            minStack = rightNeighbor;
            minHeight = stackHeights[rightNeighbor];
        }
    }

    return minStack;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: StackBoxes <stacks> <delta>\n");
        return 1;
    }

    int stacks = atoi(argv[1]);
    int delta = atoi(argv[2]);

    if (stacks <= 0 || delta < 0) {
        printf("ERROR: invalid args!\n");
        return 1;
    }

    int validBoxes = 0;
    int invalidBoxes = 0;
    int maxStackHeight = 0;
    int wastedVolume = 0;
    int minStackHeight = stacks;

    int *stackHeights = (int *)calloc(stacks, sizeof(int));

    if (stackHeights == NULL) {
        printf("ERROR: Memory allocation failed!\n");
        return 1;
    }

    int boxID;

    while (scanf("%d", &boxID) == 1) {
        if (boxID >= 0 && boxID < stacks) {
            validBoxes++;

            int minStack = findMinStack(stackHeights, stacks, boxID, delta);
            stackHeights[minStack]++;

            if (stackHeights[minStack] > maxStackHeight) {
                maxStackHeight = stackHeights[minStack];
            }
        } else {
            invalidBoxes++;
        }
    }

    if (validBoxes == 0) {
    printf("ERROR: no valid boxes!\n");
    return 1;
    }

    // Calculate wastedVolume based on boxes placed.
    for (int i = 0; i < stacks; i++) {
        wastedVolume += maxStackHeight - stackHeights[i];
    }

    // Calculate minStackHeight after placing all the boxes
    for (int i = 0; i < stacks; i++) {
        if (stackHeights[i] < minStackHeight) {
            minStackHeight = stackHeights[i];
        }
    }

    printf("Valid boxes: %d (%.1f%%)\n", validBoxes, (validBoxes * 100.0) / (validBoxes + invalidBoxes));
    printf("Invalid boxes: %d (%.1f%%)\n", invalidBoxes, (invalidBoxes * 100.0) / (validBoxes + invalidBoxes));
    printf("Min stack height: %d\n", minStackHeight);
    printf("Max stack height: %d\n", maxStackHeight);
    printf("Wasted volume: %d (%.1f%%)\n", wastedVolume, (wastedVolume * 100.0) / (stacks * maxStackHeight));
    printf("Stack height percentages:\n");
    
    for (int i = 0; i < stacks; i++) {
        printf("%.1f%% ", (stackHeights[i] * 100.0) / maxStackHeight);
    }
    printf("\n");

    displayStacks(stackHeights, stacks);

    free(stackHeights);

    return 0;
}