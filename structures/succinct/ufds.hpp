#pragma once
#include "structures/baseutils/assertions.hpp"

struct DisjointSet {
  uint64_t N;  // Number of sets
  vector<uint64_t> id;
  vector<uint64_t> rank;

  DisjointSet() : N(0) { ; }
  DisjointSet(uint64_t _N)
      : N(_N), id(vector<uint64_t>(N, 0)), rank(vector<uint64_t>(N, 1)) {
    for (uint64_t i = 0; i < N; i++) {
      id[i] = i;
    }
  }

  uint64_t Find(uint64_t i) {
    if (id[i] != i) id[i] = Find(id[i]);
    return id[i];
  }

  void Union(uint64_t i, uint64_t j) {
    i = Find(i);
    j = Find(j);
    if (rank[i] > rank[j]) swap(i, j);
    // rank[i] <= rank[j]
    id[j] = i;
    rank[i]++;
  }

  bool AreConnected(uint64_t i, uint64_t j) { return Find(i) == Find(j); }

  void debug() {
    for (uint64_t i = 0; i < N; i++) {
      cout << id[i] << " ";
    }
    cout << endl;
  }
};