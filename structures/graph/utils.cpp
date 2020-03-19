#include "graph.hpp"
#include "adjacency_list.hpp"
#include "adjacency_matrix.hpp"
#include "compressed_sparse_rows.hpp"
#include "edge_list.hpp"

AdjacencyList ReadGraphAsAdjacencyList() {
  AdjacencyList ret;
  cin >> ret.N >> ret.E;
  for (NodeId i=0; i<ret.N; i++) ret.adjlist.push_back(vector<NodeId>());
  for (NodeId i=0; i<ret.E; i++) {
    NodeId a,b;
    cin >> a >> b;
    ret.adjlist[a].push_back(b);
  }
  return ret;
}


AdjacencyMatrix ReadGraphAsAdjacencyMatrix() {
  AdjacencyMatrix ret;
  cin >> ret.N >> ret.E;
  assert( 0 <= ret.N );
  assert( 0 <= ret.E );
  
  for (NodeId i=0; i<ret.N; i++) ret.matrix.push_back(vector<bool>(ret.N,false));
  for (NodeId i=0; i<ret.E; i++) {
    NodeId a,b;
    cin >> a >> b;
    assert(0 <= a && a <= ret.N);
    assert(0 <= b && b <= ret.N);
    ret.matrix[a][b] = true;
  }
  
  return ret;
}

CSRGraph ReadGraphAsCSR() {
  NodeId N, E;
  vector<Edge> edges;
  cin >> N >> E;
  for (NodeId i=0; i<E; i++) {
    NodeId a,b;
    cin >> a >> b;
    a--; b--;
    edges.push_back({a,b});
  }  
  return CSRGraph(N, edges);
}

EdgeList ReadGraphAsEdgeList() {
  NodeId N, E;
  vector<Edge> edges;
  cin >> N >> E;
  for (NodeId i=0; i<E; i++) {
    NodeId a,b;
    cin >> a >> b;
    a--; b--;
    edges.push_back({a,b});
  }  
  return EdgeList(N, edges);
}