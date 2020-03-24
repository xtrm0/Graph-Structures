#include "algorithms/mincut/kargerStein.hpp"
#include "structures/graph/edge_list.hpp"
using std::cout;
using std::endl;

int main() {
  EdgeList graph = EdgeList(
      4, {{0, 2}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}});

  int mincut = KargerStein(graph);

  cout << mincut << endl;
}