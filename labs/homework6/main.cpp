#include <iostream>
#include <chrono>
#include "Graph.h"
#include "GraphProvider.h"


int main() {
    Graph g = GraphProvider::withoutHamiltonianPath;

    cout << g.toString() << endl;

    auto start = chrono::high_resolution_clock::now();
    // TODO: call your algorithm here + implement it
    auto end = chrono::high_resolution_clock::now();

    cout << "Time: " << (double)chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000.0<< "ms" << endl;

    return 0;
}
