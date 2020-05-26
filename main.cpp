#include <algorithm>
#include "algorithms/mst/boruvka.hpp"
#include "structures/graph/edge_list.hpp"
#include "structures/ufds/disjoint_set_simple.hpp"
#include <utility>
#include <unordered_set>
#include <set>
#include <random>
using namespace std;

vector<pair<int,int> > randomGraph(int N, uint64_t M) {
  vector<pair<int,int> > ret;
  set<pair<int,int> > used;
  int colisions = 0;
  while(ret.size() != M) {
    int a = random() % N;
    int b = random() % N;
    if (a!=b && used.count({a,b})==0) {
      ret.emplace_back(pair<int,int>{a,b});
      used.insert(pair<int,int>{a,b});
      used.insert(pair<int,int>{b,a});
    } else {
      colisions++;
    }
  }
  cout << "Colisions:" << colisions << endl;
  return ret;
}

vector<pair<int,int> > randomERGraph(int N, double p) {
  std::default_random_engine generator;
  std::binomial_distribution<int> distribution(N*(N-1)/2, p);
  uint64_t M = distribution(generator);
  return randomGraph(N,M);
}

double APL(int N, vector<pair<int,int> > edges) {
  assert(N>2);
  vector<vector<int > > D;
  for(int i=0;i<N; i++) D.push_back(vector<int>(N,numeric_limits<int>::max()));
  for (int i=0; i<N; i++) {
    D[i][i] = 0;    
  }
  for (auto& pp : edges) {
    D[pp.first][pp.second] = 1;
    D[pp.second][pp.first] = 1;
  }
  for (int k=0; k<N; k++) {
    for (int i=0; i<N; i++) {
       for (int j=0; j<N; j++) {
          if (D[i][k] != numeric_limits<int>::max() && D[k][j] != numeric_limits<int>::max()) {
            D[i][j] = min(D[i][j], D[i][k] + D[k][j]);    
  }}}}
  
  double result=0.0;
  for (int i=0; i<N; i++) {
    for (int j=i; j<N; j++) {
      result += D[i][j];  
  }}
  
  return result / ((N)*(N-1)/2); 
}

double clustering_coefficient(int N, vector<pair<int,int> > edges) {
  vector<vector<int > > G;
  for(int i=0;i<N; i++) G.push_back(vector<int>(N,0));
  for (int i=0; i<N; i++) {
    G[i][i] = 0;    
  }
  for (auto& pp : edges) {
    G[pp.first][pp.second] = 1;
    G[pp.second][pp.first] = 1;
  }
  
  double count=0.0;
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      for (int k=0; k<N; k++) {
        if (i==j || k==j || i==k) continue;
        if (G[i][j] == 1 && G[j][k] == 1 && G[k][i] == 1) {
          count += 1;
  }}}}
  
  return (count) / ((N*(N-1)*(N-2)));
}


int main() {
  int N = 10;
  vector<pair<int,int> > graph = randomERGraph(N, 0.5);
  //vector<pair<int,int> > graph = randomGraph(N, 40);
  
  for (pair<int,int> & e : graph) {
    cout << e.first << " " << e.second << endl;
  }
  //cout << APL(N, graph) << endl;
  //cout << clustering_coefficient(N, graph) << endl;
}