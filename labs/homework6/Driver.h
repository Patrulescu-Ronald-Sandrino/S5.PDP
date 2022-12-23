//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK6_DRIVER_H
#define HOMEWORK6_DRIVER_H

#include <iostream>
#include "Graph.h"
#include "HamiltonianCycleFinder.h"

class Driver {
public:
    static void main(Graph &g) {
        // running the algorithm
        auto [result, milliseconds] = run(g);

        // printing the results
        cout << g.toString() << endl << endl;
        cout << "Time: " << milliseconds << "ms" << endl;

        if (result.empty()) {
            cout << "No Hamiltonian cycle found" << endl;
        } else {
            cout << "Hamiltonian cycle found: ";
            for (int i = 0; i < result.size(); i++) {
                cout << result[i];
                if (i != result.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }

    static void main(int n) {
        for (int i = 1; i <= n; ++i) {
            auto g = Graph::Factory::random(i);
            auto [path, milliseconds] = run(g);
            cout << i << "," << milliseconds << endl;
        }
    }

    static pair<vector<int>, double> run(Graph &g) {
        auto start = chrono::high_resolution_clock::now();
        auto result = HamiltonianCycleFinder::hasHamiltonianCycle(g);
        auto end = chrono::high_resolution_clock::now();

        return make_pair(result, (double) chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1'000'000.0);
    }
};

#endif //HOMEWORK6_DRIVER_H
