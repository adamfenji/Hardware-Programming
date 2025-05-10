// Adam Fenjiro: afenjiro@mtu.edu
// CS1142, Program 2. Quiz.c
// 12/12/23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Card.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: Quiz <in filename> <attempts> [out filename]\n");
        exit(1);
    }

    FILE *cardsFile = fopen(argv[1], "r");
    if (cardsFile == NULL) {
        printf("ERROR: failed to open input file!\n");
        exit(1);
    }

    int numCards;
    fscanf(cardsFile, "%d", &numCards);
    Card *cards = (Card *)malloc(numCards * sizeof(Card));

    for (int i = 0; i < numCards; ++i) {
        char front[MAX_CARD_LEN + 1];
        char back[MAX_CARD_LEN + 1];
        int stack, correct, incorrect;
        fscanf(cardsFile, "%s %s %d %d %d", front, back, &stack, &correct, &incorrect);
        initCard(&cards[i], front, back, stack, correct, incorrect);
    }
    fclose(cardsFile);

    int attempts = atoi(argv[2]);
    if (attempts <= 0) {
        printf("ERROR: attempts must be positive!\n");
        for (int i = 0; i < numCards; ++i) {
            uninitCard(&cards[i]);
        }
        free(cards);
        return 1;
    }

    char answer[MAX_CARD_LEN + 1];
    int correctAnswers = 0;
    int totalQuestions = 0;

    while (totalQuestions < attempts) {
        for (int i = 0; i < numCards; ++i) {
            if (!cards[i].seen) {
                printCard(&cards[i], false);
                printf("Enter your answer: ");
                fgets(answer, MAX_CARD_LEN, stdin);
                answer[strcspn(answer, "\n")] = '\0'; // Remove newline character

                if (checkAndUpdateCard(&cards[i], answer)) {
                    correctAnswers++;
                }
                totalQuestions++;

                if (totalQuestions >= attempts) break;
            }
        }
    }

    printf("Quiz Results:\n");
    printf("Correct Answers: %d/%d\n", correctAnswers, totalQuestions);
    printf("Percentage Correct: %.2f%%\n", (double)correctAnswers / totalQuestions * 100.0);

    for (int i = 0; i < numCards; ++i) {
        uninitCard(&cards[i]);
    }
    free(cards);

    return 0;
}
