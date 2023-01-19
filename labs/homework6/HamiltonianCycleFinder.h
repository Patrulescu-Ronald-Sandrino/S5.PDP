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

    bool search(int currentNode, vector<int> &path) const {
        if (visitedAllNodes(path)) return graph.hasEdge(currentNode, path[0]);

        for (auto node: graph.getNodes()) {
//            ::printf("tid=%x, currentNode=%d, node=%d\n", this_thread::get_id(), currentNode, node);

            if (graph.hasEdge(currentNode, node) and not contains(path, node)) {
                path.push_back(node);
                std::remove(graph.getEdgesFrom(currentNode).begin(), graph.getEdgesFrom(currentNode).end(), node);

                if (searchAsync(node, path).get()) return true;

                graph.getEdgesFrom(currentNode).push_back(node);
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
