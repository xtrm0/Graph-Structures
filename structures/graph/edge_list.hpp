#pragma once
#include "graph.hpp"

struct EdgeList : Graph {
  vector<Edge> edges;
  EdgeList() : Graph() {;}
  EdgeList(uint64_t N, vector<Edge> edges) : Graph(N, edges), edges(edges) {;}

public:
  vector<Edge> GetEdges() {return edges;}
  vector<NodeId> GetNeighboors(NodeId i) {
      vector<NodeId> ret;
      for(Edge& e: edges) {
          if (e.u == i) {
              ret.push_back(e.v);
          }
      }
      return ret;
  }
  vector<NodeId> GetReverseNeighboors(NodeId i)  {
      vector<NodeId> ret;
      for(Edge& e: edges) {
          if (e.v == i) {
              ret.push_back(e.u);
          }
      }
      return ret;
  }
  bool IsAdjacent(NodeId i, NodeId j) {
      return 0 != count_if(edges.begin(), edges.end(), [&i,&j](const Edge& e) { return e.u == i && e.v == j;});
  }
  uint64_t GetMemoryUsage() {
    uint64_t ret = 0;
    ret += 2*sizeof(uint64_t); //N,E
    ret += sizeof(vector<Edge>);
    ret += edges.capacity() * sizeof(Edge);
    return ret;
  }
};