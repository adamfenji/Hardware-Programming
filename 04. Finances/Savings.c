//Adam Fenjiro, afenjiro@mtu.edu
//Program 4: Savings.c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc != 5) {
        printf("Usage: Savings <account> <amount> <rate> <months>\n");
        return 1;
    }

    // get the variable
    char *account = argv[1];
    double amount = strtod(argv[2], NULL);
    double rate = strtod(argv[3], NULL);
    int months = atoi(argv[4]);

    // ammount must be positive
    if (amount <= 0) {
        printf("ERROR: amount must be positive!\n");
        return 1;
    }

    // months must be valid
    if (months <= 0) {
        months = 0;
    }

    // print initial deposit
    printf("Deposited $%.2f into %s\n", amount, account);

    // calculate interest + print monthly details
    for (int i = 1; i <= months; i++) {
        double interest = amount * rate / 1200.0; // Adjust for rate as percentage
        amount += interest;
        if (months > 0) { // Only print for positive months
            printf("Month %d, $%.2f change, new total $%.2f\n", i, interest, amount);
        }
    }

    // calculate + print relative change
    double initialAmount = strtod(argv[2], NULL);
    double finalAmount = amount;
    double relativeChange = ((finalAmount - initialAmount) / initialAmount) * 100.0;
    printf("Relative change: %.2f%%\n", relativeChange);

    return 0;
}