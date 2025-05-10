//Adam Fenjiro
//afenjiro@mtu.edu
//Program 8: Movie Reviews
//ScoreWords.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Reviews.h"

#define MAX_WORDS 100

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ScoreWords <reviews file> <word1> [word2] ...\n");
        return 1;
    }

    Reviews reviews;
    int loaded = reviewsInit(&reviews, argv[1]);
    if (loaded == 0) {
        printf("Failed to load reviews from '%s'\n", argv[1]);
        return 1;
    }

    printf("Loaded %d reviews\n", loaded);

    int matched[MAX_WORDS] = {0};
    double avgScore[MAX_WORDS] = {0};

    for (int i = 2; i < argc; i++) {
        reviewsSearch(&reviews, argv[i], &matched[i-2], &avgScore[i-2]);

        if(avgScore[i-2] == -1){
            printf("'%s' in %d reviews\n", argv[i], matched[i-2]);
        }
        else{
            printf("'%s' in %d reviews, avg score %.3f\n", argv[i], matched[i-2], avgScore[i-2]);
        }

    }

    reviewsUninit(&reviews);

    return 0;
}
