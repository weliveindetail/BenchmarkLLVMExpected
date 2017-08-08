#include <benchmark/benchmark.h>

void BM_Vector_SuccessAlways_IgnoreErr(benchmark::State &state);
void BM_Vector_SuccessAlways_ErrorCode(benchmark::State &state);
void BM_Vector_SuccessAlways_Expected(benchmark::State &state);

void BM_Vector_Success2outOf3_IgnoreErr(benchmark::State &state);
void BM_Vector_Success2outOf3_ErrorCode(benchmark::State &state);
void BM_Vector_Success2outOf3_Expected(benchmark::State &state);

void BM_Vector_Success1outOf3_IgnoreErr(benchmark::State &state);
void BM_Vector_Success1outOf3_ErrorCode(benchmark::State &state);
void BM_Vector_Success1outOf3_Expected(benchmark::State &state);

void BM_Vector_SuccessNever_IgnoreErr(benchmark::State &state);
void BM_Vector_SuccessNever_ErrorCode(benchmark::State &state);
void BM_Vector_SuccessNever_Expected(benchmark::State &state);
