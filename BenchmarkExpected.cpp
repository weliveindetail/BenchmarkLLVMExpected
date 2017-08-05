#include <benchmark/benchmark.h>
#include <llvm/Support/Error.h>
#include <chrono>

using namespace std::chrono;

namespace ignore {

bool isSomeModulo(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return true;

  if (value % 2 == 0) // 2, 4, 8, 10, ...
    return false;

  return false;
}

}

namespace expected {

llvm::Expected<bool> isSomeModulo(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return true;

  if (value % 2 == 0) // 2, 4, 8, 10, ...
    return false;

  // 1, 5, 7, 11, ...
  return llvm::make_error<llvm::StringError>(
    "Mocked Error", std::error_code(9, std::system_category()));
}

}

namespace error_code {

std::error_code isSomeModulo(int value, bool &res) {
  if (value % 3 == 0) { // 3, 6, 9, 12, ...
    res = true;
    return std::error_code();
  }

  if (value % 2 == 0) { // 2, 4, 8, 10, ...
    res = false;
    return std::error_code();
  }

  // 1, 5, 7, 11, ...
  return std::error_code(9, std::system_category());
}

}

static void BM_isSomeModulo_IgnoreErr(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto input_time = system_clock::now().time_since_epoch();
    auto input_millis = duration_cast<milliseconds>(input_time).count();

    auto S = high_resolution_clock::now();

    auto res = ignore::isSomeModulo(input_millis);
    (void)res;

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

static void BM_isSomeModulo_ErrorCode(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto input_time = system_clock::now().time_since_epoch();
    auto input_millis = duration_cast<milliseconds>(input_time).count();

    auto S = high_resolution_clock::now();

    bool res;
    auto ec = error_code::isSomeModulo(input_millis, res);
    (void)ec;
    (void)res;
    
    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());
  }
}

static void BM_isSomeModulo_Expected(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto input_time = system_clock::now().time_since_epoch();
    auto input_millis = duration_cast<milliseconds>(input_time).count();

    auto S = high_resolution_clock::now();

    auto result = expected::isSomeModulo(input_millis);

    auto E = high_resolution_clock::now();
    state.SetIterationTime(duration_cast<duration<double>>(E - S).count());

    if (!result)
      llvm::consumeError(result.takeError());
  }
}

BENCHMARK(BM_isSomeModulo_IgnoreErr)->UseManualTime();
BENCHMARK(BM_isSomeModulo_Expected)->UseManualTime();
BENCHMARK(BM_isSomeModulo_ErrorCode)->UseManualTime();

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
}
