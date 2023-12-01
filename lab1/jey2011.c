#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

void print_histogram(int *hist)
{
	int i;
	int factors[5] = {2, 3, 5, 7, 13};
	for (i = 0; i < 4; i++)
	{
		printf("%d:  %d\n", factors[i], hist[i]);
	}
	printf("%d: %d\n", factors[4], hist[4]);
}

int main(int argc, char *argv[])
{

	double start, end, local_time, elapsed;
	int n, k;
	int my_rank, comm_sz;

	if (argc != 2)
	{
		printf("You need to enter the end number of the range\n");
		return 1;
	}

	n = atoi(argv[1]);

	if (n <= 1)
	{
		printf("n must be greater than one\n");
		return 1;
	}
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();

	/* code to be timed is here */

	k = (int)(((n - 1) + (comm_sz - 1)) / comm_sz);
	int local_hist_start = 2 + my_rank * k;
	int local_hist_end = local_hist_start + k;
	if (local_hist_end > n + 1)
	{
		local_hist_end = n + 1;
	}
	int factors[5] = {2, 3, 5, 7, 13};
	int local_hist[5] = {0};
	int i;
	for (i = local_hist_start; i < local_hist_end; i++)
	{
		int j;
		for (j = 0; j < 5; j++)
		{
			if (i % factors[j] == 0)
			{
				local_hist[j]++;
			}
		}
	}

	// Reduce all of the local histograms into the global histogram
	int global_hist[5] = {0};
	for (int i = 0; i < 5; i++)
	{
		MPI_Reduce(&local_hist[i], &global_hist[i], 1, MPI_INT, MPI_SUM, 0,
				   MPI_COMM_WORLD);
	}

	end = MPI_Wtime();
	local_time = end - start;
	/* Assuming process 0 will end up having the time elapsed to be measured. You can change that if you want. */
	MPI_Reduce(&local_time, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	/* print time taken as well as the historgran ib the screen */
	if (my_rank == 0)
	{
		printf("Time taken: %f\n", elapsed);
		print_histogram(global_hist);
	}

	MPI_Finalize();
	return 0;
}