#include <mpi.h>
#include <iostream>
#include "tasks.h"
#include "model/Polynomial.h"

using namespace std;



/// PLAY WITH THESE VALUES ///
int POLYNOMIAL_SIZE = 5;
Implementation implementation = Implementation::regular;
/// ---------------------- ///


/*
DEGREE VS SIZE
X^2 + X^1 + X^0
 size = 3, degree = 2

degree = size - 1
size = degree + 1
 */

int main() {
    MPI_Init(nullptr, nullptr);
    int id;
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    cout << id << " | " << "Hello, World!" << endl;

    if (id == 0) {
        cout << "Master process" << endl;

        Polynomial p1 = Polynomial(Util::vectorFromIndexMapping(POLYNOMIAL_SIZE, [](unsigned int i) { return (i + 1) % 10; }));
        Polynomial p2 = Polynomial(Util::vectorFromIndexMapping(POLYNOMIAL_SIZE, [](unsigned int i) { return (i + 1) % 10; }));

        cout << "p1 = " << p1 << endl;
        cout << "p2 = " << p2 << endl;

        masterTask(p1, p2, size);
    }
    else {
        implementation == Implementation::regular ? regularTask(id) : karatsubaTask(id);
    }

    MPI_Finalize();


    return 0;
}

