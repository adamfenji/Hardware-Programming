//Adam Fenjiro, afenjiro@mtu.edu
//Program 4: Invest.c

#include <stdio.h>
#include <stdlib.h>

int main() {
    int numDays;
    double *prices;

    // check number of days
    if (scanf("%d", &numDays) != 1 || numDays <= 1) {
        printf("ERROR: requires at least 2 days of data!\n");
        return 1;
    }

    // allocate memory for prices
    prices = calloc(numDays, sizeof(double));
    if (!prices) {
        printf("ERROR: memory allocation failed!\n");
        return 1;
    }

    // get prices
    for (int i = 0; i < numDays; i++) {
        if (scanf("%lf", &prices[i]) != 1 || prices[i] <= 0) {
            printf("ERROR: prices must be positive!\n");
            free(prices);
            return 1;
        }
    }

    // get min, max, and avg price
    int minDay = 0, maxDay = 0;
    double minPrice = prices[0], maxPrice = prices[0], avgPrice = 0;

    for (int i = 0; i < numDays; i++) {
        if (prices[i] < minPrice) {
            minPrice = prices[i];
            minDay = i;
        } else if (prices[i] > maxPrice) {
            maxPrice = prices[i];
            maxDay = i;
        }
        avgPrice += prices[i];
    }
    avgPrice /= numDays;

    printf("Read %d days\n", numDays);
    printf("Min price $%.2f on day %d\n", minPrice, minDay + 1);
    printf("Max price $%.2f on day %d\n", maxPrice, maxDay + 1);
    printf("Avg price $%.2f\n", avgPrice);

    // simulate buy sell trades
    int bestBuy = 0, bestSell = 0, worstBuy = 0, worstSell = 0;
    double bestGain = 0, worstGain = 0, totalGain = 0;
    int numTrades = 0;

    for (int buyDay = 0; buyDay < numDays - 1; buyDay++) {
        for (int sellDay = buyDay + 1; sellDay < numDays; sellDay++) {
            double gain = (prices[sellDay] - prices[buyDay]) / prices[buyDay] * 100;
            totalGain += gain;
            numTrades++;

            if (gain > bestGain || (gain == bestGain && buyDay < bestBuy)) {
                bestGain = gain;
                bestBuy = buyDay;
                bestSell = sellDay;
            }

            if (gain < worstGain || (gain == worstGain && buyDay < worstBuy)) {
                worstGain = gain;
                worstBuy = buyDay;
                worstSell = sellDay;
            }
        }
    }

    double avgGain = totalGain / numTrades;

    printf("Simulated %d possible trades\n", numTrades);
    printf("Average case, %.2f%%\n", avgGain);
    printf("Best case, buy day %d, sell day %d, %.2f%%\n", bestBuy + 1, bestSell + 1, bestGain);
    printf("Worst case, buy day %d, sell day %d, %.2f%%\n", worstBuy + 1, worstSell + 1, worstGain);

    // free memory
    free(prices);

    return 0;
}