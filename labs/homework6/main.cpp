#include "Graph.h"
#include "GraphProvider.h"
#include "Driver.h"


int main() {
    srand(time(nullptr));

    bool runOnce = false;
    int nodes = 25;
    Graph g = GraphProvider::random(nodes);


    if (runOnce) Driver::main(g);
    else Driver::main(nodes);

    return 0;
}
