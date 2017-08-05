#include <benchmark/benchmark.h>

void BM_Bool_SuccessAlways_IgnoreErr(benchmark::State &state);
void BM_Bool_SuccessAlways_ErrorCode(benchmark::State &state);
void BM_Bool_SuccessAlways_Expected(benchmark::State &state);

void BM_Bool_Success2outOf3_ErrorCode(benchmark::State &state);
void BM_Bool_Success2outOf3_Expected(benchmark::State &state);

void BM_Bool_Success1outOf3_ErrorCode(benchmark::State &state);
void BM_Bool_Success1outOf3_Expected(benchmark::State &state);
