#include "Graph.h"
#include "GraphProvider.h"
#include "HamiltonianCycleFinder.h"


int main() {
    Graph g = GraphProvider::withoutHamiltonianPath;

    HamiltonianCycleFinder::main(g);
    return 0;
}
