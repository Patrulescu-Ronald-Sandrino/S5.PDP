#include "Graph.h"
#include "GraphProvider.h"
#include "Driver.h"


int main() {
    srand(time(nullptr));

    bool runOnce = true;
    int nodes = 1000;
    Graph g = GraphProvider::random(nodes);


    if (runOnce) Driver::main(g);
    else Driver::main(nodes);

    return 0;
}
