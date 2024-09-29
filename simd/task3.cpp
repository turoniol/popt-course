#include "task3.h"

#include "common.h"
#include "linalg.h"

void run_task3() {
  const auto nSize = 95'000 + 117;

  auto vec1 = generate_random_range<linvec>(nSize);
  auto vec2 = generate_random_range<linvec>(nSize);

  // Dot product
  float sisd_dot = 0.0f;
  float simd_dot = 0.0f;

  const auto time1 =
      measure_time([&] { sisd_dot = sisd::vector_dot(vec1, vec2); });

  const auto time2 =
      measure_time([&] { simd_dot = simd::vector_dot(vec1, vec2); });

  print_splitter();

  std::cout << "Dot product simple:\n";
  print_results(sisd_dot, time1);

  print_splitter();
  std::cout << "Dot product SIMD:\n";
  print_results(simd_dot, time2);

  print_splitter();

  assert(float_are_equal(sisd_dot, simd_dot));

  // Sum
  benchmark_arrays_addition(vec1, vec2);
}
