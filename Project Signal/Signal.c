// Adam Fenjiro
// afenjiro@mtu.edu
// CS1142 Spring 24
// Project 2: Signal.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Represents a contiguous run in a sample sequence with the same value
// DO NOT MODIFY
typedef struct
{
    int value;      // Sample value of the contiguous run
    int startIndex; // Starting index of the run
    int endIndex;   // Ending index of the run
} SampleRun;

// Stores various statistics about a sequence of samples
// DO NOT MODIFY
typedef struct
{
    double seconds;             // Length of sequence in seconds
    int minValue;               // Min sample observed in sequence
    int maxValue;               // Max sample observed in sequence
    double avgAmplitudePercent; // Avg absolute value of samples, as a percent of 128
    double nearZeroPercent;     // Percent of samples close to 0
    double clippedPercent;      // Percent of samples at max positive or min negative value
    SampleRun longestRun;       // Longest run of samples with the same value
} SampleStats;

void printSignal(int numSamples, const signed char samples[numSamples], int maxPerLine)
{
    for (int i = 0; i < numSamples; i++)
    {
        printf("%5d", samples[i]);
        if ((i + 1) % maxPerLine == 0 || i == numSamples - 1)
        {
            printf("\n");
        }
    }
}

// Exact function signature is up to you, but it should be named: printStats
// This function should only print things based on the values in a SampleStats struct.
// It should not calculate things, that's the job of getStats
void printStats(const SampleStats *stats)
{
    printf("Seconds: %.2f\n", stats->seconds);
    printf("Sample range: [%d, %d]\n", stats->minValue, stats->maxValue);
    printf("Average amplitude: %.1f%%\n", stats->avgAmplitudePercent);
    printf("Near zero: %.1f%%\n", stats->nearZeroPercent);
    printf("Clipped: %.1f%%\n", stats->clippedPercent);
    printf("Longest run: value of %d from sample %d to %d\n", stats->longestRun.value, stats->longestRun.startIndex, stats->longestRun.endIndex);
}

// Exact function signature is up to you, but it should be named: getStats
// This function calculates the values contained in a SampleStats stuct
// based on a passed in sequence of samples at a specified sampleing rate.
// It should not print things, that's the job of printStats
void getStats(const signed char *samples, int numSamples, int samplingRate, SampleStats *stats)
{
    stats->seconds = (double)numSamples / samplingRate;

    stats->minValue = samples[0];
    stats->maxValue = samples[0];
    for (int i = 1; i < numSamples; i++)
    {
        if (samples[i] < stats->minValue)
            stats->minValue = samples[i];
        if (samples[i] > stats->maxValue)
            stats->maxValue = samples[i];
    }

    double sum = 0.0;
    for (int i = 0; i < numSamples; i++)
    {
        int absSample = abs(samples[i]);
        sum += absSample;
    }
    stats->avgAmplitudePercent = (sum / numSamples) / 128 * 100;

    int nearZeroCount = 0;
    for (int i = 0; i < numSamples; i++)
    {
        if (abs(samples[i]) <= 2)
            nearZeroCount++;
    }
    stats->nearZeroPercent = (double)nearZeroCount / numSamples * 100;

    int clippedCount = 0;
    for (int i = 0; i < numSamples; i++)
    {
        if (samples[i] == 127 || samples[i] == -128)
            clippedCount++;
    }
    stats->clippedPercent = (double)clippedCount / numSamples * 100;

    int longestRunLength = 0;
    int currentRunLength = 0;
    int longestRunStart = 0;
    int currentRunStart = 0;
    int longestRunValue = samples[0];
    for (int i = 1; i < numSamples; i++)
    {
        if (samples[i] == samples[i - 1])
        {
            currentRunLength++;
            if (currentRunLength > longestRunLength)
            {
                longestRunLength = currentRunLength;
                longestRunStart = currentRunStart;
                longestRunValue = samples[i];
            }
        }
        else
        {
            currentRunStart = i;
            currentRunLength = 0;
        }
    }
    stats->longestRun.value = longestRunValue;
    stats->longestRun.startIndex = longestRunStart;
    stats->longestRun.endIndex = longestRunStart + longestRunLength;
}

