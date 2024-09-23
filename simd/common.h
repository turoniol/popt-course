#pragma once

#include <chrono>

constexpr auto ARRAY_SIZE = 100'000;
using array_t = std::array<float, ARRAY_SIZE>;

template <class F> auto measure_time(F &&func) -> std::chrono::nanoseconds {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();

  return (end - start);
}

void print_results([[maybe_unused]] const array_t &result,
                   std::chrono::nanoseconds time) noexcept;

void assert_arrays_are_equal(const array_t &a, const array_t &b);

void benchmark_arrays_addition(const array_t& a, const array_t& b);

auto generate_random_array() -> array_t;