#include "structures/graph/edge_list.hpp"
#include "algorithms/mincut/kargerStein.hpp"
using namespace std;

int main() {
    EdgeList graph = ReadGraphAsEdgeList();
    
    int mincut = KargerStein(graph);
    
    cout << mincut << endl;
}