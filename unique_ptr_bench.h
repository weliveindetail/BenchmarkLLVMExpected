#include <benchmark/benchmark.h>

void BM_UniquePtr_SuccessAlways_IgnoreErr(benchmark::State &state);
void BM_UniquePtr_SuccessAlways_ErrorCode(benchmark::State &state);
void BM_UniquePtr_SuccessAlways_Expected(benchmark::State &state);

void BM_UniquePtr_Success2outOf3_IgnoreErr(benchmark::State &state);
void BM_UniquePtr_Success2outOf3_ErrorCode(benchmark::State &state);
void BM_UniquePtr_Success2outOf3_Expected(benchmark::State &state);

void BM_UniquePtr_Success1outOf3_IgnoreErr(benchmark::State &state);
void BM_UniquePtr_Success1outOf3_ErrorCode(benchmark::State &state);
void BM_UniquePtr_Success1outOf3_Expected(benchmark::State &state);

void BM_UniquePtr_SuccessNever_IgnoreErr(benchmark::State &state);
void BM_UniquePtr_SuccessNever_ErrorCode(benchmark::State &state);
void BM_UniquePtr_SuccessNever_Expected(benchmark::State &state);