// For full credit, this function should not print anything.
// Instead your main function should call the print function you implemented in part 2.
// It returns the smoothed buffer as the function's return value.
// The size of the smoothed buffer is passed back in the numResultSamples parameter.
signed char *smoothSignal(int numSamples, const signed char samples[numSamples], int windowSize, int *numResultSamples)
{

    *numResultSamples = (numSamples + windowSize - 1) / windowSize;
    signed char *result = (signed char *)malloc(*numResultSamples * sizeof(signed char));
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < *numResultSamples; i++)
    {
        int sum = 0;
        int count = 0;
        for (int j = i * windowSize; j < (i + 1) * windowSize && j < numSamples; j++)
        {
            sum += samples[j];
            count++;
        }
        result[i] = round((double)sum / count);
    }
    return result;
}

// Read in signed character data from the specified filename.
// Returns pointer to array containing the signal data.
// Returns NULL on failure to open file or allocate memory.
// Returns samples read in in numSamples parameter.
// Caller is responsible for freeing returned buffer.
signed char *readSignalFile(const char *filename, int *numSamples)
{
    *numSamples = 0;

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        // printf("ERROR: Unable to open file '%s' for reading.\n", filename);
        return NULL;
    }

    int capacity = 256;
    signed char *samples = malloc(capacity * sizeof(signed char));
    if (samples == NULL)
    {
        printf("ERROR: Memory allocation failed.\n");
        fclose(fp);
        return NULL;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        samples[*numSamples] = ch;
        (*numSamples)++;

        if (*numSamples >= capacity)
        {
            capacity *= 2;
            signed char *samplesNew = realloc(samples, capacity * sizeof(signed char));
            if (samplesNew == NULL)
            {
                printf("ERROR: Failed to reallocate memory.\n");
                free(samples);
                fclose(fp);
                return NULL;
            }
            samples = samplesNew;
        }
    }

    printf("Read %d samples from '%s'\n", *numSamples, filename);

    fclose(fp);
    return samples;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: Signal <filename> [command] [...]\n");
        printf("Commands:\n");
        printf("  print      [max per line, default 14]\n");
        printf("  stats      <sampling rate>\n");
        printf("  smooth     <window size>\n");
        return 0;
    }

    char *filename = argv[1];
    int numSamples = 0;
    signed char *samples = readSignalFile(filename, &numSamples);

    if (samples == NULL)
    {
        printf("ERROR: failed to read samples!\n");
        return 1;
    }

    if (argc < 3)
    {
        printf("ERROR: failed to read samples!\n");
        free(samples);
        return 1;
    }

    if (strcmp(argv[2], "print") == 0)
    {
        int maxPerLine = 14;
        if (argc >= 4)
        {
            maxPerLine = atoi(argv[3]);
            if (maxPerLine <= 0)
            {
                printf("ERROR: print requires positive max per line!\n");
                free(samples);
                return 1;
            }
        }
        printSignal(numSamples, samples, maxPerLine);
    }
    else if (strcmp(argv[2], "stats") == 0)
    {
        if (argc < 4)
        {
            printf("ERROR: stats requires positive sampling rate!\n");
            free(samples);
            return 1;
        }
        int samplingRate = atoi(argv[3]);
        if (samplingRate <= 0)
        {
            printf("ERROR: stats requires positive sampling rate!\n");
            free(samples);
            return 1;
        }
        SampleStats stats;
        getStats(samples, numSamples, samplingRate, &stats);
        printStats(&stats);
    }
    else if (strcmp(argv[2], "smooth") == 0)
    {
        if (argc < 4)
        {
            printf("ERROR: smooth requires positive window size!\n");
            free(samples);
            return 1;
        }
        int windowSize = atoi(argv[3]);
        if (windowSize <= 0)
        {
            printf("ERROR: smooth requires positive window size!\n");
            free(samples);
            return 1;
        }
        int numResultSamples;
        signed char *smoothed = smoothSignal(numSamples, samples, windowSize, &numResultSamples);
        printSignal(numResultSamples, smoothed, 14);
        free(smoothed);
    }
    else
    {
        printf("ERROR: invalid command '%s'!\n", argv[2]);
        free(samples);
        return 1;
    }

    free(samples);
    return 0;
}