#include "BenchPerfCategories.h"
#include "FastRand.h"

// Runtime for generating a single pseudo-random number
void BM_Category_FastRand(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    auto input = fastrand();
    benchmark::DoNotOptimize(input);
  }
}

// Overhead of minimal unpredictable branch instruction
void BM_Category_FastRand_BranchInstruction(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    if (fastrand() % 2)
      benchmark::ClobberMemory();
    else
      benchmark::ClobberMemory();
  }
}

__attribute__((noinline))
void FunctionCall1_NoInline() noexcept {
  benchmark::ClobberMemory();
}

__attribute__((noinline))
void FunctionCall2_NoInline() noexcept {
  benchmark::ClobberMemory();
}

// Overhead of minimal unpredictable function call
void BM_Category_FastRand_FunctionCall(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    if (fastrand() % 2)
      FunctionCall1_NoInline();
    else
      FunctionCall2_NoInline();
  }
}

void FunctionPtrCall1() noexcept {
  benchmark::ClobberMemory();
}

void FunctionPtrCall2() noexcept {
  benchmark::ClobberMemory();
}

// Overhead of minimal unpredictable function pointer call (like virtual func.)
void BM_Category_FastRand_FunctionPtrCall(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    ((fastrand() % 2) ? &FunctionPtrCall1 : &FunctionPtrCall2)();
  }
}

// Runtime of minimal heap allocation + deallocation
void BM_Category_HeapAllocDealloc(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    int *heapMem = new int;
    benchmark::DoNotOptimize(heapMem);
    delete heapMem;
  }
}

__attribute__((noinline))
void UniquePtrReceiver(std::unique_ptr<int> value) noexcept {
  benchmark::DoNotOptimize(value);
}

// Overhead of passing a unique_ptr to a function by move
void BM_Category_HeapAllocDealloc_UniquePtrMove(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    auto value = std::make_unique<int>(42);
    UniquePtrReceiver(std::move(value));
  }
}

__attribute__((noinline))
void SharedPtrReceiver(std::shared_ptr<int> value) noexcept {
  benchmark::DoNotOptimize(value);
}

// Overhead of passing a shared_ptr to a function by move
void BM_Category_HeapAllocDealloc_SharedPtrMove(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    auto value = std::make_shared<int>(42);
    SharedPtrReceiver(std::move(value));
  }
}

// Overhead of passing a shared_ptr to a function by copy
void BM_Category_HeapAllocDealloc_SharedPtrCopy(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    auto value = std::make_shared<int>(42);
    SharedPtrReceiver(value);
    benchmark::DoNotOptimize(value);
  }
}

// Overhead of minimal read access to hard disk
void BM_Category_DiskReadAccess(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    FILE *file = fopen("/usr/include/stdio.h", "r");
    int firstChar = getc(file);
    fclose(file);

    benchmark::DoNotOptimize(firstChar);
  }
}
