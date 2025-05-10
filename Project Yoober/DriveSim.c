//Adam Fenjiro
//afenjiro@mtu.edu
//Project 1 - Yoober
//DriveSim.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_LOCATIONS 100

bool validDistanceMatrix(int size, int dist[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (dist[i][j] != dist[j][i]) {
                return false;
            }
        }
    }
    for (int i = 0; i < size; i++) {
        if (dist[i][i] != 0) {
            return false;
        }
        for (int j = 0; j < size; j++) {
            if (i != j && dist[i][j] < 1) {
                return false;
            }
        }
    }
    if (size < 2) {
        return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: DriveSim <mpg> <gas price> <max passengers> <distance file>\n");
        return 1;
    }

    float mpg = atof(argv[1]);
    float gas_price = atof(argv[2]);
    int max_passengers = atoi(argv[3]);
    char *distance_file = argv[4];

    if (mpg <= 0 || gas_price <= 0 || max_passengers <= 0) {
        printf("ERROR: invalid input!\n");
        return 1;
    }

    FILE *file = fopen(distance_file, "r");
    if (file == NULL) {
        printf("ERROR: failed to open distance file!\n");
        return 1;
    }

    int num_locations;
    fscanf(file, "%d", &num_locations);
    if (num_locations <= 0 || num_locations > MAX_LOCATIONS) {
        printf("ERROR: invalid number of locations in distance file!\n");
        return 1;
    }

    int distances[MAX_LOCATIONS][MAX_LOCATIONS];
    for (int i = 0; i < num_locations; i++) {
        for (int j = 0; j < num_locations; j++) {
            fscanf(file, "%d", &distances[i][j]);
        }
    }

    printf("Read %d distances from '%s'\n", num_locations * num_locations, distance_file);

    // if (!validDistanceMatrix(num_locations, distances)) {
    //     printf("ERROR: invalid distance matrix!\n");
    //     return 1;
    // }

    int trip_number = 0;
    int total_fare_miles = 0;
    int total_transit_miles = 0;
    float total_profit = 0.0;
    int prev_dropoff = -1;

    printf("Trip #%d: ", trip_number);
    int pickup, dropoff, passengers, surge;
    while (scanf("%d %d %d %d", &pickup, &dropoff, &passengers, &surge) == 4) {
        if (pickup < 0 || pickup >= num_locations || dropoff < 0 || dropoff >= num_locations || pickup == dropoff) {
            printf("Invalid input!\n");
            trip_number++;
            printf("Trip #%d: ", trip_number);
            continue;
        }

        if (passengers <= 0 || passengers > max_passengers) {
            printf("Car too small!\n");
            trip_number++;
            printf("Trip #%d: ", trip_number);
            continue;
        }

        int trip_distance = distances[pickup][dropoff];
        if (trip_distance == 0) {
            printf("Invalid input!\n");
            trip_number++;
            printf("Trip #%d: ", trip_number);
            continue;
        }

        int transit_distance = (prev_dropoff != -1) ? distances[prev_dropoff][pickup] : 0;
        float fare = (5.0 + 0.1 * trip_distance) * (surge ? 1.5 : 1.0);
        float expense = trip_distance / mpg * gas_price;
        float profit = fare - expense;

        printf("%d -> %d, transit %d, trip %d, fare $%.2f, profit $%.2f\n", pickup, dropoff, transit_distance, trip_distance, fare, profit);

        total_fare_miles += trip_distance;
        total_transit_miles += transit_distance;
        total_profit += profit;
        prev_dropoff = dropoff;
        trip_number++;
        printf("Trip #%d: ", trip_number);
    }

    printf("\nTotal fare miles %d\n", total_fare_miles);
    printf("Total transit miles %d\n", total_transit_miles);
    printf("Total profit $%.2f\n", total_profit);

    fclose(file);
    return 0;
}
