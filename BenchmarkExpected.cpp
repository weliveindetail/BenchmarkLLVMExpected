#include "bool_bench.h"
#include "int_bench.h"

#include <benchmark/benchmark.h>

// bool data
BENCHMARK(BM_Bool_SuccessAlways_IgnoreErr)->UseManualTime();
BENCHMARK(BM_Bool_SuccessAlways_ErrorCode)->UseManualTime();
BENCHMARK(BM_Bool_SuccessAlways_Expected)->UseManualTime();

BENCHMARK(BM_Bool_Success2outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Bool_Success2outOf3_Expected)->UseManualTime();

BENCHMARK(BM_Bool_Success1outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Bool_Success1outOf3_Expected)->UseManualTime();

// int data
BENCHMARK(BM_Int_SuccessAlways_IgnoreErr)->UseManualTime();
BENCHMARK(BM_Int_SuccessAlways_ErrorCode)->UseManualTime();
BENCHMARK(BM_Int_SuccessAlways_Expected)->UseManualTime();

BENCHMARK(BM_Int_Success2outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Int_Success2outOf3_Expected)->UseManualTime();

BENCHMARK(BM_Int_Success1outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Int_Success1outOf3_Expected)->UseManualTime();

int main(int argc, char **argv) {
  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
}
