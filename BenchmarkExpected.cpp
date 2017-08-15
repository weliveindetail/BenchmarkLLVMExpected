#include "BenchPerfCategories.h"
#include "BenchOptimizations.h"
#include "BenchSuccessRates.h"

#include <benchmark/benchmark.h>
#include <llvm/Support/Error.h>

#include <chrono>
#include <thread>

BENCHMARK(BM_Category_FastRand);
BENCHMARK(BM_Category_FunctionCall);
BENCHMARK(BM_Category_BranchInstruction);
BENCHMARK(BM_Category_VirtualFunctionCall);
BENCHMARK(BM_Category_HeapAllocDealloc);
BENCHMARK(BM_Category_DiskAccess);

BENCHMARK(BM_MinStruct_NoInline_Raw);
BENCHMARK(BM_MinStruct_NoInline_ExpectedSuccess);
BENCHMARK(BM_MinStruct_NoInline_ExpectedFail);

BENCHMARK(BM_NoRVO_OutParam);
BENCHMARK(BM_NoRVO_Copy);
BENCHMARK(BM_RVO_Raw);
BENCHMARK(BM_RVO_Expected);
BENCHMARK(BM_NRVO_Raw);
BENCHMARK(BM_NRVO_Expected);

BENCHMARK(BM_Rate_SuccessAlways_ErrorCode);
BENCHMARK(BM_Rate_Success2outOf3_ErrorCode);
BENCHMARK(BM_Rate_Success1outOf3_ErrorCode);
BENCHMARK(BM_Rate_SuccessNever_ErrorCode);

BENCHMARK(BM_Rate_SuccessAlways_Expected);
BENCHMARK(BM_Rate_Success2outOf3_Expected);
BENCHMARK(BM_Rate_Success1outOf3_Expected);
BENCHMARK(BM_Rate_SuccessNever_Expected);

int main(int argc, char **argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
