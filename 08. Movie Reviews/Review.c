//Adam Fenjiro
//afenjiro@mtu.edu
//Program 8: Movie Reviews
//Review.c

#include "Review.h"
#include <stdlib.h>
#include <string.h>

bool reviewInit(Review* review, FILE* stream) {
    if (fscanf(stream, "%d", &(review->score)) != 1) {
        return false;
    }
    if (fscanf(stream, "%d", &(review->numWords)) != 1) {
        return false;
    }

    review->words = (char**)malloc(review->numWords * sizeof(char*));
    if (review->words == NULL) {
        return false;
    }

    for (int i = 0; i < review->numWords; ++i) {
        review->words[i] = (char*)malloc((MAX_WORD_LENGTH + 1) * sizeof(char));
        if (review->words[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(review->words[j]);
            }
            free(review->words);
            return false;
        }
        if (fscanf(stream, SCANF_MAX_WORD, review->words[i]) != 1) {
            for (int j = 0; j <= i; ++j) {
                free(review->words[j]);
            }
            free(review->words);
            return false;
        }
    }

    return true;
}

void reviewUninit(Review* review) {
    if (review != NULL) {
        if (review->words != NULL) {
            for (int i = 0; i < review->numWords; i++) {
                free(review->words[i]);
            }
            free(review->words);
        }
        review->words = NULL;
        review->numWords = 0;
    }
}

bool reviewMatches(const Review* review, const char* word) {
    for (int i = 0; i < review->numWords; ++i) {
        if (strcmp(review->words[i], word) == 0) {
            return true;
        }
    }
    return false;
}

void reviewPrint(const Review* review) {
    for (int i = 0; i < review->numWords; ++i) {
        printf("%s", review->words[i]);
        if (i != review->numWords - 1) {
            printf(" ");
        }
    }
}
