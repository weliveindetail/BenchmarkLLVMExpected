#include <chrono>
#include <system_error>

#include <llvm/Support/Error.h>

static int make_input() {
  using namespace std::chrono;
  auto t = system_clock::now().time_since_epoch();
  return duration_cast<milliseconds>(t).count();
}

namespace ignore_error {

static int success_always(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return value + 2;

  if (value % 6 != 0) // 1, 2, 4, 5, 7, 8, 10, 11, ...
    return value - 3;

  return 0; // never
}
} // namespace ignore_error

namespace error_code {

static std::error_code success_always(int value, int &res) {
  if (value % 3 == 0) { // 3, 6, 9, 12, ...
    res = value + 2;
    return std::error_code();
  }

  if (value % 6 != 0) { // 1, 2, 4, 5, 7, 8, 10, 11, ...
    res = value - 3;
    return std::error_code();
  }

  return std::error_code(9, std::system_category()); // never
}

static std::error_code success_2outof3(int value, int &res) {
  if (value % 3 == 0) { // 3, 6, 9, 12, ...
    res = value + 2;
    return std::error_code();
  }

  if (value % 2 == 0) { // 2, 4, 8, 10, ...
    res = value - 3;
    return std::error_code();
  }

  return std::error_code(9, std::system_category()); // 1, 5, 7, 11, ...
}

static std::error_code success_1outof3(int value, int &res) {
  if (value % 6 == 0) { // 6, ...
    res = value + 2;
    return std::error_code();
  }

  if (value % 3 == 0) { // 3, 9, ...
    res = value - 3;
    return std::error_code();
  }

  return std::error_code(9, std::system_category()); // 1, 2, 4, 5, 7, 8 ...
}

static std::error_code success_never(int value, int &res) {
  if (value % 3 == 3) { // never
    res = value + 2;
    return std::error_code();
  }

  if (value % 6 > 5) { // never
    res = value - 3;
    return std::error_code();
  }

  return std::error_code(9, std::system_category()); // always
}
} // namespace error_code

namespace expected {

static llvm::Expected<int> success_always(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return value + 2;

  if (value % 6 != 0) // 1, 2, 4, 5, 7, 8, 10, 11, ...
    return value - 3;

  return llvm::make_error<llvm::StringError>( // never
      "Mocked Error", std::error_code(9, std::system_category()));
}

static llvm::Expected<int> success_2outof3(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return value + 2;

  if (value % 2 == 0) // 2, 4, 8, 10, ...
    return value - 3;

  return llvm::make_error<llvm::StringError>( // 1, 5, 7, 11, ...
      "Mocked Error", std::error_code(9, std::system_category()));
}

static llvm::Expected<int> success_1outof3(int value) {
  if (value % 6 == 0) // 6, ...
    return value + 2;

  if (value % 3 == 0) // 3, 9, ...
    return value - 3;

  return llvm::make_error<llvm::StringError>( // 1, 2, 4, 5, 7, 8 ...
      "Mocked Error", std::error_code(9, std::system_category()));
}

static llvm::Expected<int> success_never(int value) {
  if (value % 3 == 3) // never
    return value + 2;

  if (value % 6 > 5) // never
    return value - 3;

  return llvm::make_error<llvm::StringError>( // always
      "Mocked Error", std::error_code(9, std::system_category()));
}
} // namespace expected
