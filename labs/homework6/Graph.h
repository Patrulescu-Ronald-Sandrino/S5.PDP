//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK6_GRAPH_H
#define HOMEWORK6_GRAPH_H

#include <vector>
#include <string>
#include <fstream>
#include <valarray>
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

        Graph static random(int n) {
            vector<int> nodes = vectorFromIndexMapping<int>(n, [](unsigned int i) { return i; });
            vector<vector<int>> edges = vectorFromIndexMapping<vector<int>>(n, [](unsigned int i) { return vector<int>();});

            for (int i = 0; i < pow(n, 2) / 2; i++) {
                int from = rand() % n;
                int to = rand() % n;

                if (from == to) continue;
                if (contains(edges[from], to)) continue;

                edges[from].push_back(to);
            }

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
    };

    [[nodiscard]] const vector<int> &getNodes() const {
        return nodes;
    }

    [[nodiscard]] string toString() const {
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

    vector<int> &getEdgesFrom(int node) {
        if (not exists(node)) throw runtime_error("Node " + to_string(node) + " does not exist");

        return edges[node];
    }

    [[nodiscard]] bool hasEdge(int from, int to) const {
        if (not exists(from)) throw runtime_error("Node " + to_string(from) + " does not exist");
        if (not exists(to)) throw runtime_error("Node " + to_string(to) + " does not exist");

        return std::find(edges[from].begin(), edges[from].end(), to) != edges[from].end();
    }

    /** @return number of nodes in the graph */
    [[nodiscard]] size_t size() const {
        return nodes.size();
    }

protected:
    vector<int> nodes;
    vector<vector<int>> edges;

    Graph(const vector<int> &nodes, const vector<vector<int>> &edges) : nodes(nodes), edges(edges) {}


    [[nodiscard]] bool exists(int node) const {
        return std::find(nodes.begin(), nodes.end(), node) != nodes.end();
    }
};


#endif //HOMEWORK6_GRAPH_H
