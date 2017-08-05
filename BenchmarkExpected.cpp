#include <benchmark/benchmark.h>

#include <llvm/Support/Error.h>

#include <chrono>
using namespace std::chrono;

namespace check_bool {

int make_input() {
  auto t = system_clock::now().time_since_epoch();
  return duration_cast<milliseconds>(t).count();
}

namespace ignore_error {

bool success_always(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return true;

  if (value % 6 != 0) // 1, 2, 4, 5, 7, 8, 10, 11, ...
    return false;

  return false; // never
}
}

namespace error_code {

std::error_code success_always(int value, bool &res) {
  if (value % 3 == 0) { // 3, 6, 9, 12, ...
    res = true;
    return std::error_code();
  }

  if (value % 6 != 0) { // 1, 2, 4, 5, 7, 8, 10, 11, ...
    res = false;
    return std::error_code();
  }

  return std::error_code(9, std::system_category()); // never
}

std::error_code success2outof3(int value, bool &res) {
  if (value % 3 == 0) { // 3, 6, 9, 12, ...
    res = true;
    return std::error_code();
  }

  if (value % 2 == 0) { // 2, 4, 8, 10, ...
    res = false;
    return std::error_code();
  }

  return std::error_code(9, std::system_category()); // 1, 5, 7, 11, ...
}

std::error_code success1outof3(int value, bool &res) {
  if (value % 6 == 0) { // 6, ...
    res = true;
    return std::error_code();
  }

  if (value % 3 == 0) { // 3, 9, ...
    res = false;
    return std::error_code();
  }

  return std::error_code(9, std::system_category()); // 1, 2, 4, 5, 7, 8 ...
}
}

namespace expected {

llvm::Expected<bool> success_always(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return true;

  if (value % 6 != 0) // 1, 2, 4, 5, 7, 8, 10, 11, ...
    return false;

  return llvm::make_error<llvm::StringError>( // never
      "Mocked Error", std::error_code(9, std::system_category()));
}

llvm::Expected<bool> success2outof3(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return true;

  if (value % 2 == 0) // 2, 4, 8, 10, ...
    return false;

  return llvm::make_error<llvm::StringError>( // 1, 5, 7, 11, ...
      "Mocked Error", std::error_code(9, std::system_category()));
}

llvm::Expected<bool> success1outof3(int value) {
  if (value % 6 == 0) // 6, ...
    return true;

  if (value % 3 == 0) // 3, 9, ...
    return false;

  return llvm::make_error<llvm::StringError>( // 1, 2, 4, 5, 7, 8 ...
      "Mocked Error", std::error_code(9, std::system_category()));
}
}
}

static void BM_Bool_SuccessAlways_IgnoreErr(benchmark::State &state) {
  while (state.KeepRunning()) {
    auto input = check_bool::make_input();
    auto S = high_resolution_clock::now();

    auto res = check_bool::ignore_error::success_always(input);
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

static void BM_Bool_SuccessAlways_ErrorCode(benchmark::State &state) {
  while (state.KeepRunning()) {
    auto input = check_bool::make_input();
    auto S = high_resolution_clock::now();

    bool res;
    auto ec = check_bool::error_code::success_always(input, res);
    (void)ec;
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

static void BM_Bool_Success2outOf3_ErrorCode(benchmark::State &state) {
  while (state.KeepRunning()) {
    auto input = check_bool::make_input();
    auto S = high_resolution_clock::now();

    bool res;
    auto ec = check_bool::error_code::success2outof3(input, res);
    (void)ec;
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

static void BM_Bool_Success1outOf3_ErrorCode(benchmark::State &state) {
  while (state.KeepRunning()) {
    auto input = check_bool::make_input();
    auto S = high_resolution_clock::now();

    bool res;
    auto ec = check_bool::error_code::success1outof3(input, res);
    (void)ec;
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

static void BM_Bool_SuccessAlways_Expected(benchmark::State &state) {
  while (state.KeepRunning()) {
    auto input = check_bool::make_input();
    auto S = high_resolution_clock::now();

    auto result = check_bool::expected::success_always(input);

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());

    if (!result)
      llvm::consumeError(result.takeError());
  }
}

static void BM_Bool_Success2outOf3_Expected(benchmark::State &state) {
  while (state.KeepRunning()) {
    auto input = check_bool::make_input();
    auto S = high_resolution_clock::now();

    auto result = check_bool::expected::success2outof3(input);

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());

    if (!result)
      llvm::consumeError(result.takeError());
  }
}

static void BM_Bool_Success1outOf3_Expected(benchmark::State &state) {
  while (state.KeepRunning()) {
    auto input = check_bool::make_input();
    auto S = high_resolution_clock::now();

    auto result = check_bool::expected::success1outof3(input);

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());

    if (!result)
      llvm::consumeError(result.takeError());
  }
}

BENCHMARK(BM_Bool_SuccessAlways_IgnoreErr)->UseManualTime();
BENCHMARK(BM_Bool_SuccessAlways_ErrorCode)->UseManualTime();
BENCHMARK(BM_Bool_SuccessAlways_Expected)->UseManualTime();

BENCHMARK(BM_Bool_Success2outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Bool_Success2outOf3_Expected)->UseManualTime();

BENCHMARK(BM_Bool_Success1outOf3_ErrorCode)->UseManualTime();
BENCHMARK(BM_Bool_Success1outOf3_Expected)->UseManualTime();

int main(int argc, char **argv) {
  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
}
