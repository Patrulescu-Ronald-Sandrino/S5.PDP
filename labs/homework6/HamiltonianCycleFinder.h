//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK6_HAMILTONIANCYCLEFINDER_H
#define HOMEWORK6_HAMILTONIANCYCLEFINDER_H

#include <chrono>
#include <iostream>
#include <future>
#include "Graph.h"

class HamiltonianCycleFinder {
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

    static vector<int> hasHamiltonianCycle(Graph &graph) {
        return HamiltonianCycleFinder(graph).hasHamiltonianCycle();
    }

private:
    Graph &graph;

    explicit HamiltonianCycleFinder(Graph &graph) : graph(graph) {}

    [[nodiscard]] vector<int> hasHamiltonianCycle() const {
        if (graph.getNodes().empty()) throw runtime_error("Graph is empty");

        auto node = graph.getNodes()[0];
        vector<int> path = {node};
        auto found = search(node, path);

        return found ? path : vector<int>();
    }

    bool search(int node, vector<int> &path) const {
        if (visitedAllNodes(path)) return graph.hasEdge(node, path[0]);

        for (int i = 0; i < graph.size(); ++i) {

            if (graph.hasEdge(node, i) and not contains(path, i)) {
                path.push_back(i);
                std::remove(graph.getEdgesFrom(node).begin(), graph.getEdgesFrom(node).end(), i);

                if (searchAsync(i, path).get()) return true;

                graph.getEdgesFrom(node).push_back(i);
                path.pop_back();
            }
        }

        return false;
    }

    [[nodiscard]] bool visitedAllNodes(const vector<int> &path) const {
        return path.size() == graph.size();
    }

    future<bool> searchAsync(int node, vector<int> &path) const {
        return async(launch::async, [this, node, &path] { return search(node, path); });
    }
};

#endif //HOMEWORK6_HAMILTONIANCYCLEFINDER_H
