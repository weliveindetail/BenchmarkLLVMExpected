#include "int_bench.h"
#include "int_utils.h"

#include <chrono>
#include <system_error>

#include <llvm/Support/Error.h>

// -----------------------------------------------------------------------------

void BM_Int_NoErrors_ErrorCode(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    int res;
    auto ec = error_code::no_errors(input, res);
    (void)ec;
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Int_SuccessAlways_ErrorCode(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    int res;
    auto ec = error_code::success_always(input, res);
    (void)ec;
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Int_Success2outOf3_ErrorCode(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    int res;
    auto ec = error_code::success_2outof3(input, res);
    (void)ec;
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Int_Success1outOf3_ErrorCode(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    int res;
    auto ec = error_code::success_1outof3(input, res);
    (void)ec;
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Int_SuccessNever_ErrorCode(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    int res;
    auto ec = error_code::success_never(input, res);
    (void)ec;
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

// -----------------------------------------------------------------------------

void BM_Int_NoErrors_Expected(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    auto result = expected::no_errors(input);

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());

    if (!result)
      llvm::consumeError(result.takeError());
  }
}

void BM_Int_SuccessAlways_Expected(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    auto result = expected::success_always(input);

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());

    if (!result)
      llvm::consumeError(result.takeError());
  }
}

void BM_Int_Success2outOf3_Expected(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    auto result = expected::success_2outof3(input);

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());

    if (!result)
      llvm::consumeError(result.takeError());
  }
}

void BM_Int_Success1outOf3_Expected(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    auto result = expected::success_1outof3(input);

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());

    if (!result)
      llvm::consumeError(result.takeError());
  }
}

void BM_Int_SuccessNever_Expected(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    auto result = expected::success_never(input);

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());

    if (!result)
      llvm::consumeError(result.takeError());
  }
}
