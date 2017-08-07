#include <chrono>
#include <system_error>

#include <llvm/Support/Error.h>

static int make_input() {
  using namespace std::chrono;
  auto t = system_clock::now().time_since_epoch();
  return duration_cast<milliseconds>(t).count();
}

namespace ignore_error {

static bool success_always(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return true;

  if (value % 6 != 0) // 1, 2, 4, 5, 7, 8, 10, 11, ...
    return false;

  return false; // never
}
}

namespace error_code {

static std::error_code success_always(int value, bool &res) {
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

static std::error_code success_2outof3(int value, bool &res) {
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

static std::error_code success_1outof3(int value, bool &res) {
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

static std::error_code success_never(int value, bool &res) {
  if (value % 3 == 3) { // never
    res = true;
    return std::error_code();
  }

  if (value % 6 > 5) { // never
    res = false;
    return std::error_code();
  }

  return std::error_code(9, std::system_category()); // always
}
}

namespace expected {

static llvm::Expected<bool> success_always(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return true;

  if (value % 6 != 0) // 1, 2, 4, 5, 7, 8, 10, 11, ...
    return false;

  return llvm::make_error<llvm::StringError>( // never
      "Mocked Error", std::error_code(9, std::system_category()));
}

static llvm::Expected<bool> success_2outof3(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return true;

  if (value % 2 == 0) // 2, 4, 8, 10, ...
    return false;

  return llvm::make_error<llvm::StringError>( // 1, 5, 7, 11, ...
      "Mocked Error", std::error_code(9, std::system_category()));
}

static llvm::Expected<bool> success_1outof3(int value) {
  if (value % 6 == 0) // 6, ...
    return true;

  if (value % 3 == 0) // 3, 9, ...
    return false;

  return llvm::make_error<llvm::StringError>( // 1, 2, 4, 5, 7, 8 ...
      "Mocked Error", std::error_code(9, std::system_category()));
}

static llvm::Expected<bool> success_never(int value) {
  if (value % 3 == 3) // never
    return true;

  if (value % 6 > 5) // never
    return false;

  return llvm::make_error<llvm::StringError>( // always
      "Mocked Error", std::error_code(9, std::system_category()));
}
}
