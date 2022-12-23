//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK6_HAMILTONIANCYCLEFINDER_H
#define HOMEWORK6_HAMILTONIANCYCLEFINDER_H

#include <chrono>
#include <iostream>
#include "Graph.h"

class HamiltonianCycleFinder {
public:
    static void main(const Graph& g) {
        // running the algorithm
        auto start = chrono::high_resolution_clock::now();
        auto result = HamiltonianCycleFinder::hasHamiltonianCycle(g);
        auto end = chrono::high_resolution_clock::now();

        // printing the results
        cout << g.toString() << endl << endl;
        cout << "Time: " << (double)chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1'000.0<< "ms" << endl;

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

    static vector<int> hasHamiltonianCycle(const Graph &graph)  {
        return HamiltonianCycleFinder(graph).hasHamiltonianCycle();
    }

private:
    const Graph& graph;
    explicit HamiltonianCycleFinder(const Graph& graph) : graph(graph) {}

    [[nodiscard]] vector<int> hasHamiltonianCycle() const {
        return {};
    }
};

#endif //HOMEWORK6_HAMILTONIANCYCLEFINDER_H
