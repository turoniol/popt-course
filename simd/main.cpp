#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>

#include <x86intrin.h>

constexpr auto ARRAY_SIZE = 100'000;
using array_t = std::array<float, ARRAY_SIZE>;

template <class F> auto measure_time(F &&func) -> std::chrono::nanoseconds {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();

  return (end - start);
}

void print_results([[maybe_unused]] const array_t &result,
                   std::chrono::nanoseconds time) noexcept {
#ifdef PRINT
  std::cout << "Result: ";
  for (const auto &element : result) {
    std::cout << element << " ";
  }
  std::cout << "\n";
#endif
  std::cout << "Time: " << time.count() << "ns\n";
}

void naive_add(array_t &result, const array_t &left, const array_t &right) {
  for (size_t i = 0; i < result.size(); ++i) {
    result[i] = left[i] + right[i];
  }
}

void fast_add(array_t &result, const array_t &left, const array_t &right) {
  const int nElements = sizeof(__m256) / sizeof(float);

  for (int i = 0; i < result.size(); i += nElements) {
    const __m256 x = _mm256_loadu_ps(left.data() + i);
    const __m256 y = _mm256_loadu_ps(right.data() + i);

    const __m256 result_vector = _mm256_add_ps(x, y);

    _mm256_storeu_ps(result.data() + i, result_vector);
  }
}

auto generate_random_array() -> array_t {
  auto result = array_t{};
  for (auto &element : result) {
    element = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }
  return result;
}

auto float_arrays_are_equal(const array_t &a, const array_t &b) -> bool {
  return std::ranges::equal(
      a, b, [](auto a, auto b) { return std::abs(a - b) < 0.0001; });
}

int main() {
  std::cout << std::setprecision(7) << std::fixed;

  const auto a = generate_random_array();
  const auto b = generate_random_array();

  auto naive_result = array_t{};
  auto fast_result = array_t{};

  std::cout << "--------------------------------\n";
  std::cout << "Naive add:\n";
  print_results(naive_result,
                measure_time([&] { naive_add(naive_result, a, b); }));

  std::cout << "--------------------------------\n";
  std::cout << "Fast add:\n";
  print_results(fast_result,
                measure_time([&] { fast_add(fast_result, a, b); }));

  std::cout << "--------------------------------\n";

  assert(float_arrays_are_equal(naive_result, fast_result));
}