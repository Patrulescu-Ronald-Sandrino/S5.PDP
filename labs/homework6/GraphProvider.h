//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK6_GRAPHPROVIDER_H
#define HOMEWORK6_GRAPHPROVIDER_H

#include "Graph.h"

class GraphProvider {
public:
    static Graph withHamiltonianCycle;
    static Graph withoutHamiltonianPath;
    static Graph random(int n) { return Graph::Factory::random(n); }


    ~GraphProvider() = delete;
    Graph operator=(const GraphProvider&) = delete;
};


Graph GraphProvider::withHamiltonianCycle = Graph::Factory::create({0, 1, 2, 3, 4}, {{1}, {2}, {4}, {0}, {3}}); // http://graphonline.ru/en/?graph=ZtbvgGfHcXvBmoXr
Graph GraphProvider::withoutHamiltonianPath = Graph::Factory::create({0, 1, 2, 3, 4}, {{1}, {2}, {}, {0}, {3}}); // http://graphonline.ru/en/?graph=ZtbvgGfHcXvBmoXr


#endif //HOMEWORK6_GRAPHPROVIDER_H
