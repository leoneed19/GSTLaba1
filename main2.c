#include "mpi.h"

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>
#include <time.h>

int gcd(int a, int b) {

    return( b != 0 ? gcd(b, a % b) : a);

}

int main(int argc, char **argv) {

    int numtasks, rank, rc, i, gcdv;

    int *sbuf, rbuf[2], result;

    if((rc = MPI_Init(&argc, &argv)) != MPI_SUCCESS) {

        fprintf(stderr, "Error starting MPI program. Terminating.\n");

        MPI_Abort(MPI_COMM_WORLD, rc);

    }

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {

        printf("Number of tasks=%d\n", numtasks);

        sbuf = (int *)malloc(numtasks * sizeof(int) * 2);

        srand(time(NULL));

        for(i=0; i < numtasks * 2; i++) sbuf[i] = rand() % 10000;

    }

    MPI_Scatter(sbuf, 2, MPI_INT, rbuf, 2, MPI_INT, 0, MPI_COMM_WORLD);

    gcdv = gcd(rbuf[0], rbuf[1]);

    printf("My rank=%d r1=%d r2=%d GCD=%d\n", rank, rbuf[0], rbuf[1], gcdv);

    MPI_Reduce(&gcdv, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0) {

        printf("Sum of GCDs is %d\n", result);

    }

    MPI_Finalize();

    return 0;

}