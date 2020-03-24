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

struct UndoableDisjointSet : DisjointSet {
  struct HistoryOp {
    uint64_t type;     // 0 -> save_version, 1-> update
    uint64_t node;     // which node was updated
    uint64_t oldid;    // the value that was here before
    uint64_t oldrank;  // the value that was here before
  };

  stack<HistoryOp> history;

  UndoableDisjointSet() : DisjointSet() { ; }
  UndoableDisjointSet(uint64_t _N) : DisjointSet(_N) { ; }

  uint64_t Find(uint64_t i) {
    if (id[i] != i) {
      uint64_t newId = Find(id[i]);
      if (newId != id[i]) {
        history.push({1, i, id[i], rank[i]});
        id[i] = newId;
      }
    }
    return id[i];
  }

  void Union(uint64_t i, uint64_t j) {
    i = Find(i);
    j = Find(j);
    if (rank[i] > rank[j]) swap(i, j);
    // rank[i] <= rank[j]
    history.push({1, i, id[i], rank[i]});
    history.push({1, j, id[j], rank[j]});
    id[j] = i;
    rank[i]++;
  }

  void SaveState() { history.push({0, 0, 0, 0}); }

  void RestoreState() {
    assert(history.size() > 0);
    while (true) {
      HistoryOp t = history.top();
      history.pop();
      if (t.type == 0) {
        break;
      }
      id[t.node] = t.oldid;
      rank[t.node] = t.oldrank;
    }
  }
};