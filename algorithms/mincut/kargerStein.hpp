#pragma once
#include "karger.hpp"
#include "structures/graph/edge_list.hpp"
#include "structures/succinct/ufds.hpp"
using namespace std;

// UNDONE: this implementation complexities can and should be improved
//
// UNDONE: decide between modules or moving this to a .cpp
//

static uint64_t Contract(vector<Edge>& edges, uint64_t N, uint64_t E,
                         DisjointSet& ds, uint64_t comp) {
  // Shuffle the array
  // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
  // for i from 0 to n−2 do
  for (uint64_t i = 0; i < E - 1; i++) {
    // j ← random integer such that i ≤ j < n
    uint64_t j = (rand() % (E - i - 1)) + i;
    if (i != j) swap(edges[i], edges[j]);  // exchange a[i] and a[j]
  }

  // Run compression
  uint64_t components = N;

  for (uint64_t i = 0; i < E && components > comp; i++) {
    if (ds.AreConnected(edges[i].u, edges[i].v)) continue;
    // not connected
    components--;
    ds.Union(edges[i].u, edges[i].v);
  }

  // components == comp
  uint64_t cut = 0;
  for (uint64_t i = 0; i < E; i++) {
    if (ds.AreConnected(edges[i].u, edges[i].v)) continue;
    // not connected
    cut++;
  }

  return cut;
}

static uint64_t FastMinCut(vector<Edge>& input, int N, int E, DisjointSet& ds) {
  if (N < 6) {
    return Contract(input, N, E, ds, 2);
  }

  uint64_t ret = E + 1;
  uint64_t t = 1 + (N * 100000 / 141421);

  DisjointSet ds1 = ds;
  CalcMinCut(input, N, E, ds, t);
  ret = FastMinCut(input, t, E, ds1);
  ds1 = ds;
  CalcMinCut(input, N, E, ds, t);
  ret = min(ret, FastMinCut(input, t, E, ds1));
  return ret;
}

// Probabilistic algorithm for mincut, implementation can be improved
//
// Time: O(N (N+E) log^2 N)
// Space: O(N^(3/2)+E)
// UNDONE: make time and space bounds better
//
uint64_t KargerStein(EdgeList& Graph) {
  uint64_t& E = Graph.E;
  uint64_t& N = Graph.N;
  vector<Edge>& edges = Graph.edges;

  uint64_t mincut = E + 1;

  uint64_t log = 1;
  uint64_t auxN = N;
  // change number of runs
  while (auxN != 0) {
    log++;
    auxN /= 2;
  }

  uint64_t runs = log * log + 2;

  for (uint64_t i = 0; i < runs; i++) {
    DisjointSet ds = DisjointSet(N);
    mincut = std::min(mincut, FastMinCut(edges, N, E, ds));
  }

  return mincut;
}