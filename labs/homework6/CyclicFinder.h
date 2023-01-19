//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK6_CYCLICFINDER_H
#define HOMEWORK6_CYCLICFINDER_H

#include <iostream>
#include "Graph.h"

using namespace std;

class CyclicFinder {
public:
    static void isCyclic(Graph &graph) {
        vector<int> visited(graph.size(), 0);
        vector<int> path;
        for (int i = 0; i < graph.size(); i++) {
            if (visited[i] == 0) {
                if (isCyclicUtil(graph, i, visited, path)) {
                    cout << "Graph contains cycle" << endl;
                    return;
                }
            }
        }
        cout << "Graph doesn't contain cycle" << endl;
    }
private:
    static bool isCyclicUtil(Graph &graph, int i, vector<int> vector1, vector<int> vector2) {
        if (find(vector1.begin(), vector1.end(), i) != vector1.end()) {
            return true;
        }

        if (find(vector2.begin(), vector2.end(), i) != vector2.end()) {
            return false;
        }

        vector1.push_back(i);
        vector2.push_back(i);

        for (int j : graph.getEdgesFrom(i)) {
            if (isCyclicUtil(graph, j, vector1, vector2)) {
                return true;
            }
        }

        return false;
    }
};

#endif //HOMEWORK6_CYCLICFINDER_H
