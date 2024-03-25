#include "../Algorithms/ShortestPath/ShortestPath.h"
#include "../DataStructures/Graph/Graph.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../Algorithms/Dijkstra/Dijkstra.h"

int main() {
    ULTRA::Graph graph;
    graph.load("florida.dimacs");

    ULTRA::ShortestPath<ULTRA::Graph> dijkstra(graph);

    std::srand(std::time(nullptr));
    const int num_pairs = 200;
    double total_runtime = 0.0;

    for (int i = 0; i < num_pairs; ++i) {
        const ULTRA::Vertex source = std::rand() % graph.numVertices();
        const ULTRA::Vertex target = std::rand() % graph.numVertices();

        const auto start_time = std::clock();
        dijkstra.run(source, target);
        const auto end_time = std::clock();

        total_runtime += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    }

    std::cout << "Total runtime in seconds for " << num_pairs << " random Dijkstra: " << total_runtime << std::endl;

    return 0;
}
