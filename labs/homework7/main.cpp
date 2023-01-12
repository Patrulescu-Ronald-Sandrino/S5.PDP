#include <iostream>
#include <mpi.h>

using namespace std;

int main() {
    MPI_Init(nullptr, nullptr);
    int me;
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);


    MPI_Finalize();
    return 0;
}
