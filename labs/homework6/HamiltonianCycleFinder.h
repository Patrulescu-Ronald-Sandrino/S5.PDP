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
