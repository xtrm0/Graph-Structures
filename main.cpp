#include "algorithms/mincut/kargerStein.hpp"
#include "structures/graph/edge_list.hpp"
using std::cout;
using std::endl;

int main() {
  EdgeList graph = ReadGraphAsEdgeList();

  int mincut = KargerStein(graph);

  cout << mincut << endl;
}