#include <chrono>
#include <system_error>

#include <llvm/Support/Error.h>

int make_input() {
  using namespace std::chrono;
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

std::error_code success_2outof3(int value, bool &res) {
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

std::error_code success_1outof3(int value, bool &res) {
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

llvm::Expected<bool> success_2outof3(int value) {
  if (value % 3 == 0) // 3, 6, 9, 12, ...
    return true;

  if (value % 2 == 0) // 2, 4, 8, 10, ...
    return false;

  return llvm::make_error<llvm::StringError>( // 1, 5, 7, 11, ...
      "Mocked Error", std::error_code(9, std::system_category()));
}

llvm::Expected<bool> success_1outof3(int value) {
  if (value % 6 == 0) // 6, ...
    return true;

  if (value % 3 == 0) // 3, 9, ...
    return false;

  return llvm::make_error<llvm::StringError>( // 1, 2, 4, 5, 7, 8 ...
      "Mocked Error", std::error_code(9, std::system_category()));
}
}
