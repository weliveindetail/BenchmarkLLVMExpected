#include "BenchOptimizations.h"
#include "FastRand.h"

#include <llvm/Support/Error.h>

struct A {
  int value;
};

__attribute__((noinline))
static A MinStruct_NoInline_Raw(int input) noexcept {
  return {input};
}

__attribute__((noinline))
static llvm::Expected<A> MinStruct_NoInline_ExpectedSuccess(int input) noexcept {
  return A{input};
}

__attribute__((noinline))
static llvm::Expected<A> MinStruct_NoInline_ExpectedFail(int input) noexcept {
  return llvm::make_error<llvm::StringError>("mock", std::error_code(1, std::system_category()));
}

void REF_MinStruct_NoInline_Raw() noexcept {
  auto res = MinStruct_NoInline_Raw(fastrand_NoInline());
  benchmark::DoNotOptimize(res);
}

void BM_MinStruct_NoInline_Raw(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_MinStruct_NoInline_Raw();
  }
}

void REF_MinStruct_NoInline_ExpectedSuccess() noexcept {
  auto res = MinStruct_NoInline_ExpectedSuccess(fastrand_NoInline());

#ifndef NDEBUG
  if (!res)
    llvm::consumeError(res.takeError());
#endif

  benchmark::DoNotOptimize(res);
}

void BM_MinStruct_NoInline_ExpectedSuccess(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_MinStruct_NoInline_ExpectedSuccess();
  }
}

void REF_MinStruct_NoInline_ExpectedFail() noexcept {
  auto res = MinStruct_NoInline_ExpectedFail(fastrand_NoInline());

#ifndef NDEBUG
  if (!res)
    llvm::consumeError(res.takeError());
#endif

  benchmark::DoNotOptimize(res);
}

void BM_MinStruct_NoInline_ExpectedFail(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_MinStruct_NoInline_ExpectedFail();
  }
}

// -----------------------------------------------------------------------------
/*
class MoveDelete {
public:
  MoveDelete(MoveDelete &&) = delete;
  std::vector<int> v;
};

__attribute__((noinline))
static llvm::Expected<MoveDelete> MoveCtor_Delete() {
  MoveDelete res {{
    fastrand(), fastrand(), fastrand(), fastrand(),
    fastrand(), fastrand(), fastrand(), fastrand()
  }};
  return llvm::Expected<MoveDelete>(res);
}

void REF_MoveCtor_Delete() noexcept {
  auto res = MoveCtor_Delete();

#ifndef NDEBUG
  if (!res)
    llvm::consumeError(res.takeError());
#endif

  benchmark::DoNotOptimize(res);
}

void BM_MoveCtor_Delete(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_NRVO_Expected();
  }
}
*/
// -----------------------------------------------------------------------------

__attribute__((noinline))
static void NoRVO_OutParam(std::vector<int> &v) {
  v.reserve(8);
  v[0] = fastrand();
  v[1] = fastrand();
  v[2] = fastrand();
  v[3] = fastrand();
  v[4] = fastrand();
  v[5] = fastrand();
  v[6] = fastrand();
  v[7] = fastrand();
}

void REF_NoRVO_OutParam() noexcept {
  std::vector<int> res;
  NoRVO_OutParam(res);
  benchmark::DoNotOptimize(res);
}

void BM_NoRVO_OutParam(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_NoRVO_OutParam();
  }
}

__attribute__((noinline))
static std::vector<int> NoRVO_Copy() noexcept {
  std::vector<int> res {
    fastrand(), fastrand(), fastrand(), fastrand(),
    fastrand(), fastrand(), fastrand(), fastrand()
  };
  return std::vector<int>{res};
}

void REF_NoRVO_Copy() noexcept {
  std::vector<int> res = NoRVO_Copy();
  benchmark::DoNotOptimize(res);
}

void BM_NoRVO_Copy(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_NoRVO_Copy();
  }
}

// -----------------------------------------------------------------------------

__attribute__((noinline))
static std::vector<int> RVO_Raw() {
  return {
    fastrand(), fastrand(), fastrand(), fastrand(),
    fastrand(), fastrand(), fastrand(), fastrand()
  };
}

void REF_RVO_Raw() noexcept {
  std::vector<int> res = RVO_Raw();
  benchmark::DoNotOptimize(res);
}

void BM_RVO_Raw(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_RVO_Raw();
  }
}

__attribute__((noinline))
static llvm::Expected<std::vector<int>> RVO_Expected() {
  return std::vector<int>{
    fastrand(), fastrand(), fastrand(), fastrand(),
    fastrand(), fastrand(), fastrand(), fastrand()
  };
}

void REF_RVO_Expected() noexcept {
  auto res = RVO_Expected();

#ifndef NDEBUG
  if (!res)
    llvm::consumeError(res.takeError());
#endif

  benchmark::DoNotOptimize(res);
}

void BM_RVO_Expected(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_RVO_Expected();
  }
}

// -----------------------------------------------------------------------------

__attribute__((noinline))
static std::vector<int> NRVO_Raw() noexcept {
  std::vector<int> res {
    fastrand(), fastrand(), fastrand(), fastrand(),
    fastrand(), fastrand(), fastrand(), fastrand()
  };
  return res;
}

void REF_NRVO_Raw() noexcept {
  std::vector<int> res = NRVO_Raw();
  benchmark::DoNotOptimize(res);
}

void BM_NRVO_Raw(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_NRVO_Raw();
  }
}

__attribute__((noinline))
static llvm::Expected<std::vector<int>> NRVO_Expected() {
  std::vector<int> res {
    fastrand(), fastrand(), fastrand(), fastrand(),
    fastrand(), fastrand(), fastrand(), fastrand()
  };
  return std::move(res);
}

void REF_NRVO_Expected() noexcept {
  auto res = NRVO_Expected();

#ifndef NDEBUG
  if (!res)
    llvm::consumeError(res.takeError());
#endif

  benchmark::DoNotOptimize(res);
}

void BM_NRVO_Expected(benchmark::State &state) noexcept {
  while (state.KeepRunning()) {
    REF_NRVO_Expected();
  }
}
