#include "Graph.h"
#include "GraphProvider.h"
#include "HamiltonianCycleFinder.h"


int main() {
//    auto start = chrono::high_resolution_clock::now();
//    sleep(1);
//    auto end = chrono::high_resolution_clock::now();
//
//    auto x = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1'000'000.0;
//
//    cout << x << endl;
//    return 0;

    srand(time(nullptr));

    bool runOnce = false;
    int maxLevel = 1000;
    Graph g = GraphProvider::random(100);

    if (runOnce) {
        HamiltonianCycleFinder::main(g);
    } else {
        HamiltonianCycleFinder::main(maxLevel);
    }
    return 0;
}
