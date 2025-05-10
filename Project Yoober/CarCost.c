//Adam Fenjiro
//afenjiro@mtu.edu
//Project 1 - Yoober
//CarCost.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Usage: CarCost <name> <cost> <mpg> <gas price> <repair every> <total miles>\n");
        return 1;
    }

    char *name = argv[1];
    float cost = atof(argv[2]);
    float mpg = atof(argv[3]);
    float gas_price = atof(argv[4]);
    int repair_every = atoi(argv[5]);
    int total_miles = atoi(argv[6]);

    if (cost <= 0 || mpg <= 0 || gas_price <= 0 || repair_every <= 0 || total_miles <= 0) {
        printf("ERROR: invalid input!\n");
        return 1;
    }

    int num_repairs = ceil((float)total_miles / repair_every);
    float gas_cost = (float)total_miles / mpg * gas_price;
    float repair_cost = (float)num_repairs * 500.0;
    float total_cost = cost + gas_cost + repair_cost;
    float cost_per_mile = total_cost / total_miles;

    printf("Buying %s for $%.0f getting %.1f mpg\n", name, cost, mpg);
    printf("Driving %d miles @ $%.2f/gallon\n", total_miles, gas_price);
    printf("Burned %d gallons costing $%.2f\n", (int)ceil((float)total_miles / mpg), gas_cost);
    printf("Repaired %d times costing $%.2f\n", num_repairs, repair_cost);
    printf("Total cost of ownership: $%.2f\n", total_cost);
    printf("Cost per mile: $%.2f\n", ceil(cost_per_mile * 100.0) / 100.0);

    return 0;
}