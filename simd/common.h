#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

#include "simd.h"

constexpr auto ARRAY_SIZE = 100'000;
using vec = std::vector<float>;

namespace detail {
template <class T>
concept has_resize = requires(T val, size_t n) {
  val.resize(n);
};
} // namespace detail

template <class F> auto measure_time(F &&func) -> std::chrono::nanoseconds {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();

  return (end - start);
}

template <std::ranges::random_access_range R>
void print_results([[maybe_unused]] const R &result,
                   std::chrono::nanoseconds time) noexcept {
  {
#ifdef PRINT
    std::cout << "Result: ";
    for (const auto &element : result) {
      std::cout << element << " ";
    }
    std::cout << "\n";
#endif
    std::cout << "Time: " << time.count() << "ns\n";
  }
}

namespace detail {
template <std::ranges::random_access_range R>
auto float_arrays_are_equal(const R &a, const R &b) -> bool {
  return std::ranges::equal(
      a, b, [](auto l, auto r) { return std::abs(l - r) < 0.0001; });
}
} // namespace detail

template <std::ranges::random_access_range R>
void assert_arrays_are_equal(R &&a, R &&b) {
  assert(detail::float_arrays_are_equal(a, b));
}

template <std::ranges::random_access_range R>
void benchmark_arrays_addition(const R &a, const R &b) {
  assert(std::ranges::size(a) == std::ranges::size(b));

  auto naive_result = R{};
  auto fast_result = R{};

  if constexpr (detail::has_resize<R>) {
    naive_result.resize(std::ranges::size(a));
    fast_result.resize(std::ranges::size(a));
  }

  std::cout << "--------------------------------\n";
  std::cout << "Naive add:\n";
  print_results(naive_result,
                measure_time([&] { naive_add(naive_result, a, b); }));

  std::cout << "--------------------------------\n";
  std::cout << "Fast add:\n";
  print_results(fast_result,
                measure_time([&] { fast_add(fast_result, a, b); }));

  std::cout << "--------------------------------\n";

  assert_arrays_are_equal(naive_result, fast_result);
}

template <std::ranges::random_access_range R>
auto generate_random_range(std::size_t size = ARRAY_SIZE) -> R {
  auto result = R{};

  if constexpr (detail::has_resize<R>) {
    result.resize(size);
  }

  for (auto &element : result) {
    element = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }
  return result;
}