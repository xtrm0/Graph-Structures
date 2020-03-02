#pragma once
#include "structures/baseutils/assertions.hpp"

typedef unsigned int NodeId;

struct Edge {
  NodeId u;
  NodeId v;
};

struct Graph {
protected:
  Graph() : N(0), E(0) {;}
  Graph(uint64_t N, vector<Edge> edges) : N(N), E(edges.size()){
    for (const Edge& edge : edges) {
      ASSERT(0 <= edge.u && edge.u <= N);
      ASSERT(0 <= edge.v && edge.v <= N);
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
  uint64_t GetMemoryUsage() { UNDONE("Returns the graph memory usage"); return 0; }
    
  // UNDONE("Range Queries")
  // bool ExistsNeighboorInRange(NodeId i, NodeId minI, NodeId maxE);
  // UNDONE("Range Queries")
  // bool ExistsReverseNeighboorInRange(NodeId i, NodeId minI, NodeId maxE);
  //
};