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
                         UndoableDisjointSet& ds, uint64_t comp,
                         uint64_t& currentI) {
  // Run compression
  uint64_t components = N;

  for (; currentI < E && components > comp; currentI++) {
    // Pick a random edge in edges[currentI, E]
    uint64_t j = currentI + (rand() % (E - currentI - 1));
    swap(edges[currentI], edges[j]);
    // swap with edge at index currentI
    if (ds.AreConnected(edges[currentI].u, edges[currentI].v)) continue;
    // not connected
    components--;
    ds.Union(edges[currentI].u, edges[currentI].v);
  }

  // components == comp
  uint64_t cut = 0;

  if (comp == 2) {
    for (uint64_t i = 0; i < E; i++) {
      if (ds.AreConnected(edges[i].u, edges[i].v)) continue;
      // not connected
      cut++;
    }
  }

  return cut;
}

static uint64_t FastMinCut(vector<Edge>& input, uint64_t N, uint64_t E,
                           UndoableDisjointSet& ds, uint64_t currentI) {
  if (N < 6) {
    uint64_t ret = Contract(input, N, E, ds, 2, currentI);
    cout << ret << endl;
    return ret;
  }

  uint64_t ret = E + 1;
  uint64_t t = 1 + (N * 100000 / 141421);

  uint64_t updateableI;
  updateableI = currentI;
  ds.SaveState();
  Contract(input, N, E, ds, t, updateableI);
  ret = FastMinCut(input, t, E, ds, updateableI);
  ds.RestoreState();
  ds.SaveState();
  updateableI = currentI;
  Contract(input, N, E, ds, t, updateableI);
  ret = min(ret, FastMinCut(input, t, E, ds, updateableI));
  ds.RestoreState();

  return ret;
}

// Probabilistic algorithm for mincut, implementation can be improved
//
// Time: O((N+E) log^2 N alpha(N))
// Space: O(N+E alpha(N))
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
    UndoableDisjointSet ds = UndoableDisjointSet(N);
    mincut = std::min(mincut, FastMinCut(edges, N, E, ds, 0));
  }

  return mincut;
}