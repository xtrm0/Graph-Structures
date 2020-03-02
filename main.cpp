#include "structures/graph/adjacency_list.hpp"
using namespace std;

int main() {
    vector<Edge> edges = {{0,4},{1,2},{1,3},{1,4},{2,3},{3,4}};
    AdjacencyList graph;
    graph = AdjacencyList(5, edges);
    cout << graph.N << endl;
    cout << graph.E << endl;
}