#pragma once
#include "structures/baseutils/assertions.hpp"

// This is a simple efficient implementation of a union-find disjoint set.
// We are actually going to use the Disjoint Set class, which has many
// more utilities, but it is basically a complex version of this structure
//
// This disjoint set assumes that 1 <= i <= N
//
struct SimpleDisjointSet {
  uint64_t N;  // Number of sets
  vector<uint64_t> id;
  vector<uint64_t> rank;
  SimpleDisjointSet() : N(0) { ; }
  SimpleDisjointSet(uint64_t _N)
      : N(_N),
        id(vector<uint64_t>(N + 1, 0)),
        rank(vector<uint64_t>(N + 1, 1)) {
    for (uint64_t i = 1; i <= N; i++) {
      id[i] = i;
    }
  }
  uint64_t Find(uint64_t i) {
    assert(i > 0);
    if (id[i] != i) id[i] = Find(id[i]);
    return id[i];
  }
  void Union(uint64_t i, uint64_t j) {
    i = Find(i);
    j = Find(j);
    if (rank[i] < rank[j]) swap(i, j);
    id[j] = i;
    rank[i]++;
  }
  bool AreConnected(uint64_t i, uint64_t j) { return Find(i) == Find(j); }
};

struct DisjointSet {
  struct Node {
    // With usefull information
    //
    uint64_t id;        // set id
    uint64_t nextroot;  // next set on the linked list of sets
    uint64_t nextnode;  // next node on this set

    // Auxiliary, for performance:
    //
    uint64_t prevroot;  // root is a double linked list
    uint64_t tailnode;  // last node on this partition (to make append O(1))
    uint64_t rank;
  };

  uint64_t N;  // Number of sets
  uint64_t components;
  vector<Node> nodes;

  DisjointSet() : N(0), components(0) { ; }
  DisjointSet(uint64_t _N) : N(_N), components(_N), nodes(_N + 1, Node()) {
    for (uint64_t i = 0; i <= N; i++) {
      nodes[i].id = i;
      nodes[i].nextroot = i + 1;
      nodes[i].prevroot = i - 1;
      nodes[i].nextnode = static_cast<uint64_t>(-1);
      nodes[i].tailnode = i;
      nodes[i].rank = 1;
    }
    nodes[0].prevroot = static_cast<uint64_t>(-1);
    nodes[N].nextroot = static_cast<uint64_t>(-1);
  }

  // Find the component id of a node
  //
  uint64_t Find(uint64_t i) {
    assert(i > 0);
    if (nodes[i].id != i) nodes[i].id = Find(nodes[i].id);
    return nodes[i].id;
  }

  // Puts two nodes on the same component
  //
  void Union(uint64_t i, uint64_t j) {
    assert(i > 0);
    assert(j > 0);
    i = Find(i);
    j = Find(j);
    if (i == j) return;
    if (nodes[i].rank < nodes[j].rank) swap(i, j);
    nodes[j].id = i;
    nodes[i].rank++;
    components--;

    if (nodes[j].nextroot != static_cast<uint64_t>(-1)) {
      nodes[nodes[j].nextroot].prevroot = nodes[j].prevroot;
    }
    nodes[nodes[j].prevroot].nextroot = nodes[j].nextroot;
    nodes[nodes[i].tailnode].nextnode = j;
    nodes[i].tailnode = nodes[j].tailnode;
  }

  // Gets all the component id's
  //
  vector<uint64_t> GetRoots() {
    // UNDONE(test): test this function
    vector<uint64_t> ret;
    uint64_t currRoot = nodes[0].nextroot;
    while (currRoot != static_cast<uint64_t>(-1)) {
      currRoot = Find(currRoot);
      ret.push_back(currRoot);
      currRoot = nodes[currRoot].nextroot;
    }
    return ret;
  }

  // Gets all the nodes on a given component
  //
  vector<uint64_t> GetNodesOfComponent(uint64_t root) {
    // UNDONE(test): test this function
    vector<uint64_t> ret;
    root = Find(root);
    while (root != static_cast<uint64_t>(-1)) {
      ret.push_back(root);
      root = nodes[root].nextnode;
    }
    return ret;
  }

  bool AreConnected(uint64_t i, uint64_t j) {
    assert(i > 0);
    assert(j > 0);
    return Find(i) == Find(j);
  }

  void debug() {
    for (uint64_t i = 0; i <= N; i++) {
      cout << nodes[i].id << " ";
    }
    cout << endl;
  }
};

struct UndoableDisjointSet : DisjointSet {
  struct HistoryOp {
    uint64_t id;
    DisjointSet::Node oldstate;
    uint64_t componentsCh;
  };

  stack<HistoryOp> history;

  UndoableDisjointSet() : DisjointSet() { ; }
  UndoableDisjointSet(uint64_t _N) : DisjointSet(_N) { ; }

  uint64_t Find(uint64_t i) {
    if (nodes[i].id != i) {
      history.push(HistoryOp{i, nodes[i], 0});
      uint64_t newId = Find(nodes[i].id);
      if (newId == nodes[i].id) {
        history.pop();
      }
      nodes[i].id = newId;
    }
    return nodes[i].id;
  }

  void Union(uint64_t i, uint64_t j) {
    assert(i > 0);
    assert(j > 0);
    i = Find(i);
    j = Find(j);
    if (i == j) return;
    if (nodes[i].rank < nodes[j].rank) swap(i, j);

    history.push(HistoryOp{i, nodes[i], 1});
    history.push(HistoryOp{j, nodes[j], 0});
    history.push(HistoryOp{nodes[j].prevroot, nodes[nodes[j].prevroot], 0});
    history.push(HistoryOp{nodes[j].tailnode, nodes[nodes[j].tailnode], 0});
    if (nodes[j].nextroot != static_cast<uint64_t>(-1)) {
      history.push(HistoryOp{nodes[j].nextroot, nodes[nodes[j].nextroot], 0});
    }

    DisjointSet::Union(i, j);
  }

  void SaveState() {
    history.push({static_cast<uint64_t>(-1), DisjointSet::Node(), 0});
  }

  void RestoreState() {
    assert(history.size() > 0);
    while (true) {
      HistoryOp t = history.top();
      if (t.id == static_cast<uint64_t>(-1)) {
        history.pop();
        break;
      }
      nodes[t.id] = t.oldstate;
      components += t.componentsCh;
      history.pop();
    }
  }

  // Gets all the component id's
  //
  vector<uint64_t> GetRoots() {
    // UNDONE(test): test this function
    vector<uint64_t> ret;
    uint64_t currRoot = nodes[0].nextroot;
    while (currRoot != static_cast<uint64_t>(-1)) {
      currRoot = Find(currRoot);
      ret.push_back(currRoot);
      currRoot = nodes[currRoot].nextroot;
    }
    return ret;
  }

  // Gets all the nodes on a given component
  //
  vector<uint64_t> GetNodesOfComponent(uint64_t root) {
    // UNDONE(test): test this function
    vector<uint64_t> ret;
    root = Find(root);
    while (root != static_cast<uint64_t>(-1)) {
      ret.push_back(root);
      root = nodes[root].nextnode;
    }
    return ret;
  }

  bool AreConnected(uint64_t i, uint64_t j) {
    assert(i > 0);
    assert(j > 0);
    return Find(i) == Find(j);
  }
};