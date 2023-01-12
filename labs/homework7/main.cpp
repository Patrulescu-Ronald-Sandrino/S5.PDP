#include <iostream>
#include <mpi.h>

using namespace std;

int main() {
    MPI_Init(nullptr, nullptr);

    cout << "Hello, world!" << endl;

    MPI_Finalize();
    return 0;
}
