#include "task1.h"

#include "common.h"

void run_task1() {
  const auto a = generate_random_array();
  const auto b = generate_random_array();

  benchmark_arrays_addition(a, b);
}
