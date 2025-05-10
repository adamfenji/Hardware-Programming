// Adam Fenjiro: afenjiro@mtu.edu
// CS1142, Program 2. Cards.c
// 12/12/23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Card.h"

void initCard(Card *card, const char *front, const char *back, int stack, int correct, int incorrect) {
    card->front = malloc(strlen(front) + 1);
    card->back = malloc(strlen(back) + 1);

    if (card->front && card->back) {
        strcpy(card->front, front);
        strcpy(card->back, back);
    }

    card->stack = stack;
    card->correct = correct;
    card->incorrect = incorrect;
    card->seen = 0;
}

void uninitCard(Card *card) {
    if (card) {
        free(card->front);
        free(card->back);
    }
}

double correctPercentCard(const Card *card) {
    if (card->correct + card->incorrect == 0) {
        return 0.0;
    }
    return (double)card->correct / (card->correct + card->incorrect) * 100.0;
}

void printCard(const Card *card, bool verbose) {
    printf("%s -> %s, stack=%d", card->front, card->back, card->stack);
    if (verbose) {
        printf(", correct=%d, incorrect=%d, seen=%d", card->correct, card->incorrect, card->seen);
    }
    printf("\n");
}

bool checkAndUpdateCard(Card *card, const char *answer) {
    char lowerAnswer[MAX_CARD_LEN + 1];
    char lowerBack[MAX_CARD_LEN + 1];

    strcpy(lowerAnswer, answer);
    strcpy(lowerBack, card->back);

    for (int i = 0; lowerAnswer[i]; ++i) {
        lowerAnswer[i] = tolower(lowerAnswer[i]);
    }

    for (int i = 0; lowerBack[i]; ++i) {
        lowerBack[i] = tolower(lowerBack[i]);
    }

    card->seen++;

    if (strcmp(lowerAnswer, lowerBack) == 0) {
        card->correct++;
        if (card->stack < NUM_STACKS - 1) {
            card->stack++;
        }
        return true;
    } else {
        card->incorrect++;
        if (card->stack > 0) {
            card->stack--;
        }
        return false;
    }
}
