#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string.h>

void generate_command_string(int n, int threads, char *s)
{
    // strcpy(s, "./genprimes ");
    // strcpy(s, );
    sprintf(s, "./genprimes %d %d\0", n, threads);
}

int main(int argc, char *argv[])
{
    int const PATH_MAX = 12;
    int const CMD_MAX = 50;
    int status;
    if (argc < 2)
    {
        printf("Provide a value for max_prob_size.\n");
        return 1;
    }
    int max_prob_size = atoi(argv[1]);
    if (max_prob_size < 0 || max_prob_size > 4)
    {
        printf("max_prob_size must be an integer between 0 and 4, inclusive.\n");
        return 1;
    }

    // thread(1, 2, 5, 10) x n(1k, 10k, 100k, 1mn, 10mn)
    double times[4][5] = {0};
    double speedups[4][5] = {0};
    double efficiencies[4][5] = {0};
    int threads[4] = {1, 2, 5, 10};
    int n[5] = {1000, 10000, 100000, 1000000, 10000000};

    for (int i = 0; i < 4; i++)
    { // for each thread count
        for (int j = 0; j <= max_prob_size; j++)
        { // for each problem size
            char path[PATH_MAX];
            char command[CMD_MAX];
            generate_command_string(n[j], threads[i], command);
            FILE *fp = popen(command, "r");
            if (fp == NULL)
                return 1;

            while (fgets(path, PATH_MAX, fp) != NULL)
            {
                times[i][j] = atof(path);
            }
            status = pclose(fp);
            if (status == -1)
            {
                return 1;
            }
        }
    }

    // calculating speedup  & efficiency
    for (int i = 0; i < 4; i++)
    { // threads
        for (int j = 0; j <= max_prob_size; j++)
        { // n
            speedups[i][j] = times[0][j] / times[i][j];
            efficiencies[i][j] = speedups[i][j] / threads[i];
        }
    }

    printf("Time (ms)\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%2d: ", threads[i]);
        for (int j = 0; j <= max_prob_size; j++)
        {
            printf("%12f ", times[i][j]);
        }
        printf("\n");
    }

    printf("Speedup\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%2d: ", threads[i]);
        for (int j = 0; j <= max_prob_size; j++)
        {
            printf("%12f ", speedups[i][j]);
        }
        printf("\n");
    }

    printf("Efficiency\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%2d: ", threads[i]);
        for (int j = 0; j <= max_prob_size; j++)
        {
            printf("%12f ", efficiencies[i][j]);
        }
        printf("\n");
    }

    // system("./genprimes 1000 1");
    return 0;
}