#include <benchmark/benchmark.h>

void BM_Int_SuccessAlways_IgnoreErr(benchmark::State &state);
void BM_Int_SuccessAlways_ErrorCode(benchmark::State &state);
void BM_Int_SuccessAlways_Expected(benchmark::State &state);

void BM_Int_Success2outOf3_ErrorCode(benchmark::State &state);
void BM_Int_Success2outOf3_Expected(benchmark::State &state);

void BM_Int_Success1outOf3_ErrorCode(benchmark::State &state);
void BM_Int_Success1outOf3_Expected(benchmark::State &state);