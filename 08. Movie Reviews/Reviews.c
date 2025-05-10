//Adam Fenjiro
//afenjiro@mtu.edu
//Program 8: Movie Reviews
//Reviews.c

#include "Reviews.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reviewsInit(Reviews* reviews, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    if (fscanf(file, "%d", &(reviews->size)) != 1) {
        fclose(file);
        return 0;
    }

    reviews->items = (Review*)malloc(reviews->size * sizeof(Review));
    if (reviews->items == NULL) {
        fclose(file);
        return 0;
    }

    int reviewsLoaded = 0;
    for (int i = 0; i < reviews->size; ++i) {
        if (reviewInit(&(reviews->items[i]), file)) {
            reviewsLoaded++;
        } else {
            break;
        }
    }

    fclose(file);

    return reviewsLoaded;
}

void reviewsUninit(Reviews* reviews) {
    if (reviews != NULL) {
        if (reviews->items != NULL) {
            for (int i = 0; i < reviews->size; i++) {
                reviewUninit(&(reviews->items[i]));
            }
            free(reviews->items);
        }
        reviews->items = NULL;
        reviews->size = 0;
    }
}

void reviewsSearch(const Reviews* reviews, const char* word, int* matched, double* avgScore) {
    *matched = 0;
    *avgScore = -1.0;

    double totalScore = 0.0;
    int totalMatches = 0;

    for (int i = 0; i < reviews->size; ++i) {
        if (reviewMatches(&(reviews->items[i]), word)) {
            (*matched)++;
            totalScore += reviews->items[i].score;
            totalMatches++;
        }
    }

    if (totalMatches > 0) {
        *avgScore = totalScore / totalMatches;
    }
}
