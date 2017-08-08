#include "vector_bench.h"
#include "vector_utils.h"

#include <chrono>
#include <memory>
#include <system_error>

#include <llvm/Support/Error.h>

void BM_Vector_SuccessAlways_IgnoreErr(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    auto res = ignore_error::success_always(input);
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Vector_Success2outOf3_IgnoreErr(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    auto res = ignore_error::success_2outof3(input);
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Vector_Success1outOf3_IgnoreErr(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    auto res = ignore_error::success_1outof3(input);
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Vector_SuccessNever_IgnoreErr(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    auto res = ignore_error::success_never(input);
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Vector_SuccessAlways_ErrorCode(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    std::error_code ec;
    auto res = error_code::success_always(input, ec);
    (void)res;
    (void)ec;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Vector_Success2outOf3_ErrorCode(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    std::error_code ec;
    auto res = error_code::success_2outof3(input, ec);
    (void)res;
    (void)ec;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Vector_Success1outOf3_ErrorCode(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    std::error_code ec;
    auto res = error_code::success_1outof3(input, ec);
    (void)res;
    (void)ec;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Vector_SuccessNever_ErrorCode(benchmark::State &state) {
  using namespace std::chrono;

  while (state.KeepRunning()) {
    auto input = make_input();
    auto S = high_resolution_clock::now();

    std::error_code ec;
    auto res = error_code::success_never(input, ec);
    (void)res;
    (void)ec;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

void BM_Vector_SuccessAlways_Expected(benchmark::State &state) {
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

void BM_Vector_Success2outOf3_Expected(benchmark::State &state) {
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

void BM_Vector_Success1outOf3_Expected(benchmark::State &state) {
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

void BM_Vector_SuccessNever_Expected(benchmark::State &state) {
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
