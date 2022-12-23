//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK6_GRAPH_H
#define HOMEWORK6_GRAPH_H

#include <vector>
#include <string>
#include <fstream>
#include "util.h"

using namespace std;

class Graph {
public:
    class Factory {
        constexpr auto static const stringToIntVector = [](const string &s) {
            return map<string, int>(split(s, ' '), [](const string &s) { return stoi(s); });
        };
    public:
        Graph static create(const vector<int> &nodes, const vector<vector<int>> &edges) {
            return {nodes, edges};
        }

        Graph static readFromFile(const string &filename) {
            ifstream file(filename);

            if (!file.is_open()) throw runtime_error("Could not open file " + filename);


            vector<int> nodes;
            vector<vector<int>> edges;

            string line;
            getline(file, line);
            nodes = stringToIntVector(line);

            while (getline(file, line)) {
                edges.push_back(stringToIntVector(line));
            }

            return {nodes, edges};
        }

        Graph random(int n, int m) {
            // TODO
        }
    };

    string toString() const {
        string result = "Graph{\nnodes=[";
        for (int i = 0; i < nodes.size(); i++) {
            result += to_string(nodes[i]);
            if (i != nodes.size() - 1) result += ", ";
        }

        result += "],\nedges=[\n";
        for (int i = 0; i < edges.size(); i++) {
            result += "\t" + to_string(i) + " -> [";
            for (int j = 0; j < edges[i].size(); j++) {
                result += to_string(edges[i][j]);
                if (j != edges[i].size() - 1) result += ", ";
            }
            result += "]";
            if (i != edges.size() - 1) result += ", \n";
        }
        result += "\n]\n}";

        return result;
    }

private:
    vector<int> nodes;
    vector<vector<int>> edges;

    Graph(const vector<int> &nodes, const vector<vector<int>> &edges) : nodes(nodes), edges(edges) {}
};


#endif //HOMEWORK6_GRAPH_H
