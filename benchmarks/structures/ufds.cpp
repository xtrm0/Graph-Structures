#include "structures/succinct/ufds.hpp" 
#include "benchmark/benchmark.h"
#include "benchmarks/util/benchmark_assertions.hpp"
#include <math.h>
using std::vector;
using std::tuple;

int ufds_do_ops(int N, vector<tuple<bool,int,int> >& ops) {
  DisjointSet ds(N);
  int cnt = 0;
  for (auto&& [isJoin, i, j] : ops) {
    if (isJoin) {
      ds.Union(i,j);
    } else {
      if (ds.AreConnected(i,j)) {
        cnt++;
      }
    }
  }
  return cnt;
}

static void BM_UDFS(benchmark::State &state) {
  int opsCnt = state.range(0);
  int N = int(opsCnt/100) + 1;

  vector<tuple<bool,int,int> > ops;  
  for (auto _ : state) {
    state.PauseTiming();
    ops.clear();
    for (int i=0; i<opsCnt; i++) {
      ops.push_back(make_tuple<>(random()%2==0, random()%N, random()%N));
    }
    state.ResumeTiming();
    benchmark::DoNotOptimize(ufds_do_ops(N,ops));
  }
   
  state.SetComplexityN(state.range(0)); 
}

BENCHMARK(BM_UDFS)
    ->RangeMultiplier(4)->Range(1<<1, 1<<20)->Complexity();
    
BENCHMARK(BM_UDFS)
    ->RangeMultiplier(4)->Range(1<<1, 1<<20)->Complexity([](int64_t n) { return 8.5*((double)n); });