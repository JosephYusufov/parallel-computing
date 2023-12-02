#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string.h>

int main(int argc, char *argv[])
{
    double start, end;
    int n, t;

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

#pragma omp parallel for num_threads(t) schedule(static, 64)
    for (int i = 2; i <= n; i++)
    { // for all numbers i from 2 to n
        for (int j = 2; !A[i] && (j <= largest_divisor) && j < i; j++)
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

    printf("%lf\n", (end - start) * 1000.00);

    free(A);
    free(filename);
    fclose(fp);
    return 0;
}