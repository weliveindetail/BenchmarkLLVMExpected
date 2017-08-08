#include "int_bench.h"
#include "unique_ptr_bench.h"
#include "vector_bench.h"

#include <benchmark/benchmark.h>

// int data
BENCHMARK(BM_Int_SuccessAlways_ErrorCode)->UseManualTime();
BENCHMARK(BM_Int_Success2outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Int_Success1outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Int_SuccessNever_ErrorCode)->UseManualTime();

BENCHMARK(BM_Int_SuccessAlways_Expected)->UseManualTime();
BENCHMARK(BM_Int_Success2outOf3_Expected)->UseManualTime();
BENCHMARK(BM_Int_Success1outOf3_Expected)->UseManualTime();
BENCHMARK(BM_Int_SuccessNever_Expected)->UseManualTime();

// unique_ptr data
BENCHMARK(BM_UniquePtr_SuccessAlways_IgnoreErr)->UseManualTime();
BENCHMARK(BM_UniquePtr_Success2outOf3_IgnoreErr)->UseManualTime();
BENCHMARK(BM_UniquePtr_Success1outOf3_IgnoreErr)->UseManualTime();
BENCHMARK(BM_UniquePtr_SuccessNever_IgnoreErr)->UseManualTime();

BENCHMARK(BM_UniquePtr_SuccessAlways_ErrorCode)->UseManualTime();
BENCHMARK(BM_UniquePtr_Success2outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_UniquePtr_Success1outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_UniquePtr_SuccessNever_ErrorCode)->UseManualTime();

BENCHMARK(BM_UniquePtr_SuccessAlways_Expected)->UseManualTime();
BENCHMARK(BM_UniquePtr_Success2outOf3_Expected)->UseManualTime();
BENCHMARK(BM_UniquePtr_Success1outOf3_Expected)->UseManualTime();
BENCHMARK(BM_UniquePtr_SuccessNever_Expected)->UseManualTime();

// vector data
BENCHMARK(BM_Vector_SuccessAlways_IgnoreErr)->UseManualTime();
BENCHMARK(BM_Vector_Success2outOf3_IgnoreErr)->UseManualTime();
BENCHMARK(BM_Vector_Success1outOf3_IgnoreErr)->UseManualTime();
BENCHMARK(BM_Vector_SuccessNever_IgnoreErr)->UseManualTime();

BENCHMARK(BM_Vector_SuccessAlways_ErrorCode)->UseManualTime();
BENCHMARK(BM_Vector_Success2outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Vector_Success1outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Vector_SuccessNever_ErrorCode)->UseManualTime();

BENCHMARK(BM_Vector_SuccessAlways_Expected)->UseManualTime();
BENCHMARK(BM_Vector_Success2outOf3_Expected)->UseManualTime();
BENCHMARK(BM_Vector_Success1outOf3_Expected)->UseManualTime();
BENCHMARK(BM_Vector_SuccessNever_Expected)->UseManualTime();

int main(int argc, char **argv) {
  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
}
