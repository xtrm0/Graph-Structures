 
#include "benchmark/benchmark.h"
#include <math.h>

int foo(int w) {
    int k=0;
    for (int i=0; i<w; i++) {
        k += (w + k*k + i*2 + 7 - i*k) / 8;
    }
    return k;
}

static void BM_FOO(benchmark::State &state) {
  for (auto _ : state) benchmark::DoNotOptimize(foo(state.range(0)));
   state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_FOO)
    ->RangeMultiplier(2)->Range(1<<0, 1<<16)->Complexity();
    
BENCHMARK(BM_FOO)
    ->RangeMultiplier(2)->Range(1<<0, 1<<18)->Complexity(benchmark::oN);



int foo2(int w) {
    int k=0;
    for (int i=0; i<w; i++) {
        k += foo(w);
    }
    return k;
}

static void BM_FOO2(benchmark::State &state) {
  for (auto _ : state) benchmark::DoNotOptimize(foo2(state.range(0)));
   state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_FOO2)
    ->RangeMultiplier(2)->Range(1<<0, 1<<13)->Complexity();
    
BENCHMARK(BM_FOO2)
    ->RangeMultiplier(2)->Range(1<<0, 1<<13)->Complexity(benchmark::oAuto);
    

int foo3(int w) {
    int k=0;
    for (int i=0; i*i<w; i++) {
        k += foo(w);
    }
    return k;
}

static void BM_FOO3(benchmark::State &state) {
  for (auto _ : state) benchmark::DoNotOptimize(foo3(state.range(0)));
   state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_FOO3)
    ->RangeMultiplier(2)->Range(1<<0, 1<<13)->Complexity();
    
BENCHMARK(BM_FOO3)
    ->RangeMultiplier(2)->Range(1<<0, 1<<13)->Complexity([](int64_t n) { return ((double)n)*sqrt((double)n); });