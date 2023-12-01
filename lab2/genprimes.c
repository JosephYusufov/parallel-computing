#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const int MAX_PRINT_LENGTH = 0;
    double start, end, local_time, elapsed;
    int n, t, k;
    int my_rank, comm_sz;

    if (argc < 3)
    {
        printf("Provide values for n and t.\n");
        return 1;
    }

    n = atoi(argv[1]);
    t = atoi(argv[2]);
    if (n <= 2)
    {
        printf("n must be greater than 2\n");
        return 1;
    }

    // Using A as a bit-array to make this conceptually easier.
    // 0: Prime
    // 1: Not a prime
    char *A = calloc(n + 1, sizeof(char));
    int largest_divisor = (int)floor((n + 1) / 2);

    start = omp_get_wtime();
    // For each factor from 2 to (n+1)/2
    /*
    #pragma omp parallel for num_threads(t) schedule(static, 1)
        for (int i = 2; i < (int)floor((n + 1) / 2); i++)
        {
            // if i is still in the list (i.e. assumed to be prime)
            if (!A[i])
            {
                // For each number from i until n
                for (int j = i + 1; j <= n; j++)
                {
                    // if the bit is unset (j is assumed prime) AND i is a factor of j, set the bit
                    // printf("A[%d] = %d\n", j, A[j]);
                    if (!A[j] && j % i == 0)
                    {
                        // printf("setting bit %d\n", j);
                        A[j] = 1;
                    }
                }
            }
        }
    */

#pragma omp parallel for num_threads(t) schedule(static, 1)
    for (int i = 2; i <= n; i++)
    { // for all numbers i from 2 to n
        for (int j = 2; (j <= largest_divisor) && j < i; j++)
        { // for all divisors j from 2 to (n+1)/2
            if (!(i % j))
            { // if i is divisible by j
                A[i] = 1;
            }
        }
    }

    end = omp_get_wtime();

    char *filename = (char *)malloc((strlen(argv[1]) + 4) * sizeof(char));
    strcpy(filename, argv[1]);
    strcat(filename, ".txt");
    FILE *fp = fopen(filename, "w+");
    for (int i = 2; i <= n; i++)
    {
        if (!A[i])
            fprintf(fp, "%d ", i);
    }
    fprintf(fp, "\n");

    int elements_to_print = n > MAX_PRINT_LENGTH ? MAX_PRINT_LENGTH : n;
    for (int i = 2; i <= elements_to_print; i++)
    {
        if (!A[i])
            printf("%d ", i);
    }
    if (MAX_PRINT_LENGTH)
        printf("\n");
    printf("time: %lfms\n", (end - start) * 1000.00);

    free(A);
    return 0;
}