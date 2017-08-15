#pragma once

#include <benchmark/benchmark.h>

void BM_Category_FastRand(benchmark::State &state) noexcept;
void BM_Category_FunctionCall(benchmark::State &state) noexcept;
void BM_Category_BranchInstruction(benchmark::State &state) noexcept;
void BM_Category_VirtualFunctionCall(benchmark::State &state) noexcept;
void BM_Category_HeapAllocDealloc(benchmark::State &state) noexcept;
void BM_Category_DiskAccess(benchmark::State &state) noexcept;
