#include "BenchPerfCategories.h"
#include "FastRand.h"

void BM_Category_FastRand(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    auto input = fastrand();
    benchmark::DoNotOptimize(input);
  }
}

__attribute__((noinline))
void FunctionCall_NoInline(int input) noexcept {
  benchmark::DoNotOptimize(input);
}

void BM_Category_FunctionCall(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    FunctionCall_NoInline(fastrand());
  }
}

void BM_Category_BranchInstruction(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    int input = fastrand();
    if (input % 2)
      benchmark::DoNotOptimize(input + 1);
    else
      benchmark::DoNotOptimize(input + 2);
  }
}

class BBase {
public:
  virtual ~BBase() {};
  virtual void virtualFunction() = 0;
};

class BDerived1 : public BBase {
public:
  ~BDerived1() override = default;
  void virtualFunction() override { benchmark::ClobberMemory(); };
};

class BDerived2 : public BBase {
public:
  ~BDerived2() override = default;
  void virtualFunction() override { benchmark::ClobberMemory(); };
};

void BM_Category_VirtualFunctionCall(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    BDerived1 d1;
    BDerived2 d2;
    BBase *b = (fastrand() % 2) ? static_cast<BBase *>(&d1)
                                : static_cast<BBase *>(&d2);
    b->virtualFunction();
  }
}

void BM_Category_HeapAllocDealloc(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    char *heapMem = new char[8];
    *heapMem = fastrand();
    benchmark::DoNotOptimize(heapMem);
    delete[] heapMem;
  }
}

void BM_Category_DiskAccess(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    FILE *file = fopen("/usr/include/stdio.h", "r");
    int firstChar = getc(file);
    fclose(file);
    
    benchmark::DoNotOptimize(firstChar);
  }
}
