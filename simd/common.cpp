#include "common.h"

void print_results(float result, std::chrono::nanoseconds time) noexcept {
  std::cout << "Result: " << result << "\n";
  std::cout << "Time: " << time.count() << "ns\n";
}

bool float_are_equal(float a, float b) noexcept {
  return std::abs(a - b) < 0.0001f;
}

void print_splitter() { std::cout << "--------------------------------\n"; }
