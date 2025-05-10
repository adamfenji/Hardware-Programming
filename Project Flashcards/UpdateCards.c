// Adam Fenjiro: afenjiro@mtu.edu
// CS1142, Program 2. UpdateCards.c
// 12/12/23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CARD_LEN 255

void lowercase(char *str) {
    for (int i = 0; str[i]; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = tolower(str[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    int mode = 0; // Default mode

    if (argc == 2) {
        mode = atoi(argv[1]);
        if (mode < 0 || mode > 3) {
            printf("Invalid mode. Please use mode 0, 1, 2, or 3.\n");
            return 1;
        }
    }

    int numCards;
    scanf("%d", &numCards);

    printf("%d\n", mode > 0 ? numCards * 2 : numCards);

    for (int i = 0; i < numCards; ++i) {
        char front[MAX_CARD_LEN + 1], back[MAX_CARD_LEN + 1];
        int stack, correct, incorrect;

        scanf("%s %s %d %d %d", front, back, &stack, &correct, &incorrect);

        lowercase(front);
        lowercase(back);

        printf("%s %s %d %d %d\n", front, back, stack, correct, incorrect);

        if (mode > 0) {
            int revCorrect = (mode == 1 || mode == 2) ? 0 : correct;
            int revIncorrect = (mode == 1 || mode == 2) ? 0 : incorrect;

            printf("%s %s %d %d %d\n", back, front, stack, revCorrect, revIncorrect);
        }
    }

    return 0;
}