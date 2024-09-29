#include "task2.h"

#include "aligned_allocator.h"
#include "common.h"

void run_task2() {
  const auto nSize = ARRAY_SIZE + 117;

  const auto a = generate_random_range<aligned_vecf>(nSize);
  const auto b = generate_random_range<aligned_vecf>(nSize);

  benchmark_arrays_addition(a, b);
}
