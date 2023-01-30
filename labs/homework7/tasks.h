//
// Created by kamui on 13.01.2023.
//

#ifndef HOMEWORK7_TASKS_H
#define HOMEWORK7_TASKS_H

#include <chrono>
#include "model/Polynomial.h"
#include "model/Implementation.h"

extern Implementation implementation;

void masterTask(Polynomial& p1, Polynomial& p2, int processes) {
    auto startTime = chrono::high_resolution_clock::now();
    int length = p1.getSize() / (processes - 1); // TODO: WHY?

    int start;
    int end = 0;
    for (int i = 0; i < processes; ++i) {
        start = end;
        end = start + length;

        if (i == processes - 1) {
            end = p1.getSize();
        }

        MPI_Send((void*)p1.getSize(), 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(p1.getCoefficients().data(), p1.getSize(), MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send((void*)p2.getSize(), 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(p2.getCoefficients().data(), p2.getSize(), MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    // TODO receive result
    // TODO convert if necessary
    Polynomial result = Polynomial(5); // TODO: replace value

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

    cout << implementationToString(implementation) << " implementation took " << duration << " ms" << endl;
}

void regularTask(int id) {
    int p1Size;
    int p2Size;
    int start;
    int end;

    // receive the data
    MPI_Recv(&p1Size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    vector<int> p1Coefficients(p1Size);
    MPI_Recv(p1Coefficients.data(), p1Size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Recv(&p2Size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    vector<int> p2Coefficients(p1Size);
    MPI_Recv(p2Coefficients.data(), p1Size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // convert to polynomials
    Polynomial p1(p1Coefficients);
    Polynomial p2(p2Coefficients);

    // multiply the interval
    Polynomial result = p1.multiplySequence(p2, start, end);

    // send result
    MPI_Send((void*)result.getSize(), 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(result.getCoefficients().data(), result.getSize(), MPI_INT, 0, 0, MPI_COMM_WORLD);
}

void karatsubaTask(int id) {

}



#endif //HOMEWORK7_TASKS_H
