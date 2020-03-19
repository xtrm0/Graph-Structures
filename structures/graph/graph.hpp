#pragma once
#include "structures/baseutils/assertions.hpp"

typedef unsigned int NodeId;

struct Edge {
  NodeId u;
  NodeId v;
};

struct Graph {
 protected:
  Graph() : N(0), E(0) { ; }
  Graph(uint64_t N, vector<Edge> edges) : N(N), E(edges.size()) {
    for (const Edge& edge : edges) {
      ASSERT(static_cast<NodeId>(-1) != edge.u);
      // UNDONE(gcc-pragma-bug): ASSERT(0 <= edge.u);
      ASSERT(edge.u <= N);
      ASSERT(static_cast<NodeId>(-1) != edge.v);
      // UNDONE(gcc-pragma-bug): ASSERT(0 <= edge.v)
      ASSERT(edge.v <= N);
    }
  }

 public:
  uint64_t N;
  uint64_t E;

 public:
  int NodeCount() { return N; }
  int EdgeCount() { return E; }
  vector<Edge> GetEdges();
  vector<NodeId> GetNeighboors(NodeId i);
  vector<NodeId> GetReverseNeighboors(NodeId i);
  bool IsAdjacent(NodeId i, NodeId j);
  uint64_t GetMemoryUsage() {
    UNDONE("Returns the graph memory usage");
    return 0;
  }

  // UNDONE("Range Queries")
  // bool ExistsNeighboorInRange(NodeId i, NodeId minI, NodeId maxE);
  // UNDONE("Range Queries")
  // bool ExistsReverseNeighboorInRange(NodeId i, NodeId minI, NodeId maxE);
  //
};