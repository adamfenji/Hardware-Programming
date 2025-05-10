//Adam Fenjiro
//afenjiro@mtu.edu
//Program 5 - GA

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

//function calculate fitness of an individual
int calculate_fitness(int individual[], int coefficients[], int num_coefficients, int target_value)
{
    int sum = 0;
    for (int i = 0; i < num_coefficients; i++)
    {
        sum += individual[i] * coefficients[i];
    }
    return abs(sum - target_value);
}

int main(int argc, char *argv[])
{
    //print instructions
    if (argc < 5 || argc > 6)
    {
        printf("Usage: GA <individuals> <max steps> <seed> <in file> [out file]\n");
        return 1;
    }

    int individuals = atoi(argv[1]);
    int max_steps = atoi(argv[2]);
    int seed = atoi(argv[3]);
    char *infile_name = argv[4];    char *outfile_name = argc == 6 ? argv[5] : NULL;

    //check num_individuals
    if (individuals <= 0)
    {
        printf("ERROR: individuals must be positive!\n");
        return 1;
    }

    //seed random num gen
    srand(seed);

    //open input file
    FILE *infile = fopen(infile_name, "r");
    if (infile == NULL)
    {
        printf("ERROR: failed to open in file!\n");
        return 1;
    }

    //get target value and number of coefficients from input file
    int target_value;
    fscanf(infile, "%d", &target_value);

    int num_coefficients;
    fscanf(infile, "%d", &num_coefficients);

    //get coefficients from input file
    int coefficients[num_coefficients];
    for (int i = 0; i < num_coefficients; i++)
    {
        fscanf(infile, "%d", &coefficients[i]);
    }

    //close input file
    fclose(infile);

    //print equation
    printf("%d*x_0", coefficients[0]);
    for (int i = 1; i < num_coefficients; i++)
    {
        printf("+ %d*x_%d", coefficients[i], i);
    }
    printf(" = %d\n", target_value);

    //for population
    int population[individuals][num_coefficients];
    for (int i = 0; i < individuals; i++)
    {
        for (int j = 0; j < num_coefficients; j++)
        {
            population[i][j] = rand() % 10;
        }
    }

    //for best individual and fitness
    int best_individual[num_coefficients];
    int best_fitness = INT_MAX;
    int best_steps = 0;
    int best_generation = 0;

    //main loop for evolution steps
    for (int generation = 0; generation <max_steps; generation++)
    {
        int individual_index = rand() % individuals;
        int gene_index = rand() % num_coefficients;
        int new_gene_value = rand() % 10;
        population[individual_index][gene_index] = new_gene_value;

        int min_fitness = INT_MAX;
        for (int i = 0; i < individuals; i++)
        {
            int fitness = calculate_fitness(population[i], coefficients, num_coefficients, target_value);
            if (fitness < min_fitness)
            {
                min_fitness = fitness;
            }
        }

        if (min_fitness < best_fitness)
        {
            best_fitness = min_fitness;
            best_generation = generation;
            best_steps = generation + 1;
        }

        if (min_fitness == 0)
        {
            break;
        }
    }

    //find the best individual
    for (int i = 0; i < individuals; i++)
    {
        int fitness = calculate_fitness(population[i], coefficients, num_coefficients, target_value);
        if (fitness == best_fitness)
        {
            for (int j = 0; j < num_coefficients; j++)
            {
                best_individual[j] = population[i][j];
            }
            break;
        }
    }

    //print the best individual and fitness and steps
    printf("BEST %d: ", best_generation);
    for (int i = 0; i < num_coefficients; i++)
    {
        printf("%d", best_individual[i]);
    }
    printf(", fitness=%d,steps=%d\n", best_fitness, best_steps);

    return 0;
}