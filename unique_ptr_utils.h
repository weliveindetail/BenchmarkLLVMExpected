#include <chrono>
#include <memory>
#include <system_error>
#include <vector>

#include <llvm/Support/Error.h>

static int make_input() {
  using namespace std::chrono;
  auto t = system_clock::now().time_since_epoch();
  return duration_cast<milliseconds>(t).count();
}

namespace ignore_error {

static std::unique_ptr<std::vector<int>> success_always(int value) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 > 2) // never
    return nullptr;

  return v; // always
}

static std::unique_ptr<std::vector<int>> success_2outof3(int value) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 > 1) // 2, 5, 8, 11, ...
    return nullptr;

  return v; // 1, 3, 4, 6, 7, 9, 10, ...
}

static std::unique_ptr<std::vector<int>> success_1outof3(int value) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 > 0) // 1, 2, 4, 5, 7, 8, 10, 11, ...
    return nullptr;

  return v; // 3, 6, 9, 12, ...
}

static std::unique_ptr<std::vector<int>> success_never(int value) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 < 5) // always
    return nullptr;

  return v; // never
}
} // namespace ignore_error

namespace error_code {

static std::unique_ptr<std::vector<int>> success_always(int value,
                                                        std::error_code &ec) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 > 2) { // never
    ec = std::error_code(9, std::system_category());
    return nullptr;
  }

  return v; // always
}

static std::unique_ptr<std::vector<int>> success_2outof3(int value,
                                                         std::error_code &ec) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 > 1) { // 2, 5, 8, 11, ...
    ec = std::error_code(9, std::system_category());
    return nullptr;
  }

  return v; // 1, 3, 4, 6, 7, 9, 10, ...
}

static std::unique_ptr<std::vector<int>> success_1outof3(int value,
                                                         std::error_code &ec) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 > 0) { // 1, 2, 4, 5, 7, 8, 10, 11, ...
    ec = std::error_code(9, std::system_category());
    return nullptr;
  }

  return v; // 3, 6, 9, 12, ...
}

static std::unique_ptr<std::vector<int>> success_never(int value,
                                                       std::error_code &ec) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 < 5) { // always
    ec = std::error_code(9, std::system_category());
    return nullptr;
  }

  return v; // never
}
} // namespace error_code

namespace expected {

static llvm::Expected<std::unique_ptr<std::vector<int>>>
success_always(int value) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 > 2) // never
    return llvm::make_error<llvm::StringError>(
        "Mocked Error", std::error_code(9, std::system_category()));

  return std::move(v); // always
}

static llvm::Expected<std::unique_ptr<std::vector<int>>>
success_2outof3(int value) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 > 1) // 2, 5, 8, 11, ...
    return llvm::make_error<llvm::StringError>(
        "Mocked Error", std::error_code(9, std::system_category()));

  return std::move(v); // 1, 3, 4, 6, 7, 9, 10, ...
}

static llvm::Expected<std::unique_ptr<std::vector<int>>>
success_1outof3(int value) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 > 0) // 1, 2, 4, 5, 7, 8, 10, 11, ...
    return llvm::make_error<llvm::StringError>(
        "Mocked Error", std::error_code(9, std::system_category()));

  return std::move(v); // 3, 6, 9, 12, ...
}

static llvm::Expected<std::unique_ptr<std::vector<int>>>
success_never(int value) {
  auto v = std::make_unique<std::vector<int>>();

  if (value % 4 < 2)
    v->push_back(value + 2);
  else
    v->push_back(value - 1);

  if (value % 3 < 5) // always
    return llvm::make_error<llvm::StringError>(
        "Mocked Error", std::error_code(9, std::system_category()));

  return std::move(v); // nevers
}
} // namespace expected
